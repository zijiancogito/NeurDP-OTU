#include <regex>
#include <cstdlib>
#include "aarch64real.h"

// #define TRAIN

namespace code {
  namespace real{
  void aarch64Asm::init() {
    #ifdef TRAIN
    int sections_size = root["sections"].size();
    for (int i = 0; i < sections_size; i++)
    {
      int functions_size = root["sections"][i]["functions"].size();
      for (int j = 0; j < functions_size; j++){
        std::string function_name = root["sections"][i]["functions"][j]["function"].asString();
        map<BLOCK_ADDR, Json::Value *> blks;
        blks[0] = &root["sections"][i]["functions"][j]["instructions"];
        functions[function_name] = blks;
      }
      }
    }

    #else
    Json::Value::Members members;
    members = root.getMemberNames();
    for (Json::Value::Members::iterator itM = members.begin(); itM != members.end(); itM++){
      string sec_key = *itM;
      #ifdef DEBUG
      cout << sec_key << endl;
      #endif
      Json::Value *funcs = &(root[sec_key]);
      int func_cnt = funcs->size();
      for (int i = 0; i < func_cnt; i++)
      {
        string func_name = (*funcs)[i]["function"].asString();
        #ifdef DEBUG
        cout << func_name << endl;
        #endif
        Json::Value *blks = &((*funcs)[i]["blocks"]);
        int blk_cnt = blks->size();
        map<BLOCK_ADDR, Json::Value *> blocks;
        for (int j = 0; j < blk_cnt; j++)
        {
          char *end;
          char *addr = (char*)(*blks)[j]["vaddr"].asCString();
          Json::Value *insts = &((*blks)[j]["instructions"]);
          blocks[strtol(addr, &end, 16)] = insts;
        }
        functions[func_name] = blocks;
        #ifdef DEBUG
        for (auto t: blocks) {
          cout << t.second->size() << endl;
        }
        #endif
      }
    }
    #endif
  }

  void aarch64Asm::getOpcodeSequence(std::string &function, std::vector<std::string> &s) {
    map<BLOCK_ADDR, Json::Value *> blks = functions[function];
    for (auto it: blks) {
      Json::Value *insts = it.second;
      int insts_size = insts->size();
      for (int i = 0; i < insts_size; i++){
        s.push_back((*insts)[i]["mnemonic"].asString());
      }
    }
  }

  void aarch64Asm::getRemovedOpcodeSequence(std::string &function, options::aarch64::PASSES passes, std::vector<std::string> &s) {
    map<BLOCK_ADDR, Json::Value *> blks = functions[function];
    for (auto it: blks) {
      Json::Value *insts = it.second;
      int insts_size = insts->size();
      for (int i = 0; i < insts_size; i++){
        std::string inst = insts[i]["instruction"].asString();
        std::vector<std::string> p;
        bool parsed = parseRawInstruction(inst, &p);
        if (parsed) {
          if (options::aarch64::removeInst(passes, p[0]))
            continue;
          // s.push_back(insts[i]["mnemonic"].asString());
          s.push_back(p[0]);
        }
      }
    }
  }

  void aarch64Asm::getFunctionsName(std::vector<std::string> & FunctionNames){
    for(auto it: functions){
      // regex func("func(.*)");
      // if (regex_match(it->first, func)){
      //   FunctionNames.push_back(it->first);
      // }
      FunctionNames.push_back(it.first);
    }

  }

  bool aarch64Asm::parseRawInstruction(std::string &inst, std::vector<std::string> * res){
    std::string instruction_pattern = "([\\S]+)[\\t]*(.*)";
    std::regex instruction_regex(instruction_pattern);
    std::smatch match;
    if (std::regex_match(inst, match, instruction_regex))
    {
      res->push_back(match[1]);
      return true;
    }
    else
    {
      std::cout << "Instruction ERROR" << std::endl;
      return false;
    }
  }

  string aarch64Asm::replaceVariable(string &operand_str) {
    regex imm_index("\\[([\\S]+), (#[\\-]*[0-9]+)\\]");
    regex post_index("\\[([\\S]+)\\], (#\\-*[0-9]+)");
    regex no_index("\\[([\\S]+)\\]");
    smatch match;
    string addr;
    if (regex_search(operand_str, match, imm_index))
    {
      string base = match[1];
      string offset = match[2];
      addr = base + offset;
      operand_str = regex_replace(operand_str, imm_index, "LOCAL");
    }
    else if (regex_search(operand_str, match, post_index))
    {
      string base = match[1];
      string offset = match[2];
      addr = base + offset;
      operand_str = regex_replace(operand_str, post_index, "LOCAL");
    }
    else if (regex_search(operand_str, match, no_index))
    {
      string base = match[1];
      string offset = "#0";
      addr = base + offset;
      operand_str = regex_replace(operand_str, no_index, "LOCAL");
    }
    else {
      return "";
    }
    return addr;
  }

  ADDR aarch64Asm::parseLocalVariable (string &operand) {
    // (\\[[\\S]+, [\\S]+\\])|(\\[[\\S]+\\](, #\\-*[0-9]+)*)
    /* Analyze Local Variable */
    // regex imm_index("\\[([\\S]+), #([\\-]*[0-9]+)\\]");
    // regex post_index("\\[([\\S]+)\\], #(\\-*[0-9]+)");
    // regex no_index("\\[([\\S]+)\\]");
    regex imm_index("([\\S]+)#([\\-]*[0-9]+)");
    smatch match;
    ADDR res;
    if (regex_match(operand, match, imm_index))
    {
      string base = match[1];
      res.base = {getRegister(match[1]), 0};
      string reg = getRegisterName(getRegister(match[1]));
      regex r(base);
      regex_replace(operand, r, reg);
      res.offset = std::stoi(match[2]);
    }
    // } else if (regex_match(operand, match, post_index)) {
    //   res.base = {getRegister(match[1]), 0};
    //   res.offset = std::stoi(match[2]);
    // } else if(regex_match(operand, match, no_index)) {
    //   res.base = {getRegister(match[1]), 0};
    //   res.offset = 0;
    else {
      std::cout << "Error" << std::endl;
    }
    return res;
  }

  int aarch64Asm::parseLabel (string &operand) {
    regex label("#(.*)");
    regex abs_label("<([\\S]+)[\\+\\-]0x([0-9]+)>");
    smatch match;
    if (regex_match(operand, match, label)){
      return stoi(match[2]);
    }
    if(regex_match(operand, match, abs_label)) {
      return stoi(match[2]);
    }
    return 0;
  }

  int aarch64Asm::parseImmediate (string &operand) {
    regex imm("#(.*)");
    smatch match;
    if (regex_match(operand, match, imm))
    {
      return stoi(match[1]);
    }
    return 0;
  }

  void aarch64Asm::parseOperands(string &operand_str, vector<OPERAND> *operands) {
    string addr = replaceVariable(operand_str);
    regex ope_reg("([^,\\s]+)");
    sregex_iterator start(operand_str.cbegin(), operand_str.cend(), ope_reg);
    sregex_iterator end;
    for (; start != end; start++)
    {
      string op_str = start->str(1);
      OPERAND op;
      OperandType tp = getType(op_str);
      op.type = tp;
      OP tmp;
      switch (tp)
      {
      case VARIABLE:
        tmp.var = parseLocalVariable(addr);
        op.operand = tmp;
        op.content = addr;
        break;
      case REGISTER:
        tmp.reg = {getRegister(op_str), 0};
        op.operand = tmp;
        op.content = getRegisterName(getRegister(op_str));
        break;
      case LABEL:
        tmp.imm = parseLabel(op_str);
        op.operand = tmp;
        op.content = op_str;
        break;
      case IMMEDIATE:
        tmp.imm = parseImmediate(op_str);
        op.operand = tmp;
        op.content = op_str;
        break;
      default:
        break;
      };
      operands->push_back(op);
    }
  }

  bool aarch64Asm::isCall(std::string &mnemonic) {
    if (mnemonic == "bl")
      return true;
    return false;
  }

  void aarch64Asm::buildReturnValue(OPERAND &ret) {
    ret.content = "x0";
    OP op;
    op.reg = {getRegister("x0"), 0};
    ret.operand = op;
    ret.type = REGISTER;
  }

  void aarch64Asm::parseRawInstruction(string &inst, INSTRUCTION *instruction) {
    regex ins_reg("([\\S]+)[\\t]*(.*)");
    string operand_str;
    smatch match;
    vector<OPERAND> operands;
    if (regex_match(inst, match, ins_reg))
    {
      instruction->mnemonic = match[1];
      operand_str = match[2];
      parseOperands(operand_str, &operands);
      // cout << operands.size() << endl;
      if (operands.size() > 0 && (!isCall(instruction->mnemonic)) && (!isStore(instruction->mnemonic)))
      {
        instruction->destination = operands[0];

        operands.erase(operands.cbegin());
        instruction->source = operands;
        #ifdef DEBUG
        cout <<  instruction->mnemonic << ":" <<instruction->destination.content << endl;
        #endif
      }
      else if (isCall(instruction->mnemonic))
      {
        
        OPERAND ret;
        buildReturnValue(ret);
        instruction->destination = ret;
        instruction->source = operands;
        #ifdef DEBUG
        cout << instruction->mnemonic << ": " << ret.content << endl;
        #endif
      }
      else if (isStore(instruction->mnemonic))
      {
        instruction->destination = operands.back();
        operands.pop_back();
        instruction->source = operands;
      }
      else if(isRet(instruction->mnemonic)) {
        OPERAND ret;
        buildReturnValue(ret);
        operands.push_back(ret);
        instruction->source = operands;
      }
      else
      {
        instruction->source = operands;
      }
    }
  }

  bool aarch64Asm::isRet (string &mnemonic) {
    if (mnemonic == "ret") {
      return true;
    }
    return false;
  }

  bool aarch64Asm::isStore (string &mnemonic){
    options::aarch64::PASSES p;
    p.load = false;
    p.mov = false;
    return options::aarch64::removeInst(p, mnemonic);
  }

  void aarch64Asm::replaceLabel (std::string &inst, std::string &label) {
    regex addr("(#[\\-]*[0-9]+)");
    // smatch match;
    label = "<" + label + ">";
    if (regex_search(inst, addr))
    {
      inst = regex_replace(inst, addr, label);
    }
  }

  void aarch64Asm::extractRawCode (std::string &function, RAWFUNC *code, bool replace) {
    map<BLOCK_ADDR, Json::Value *> blks = functions[function];
    for (auto it : blks)
    {
      Json::Value *insts = it.second;
      BLOCK_ADDR start = it.first;
      int insts_size = insts->size();
      RAWBLOCK rb;
      for (int i = 0; i < insts_size; i++)
      {
        string inst = (*insts)[i]["instruction"].asString();
        string comment = (*insts)[i]["comment"].asString();
        INSADDR inst_addr = strtol((*insts)[i]["address"].asCString(), NULL, 16);
        if (comment.length() > 1 && replace)
        {
          replaceLabel(inst, comment);
        }
        rb[inst_addr] = inst;
      }
      (*code)[start] = rb;
    }
  }

  bool aarch64Asm::isNop(string &mnemonic) {
    if (mnemonic == "nop")
      return true;
    return false;
  }

  void aarch64Asm::printRawCode(string &function) {
    RAWFUNC code;
    cout << function << ": " << endl;
    extractRawCode(function, &code);
    for (auto it: code)
    {
      cout << "Block: " << it.first << endl;
      for(auto bt: it.second) {
        cout << bt.first << ": " << bt.second << endl;
      }
      cout << endl;
    }
  }

  void aarch64Asm::getFormattedCode(string &function, FUNCTION *code) {
    RAWFUNC raw_code;
    extractRawCode(function, &raw_code);
    for (auto bt: raw_code)
    {
      BLOCK_ADDR blk_start = bt.first;
      BLOCK blk;
      for (auto it : bt.second)
      {
        INSTRUCTION inst;
        parseRawInstruction(it.second, &inst);
        blk[it.first] = inst;
      }
      removeJmp(blk);
      removeCsel(blk);
      (*code)[blk_start] = blk;
      
    }
    removeNop(code);
    buildParam(code);
    fixReturnValue(code);
  }

  void aarch64Asm::removeNop(FUNCTION *code) {
    for (FUNCTION::iterator bit = code->begin(); bit != code->end(); ++bit)
    {
      for (BLOCK::iterator it = bit->second.begin(); it != bit->second.end(); ++it)
      {
        if (isNop(it->second.mnemonic))
        {
          it->second.visiable = false;
        }
        }
    }
  }

  void aarch64Asm::PrettyPrintCode(FUNCTION &code) {
    for (FUNCTION::iterator bit = code.begin(); bit != code.end(); ++bit) {
      cout << "Block: " << bit->first << endl;
      PrettyPrintBlock(bit->second);
      cout << endl;
    }
  }

  void aarch64Asm::PrettyPrintBlock (map<INSADDR, INSTRUCTION> &code) {
    for (map<INSADDR, INSTRUCTION>::iterator it = code.begin(); it != code.end(); ++it)
    {
      if (!it->second.visiable)
        continue;
      cout << it->first << "\t";
      PrettyPrintInstruction(it->second);
    }
  }

  void aarch64Asm::PrettyPrintInstruction (INSTRUCTION &inst){
    // cout << "Mnemonic: " << inst.mnemonic << endl;
    // cout << "Destination: " << inst.destination.content << endl;
    cout << inst.mnemonic << "\t";
    PrettyPrintOperand(inst.destination);
    for (vector<OPERAND>::iterator it = inst.source.begin(); it != inst.source.end(); ++it)
    {
      // cout << "Source: " << endl;
      PrettyPrintOperand(*it);
    }
    cout << "\n";
  }

  void aarch64Asm::PrettyPrintOperand (OPERAND &op) {
    int type = op.type;
    // cout << "(" << op.content << ")";
    switch (type)
    {
    case VARIABLE:
      cout << getRegisterName(op.operand.var.base.reg) << "_" << op.operand.var.base.index << "+" << op.operand.var.offset;
      // cout << op.content << endl;
      // cout << "\tType: VARIABLE" << endl;
      // cout << "\tBase: " << getRegisterName(op.operand.var.base.reg) << "_" << op.operand.var.base.index << endl;
      // cout << "\tOffset: " << op.operand.var.offset << endl;
      break;
    case IMMEDIATE:
      // cout << op.content << endl;
      // cout << "\tType: IMMEDIATE" << endl;
      // cout << "\tImm: " << op.operand.imm << endl;
      cout << op.operand.imm;
      break;
    case REGISTER:
      // cout << op.content << endl;
      // cout << "\tType: REGISTER" << endl;
      // cout << "\tReg: " << getRegisterName(op.operand.reg.reg) << "_" << op.operand.reg.index << endl;
      cout << getRegisterName(op.operand.reg.reg) << "_" << op.operand.reg.index;
      break;
    case LABEL:
      cout << op.content;
      // cout << "\tType: LABEL" << endl;
      // cout << "\tLabel: " << op.operand.imm << endl;
      // cout << op.operand.imm;
      break;
    default:
      break;
    }
    cout << ", ";
  }

  void aarch64Asm::memoryLocalize(BLOCK &code) {
    map<ADDR, int> tmp;
    for (map<INSADDR, INSTRUCTION>::iterator it = code.begin(); it != code.end(); ++it){
      if(it->second.destination.type == VARIABLE){
        if(tmp.find(it->second.destination.operand.var) == tmp.end()){
          tmp[it->second.destination.operand.var] = 0;
        }
      }
    }
    for (map<INSADDR, INSTRUCTION>::iterator it = code.begin(); it != code.end(); ++it) {
      INSTRUCTION *inst = &(it->second);
      for (vector<OPERAND>::iterator ot = inst->source.begin(); ot != inst->source.end();++ot){
        if(ot->type == VARIABLE) {
          ot->content = ot->content + "_" + to_string(tmp[ot->operand.var]);
        }
      }
      if(inst->destination.type == VARIABLE){
        tmp[inst->destination.operand.var] += 1;
        inst->destination.content = inst->destination.content + "_" + to_string(tmp[inst->destination.operand.var]);
      }
    }
  }

  void aarch64Asm::registerLocalize(string &function, BLOCK &code) {
    map<AArch64Reg, INDEX> tmp;
    for (int i = X0; i != UNK; i++)
      tmp[(AArch64Reg) i] = 0;
    for (map<INSADDR, INSTRUCTION>::iterator it = code.begin(); it != code.end(); ++it)
    {
      INSTRUCTION *inst = &(it->second);
      for (vector<OPERAND>::iterator ot = (*inst).source.begin(); ot != (*inst).source.end(); ++ot){
        if ((*ot).type == REGISTER) {
          (*ot).operand.reg.index = tmp[(*ot).operand.reg.reg];
          ot->content = ot->content + "_" + to_string(tmp[(*ot).operand.reg.reg]);
          #ifdef DEBUG
          cout << it->first << "->" << it->second.mnemonic << "->" << ot->content << endl;
          #endif
        }
        if ((*ot).type == VARIABLE) {
          (*ot).operand.var.base.index = tmp[(*ot).operand.var.base.reg];
          ot->content = ot->content + "_" + to_string(tmp[(*ot).operand.var.base.reg]);
        }
      }
      if ((*inst).destination.type == REGISTER)
      {
        tmp[(*inst).destination.operand.reg.reg] += 1;
        (*inst).destination.operand.reg.index = tmp[(*inst).destination.operand.reg.reg];
        inst->destination.content = inst->destination.content + "_" + to_string(tmp[(*inst).destination.operand.reg.reg]);
        #ifdef DEBUG
        cout << it->first << " -> " << inst->mnemonic << " -> " << inst->destination.content << endl;
        #endif
      }
      if ((*inst).destination.type == VARIABLE) {
        (*inst).destination.operand.var.base.index = tmp[(*inst).destination.operand.var.base.reg];
        inst->destination.content = inst->destination.content + "_" + to_string(tmp[(*inst).destination.operand.var.base.reg]);
      }
    }
  }

  bool aarch64Asm::dataTransferInstruction (string &mnemonic) {
    options::aarch64::PASSES p;
    p.store = false;
    bool flag = options::aarch64::removeInst(p, mnemonic);
    return flag;
  }

  /* 
   * code is map after registerLocalize.
   */
  void aarch64Asm::localVariableMap(BLOCK &code, map<OPERAND, OPERAND> &localVar) {
    for (map<INSADDR, INSTRUCTION>::iterator it = code.begin(); it != code.end(); ++it) {
      if (dataTransferInstruction(it->second.mnemonic)) {
        localVar[it->second.destination] = it->second.source[0];
        it->second.visiable = false;
      }
    }
    #ifdef DEBUG
    for (auto it: localVar) {
      cout << it.first.content << "<-" << it.second.content << endl;
    }
    #endif
  }

  void aarch64Asm::rootMap (map<OPERAND, OPERAND> &localVar) {
    for (map<OPERAND, OPERAND>::iterator it = localVar.begin(); it != localVar.end(); ++it) {
      while(true) {
        if (localVar.find(it->second) != localVar.end()) {
          it->second = localVar[it->second];
        } else {
          break;
        }
      }
    }
    #ifdef DEBUG
    for (map<OPERAND, OPERAND>::iterator it = localVar.begin(); it != localVar.end(); ++it){
      PrettyPrintOperand((OPERAND &)it->first);
      PrettyPrintOperand(it->second);
      cout << endl;
    }
    #endif
  }

  void aarch64Asm::removeDataTransfer(string &function, BLOCK &code) {
    map<OPERAND, OPERAND> localVar;
    localVariableMap(code, localVar);
    rootMap(localVar);
    for (BLOCK::iterator it = code.begin(); it != code.end(); ++it)
    {
      if(!it->second.visiable)
        continue;
      #ifdef DEBUG
      cout << "Before: "<< it->first << " -> " << it->second.mnemonic << " -> " << it->second.destination.content << endl;
      #endif
      // if (localVar.find(it->second.destination) != localVar.end())
      // {
      //   it->second.destination = localVar[it->second.destination];
      // }
      #ifdef DEBUG
      cout << "After: "<< it->first << " -> " << it->second.mnemonic << " -> " << it->second.destination.content << endl;
      #endif

      for (vector<OPERAND>::iterator ot = it->second.source.begin(); ot != it->second.source.end(); ot++)
      {
        if (localVar.find(*ot) != localVar.end()) {
          #ifdef DEBUG
          cout << "Source: " << it->first << " -> " << it->second.mnemonic << " -> " << ot->content << ":" << localVar[*ot].content<< endl;
          #endif
          #undef DEBUG
          (*ot) = localVar[*ot];
          #ifdef DEBUG
          cout << "Source: " << it->first << " -> " << it->second.mnemonic << " -> " << ot->content << endl;
          #endif
        }
      }
      #ifdef DEBUG
      cout << "Replace: "<< it->first << " -> " << it->second.mnemonic << " -> " << it->second.destination.content << endl;
      #endif
    }
    removeStore(code);
  }

  /* simple parameters recognize */
  void aarch64Asm::buildParam(FUNCTION *code) {
    for (FUNCTION::iterator bit = code->begin(); bit != code->end(); ++bit)
    {
      map<AArch64Reg, OPERAND> stack;
      BLOCK *blk = &(bit->second);
      BLOCK::iterator tmp = blk->end();
      for (BLOCK::iterator it = blk->begin(); it != blk->end(); ++it)
      {
        int reg_cnt = 0;
        #ifdef DEBUG
        cout << it->first << ": " << it->second.mnemonic << " ";
        #endif
        if (isCall(it->second.mnemonic))
        {
          for (auto op : stack){
            it->second.source.push_back(op.second);
          }
          stack.clear();
        }
        else
        {
          if (it->second.destination.operand.reg.reg >= X0 && it->second.destination.operand.reg.reg <= X7)
          {
            if(it->second.mnemonic == "mov"){
              stack[it->second.destination.operand.reg.reg] = it->second.destination;
            } else if(it->second.mnemonic == "add" && it->second.source[0].content == "sp") {
              stack[it->second.destination.operand.reg.reg] = it->second.source[0] + it->second.source[1];
              it->second.visiable = false;
            } else {
              stack[it->second.destination.operand.reg.reg] = it->second.destination;
            }
          }
        }
      }
    }
  }

  void aarch64Asm::fixReturnValue(FUNCTION *code) {
    for (FUNCTION::iterator bit = code->begin(); bit != code->end(); ++bit){
      BLOCK *blk = &(bit->second);
      for (map<INSADDR, INSTRUCTION>::iterator it = blk->begin(); it != blk->end(); ++it)
      {
        if (isCall(it->second.mnemonic))
        {
          vector<OPERAND> s;
          for (auto op : it->second.source)
          {
            if (op.type == VARIABLE)
            {
              it->second.destination = op;
            } else {
            s.push_back(op);
          }
        }
        it->second.source = s;
      }
    }
    }
  }

  void aarch64Asm::destinationAnalyze(BLOCK &code, map<OPERAND, deque<INSADDR>> &destTable) {
    for (BLOCK::iterator it = code.begin(); it != code.end();++it){
      if(!it->second.visiable){
        continue;
      }
      if(it->second.destination.content == "void"){
        continue;
      }
      if(destTable.find(it->second.destination)!=destTable.end()){
        destTable[it->second.destination].push_back(it->first);
      } else {
        deque<INSADDR> v;
        v.push_back(it->first);
        // cout <<it->first << ": " << it->second.destination.content << endl;
        destTable[it->second.destination] = v;
      }
    }
    #ifdef DEBUG
    for (map<OPERAND, deque<INSADDR>>::iterator it = destTable.begin(); it != destTable.end(); ++it) {
      // PrettyPrintOperand((OPERAND&)(it->first));
      cout << it->first.content << ": ";
      for (deque<INSADDR>::iterator dt = it->second.begin(); dt != it->second.end(); ++dt)
      {
        cout << *dt << " ";
      }
      cout << endl;
    }
    #endif
  }

  void aarch64Asm::getPre(deque<INSADDR> &v, INSADDR addr) {
    int cnt = 0;
    for (auto it : v)
    {
      if (addr > it){
        cnt++;
      }
      else {
        break;
      }
    }
    cnt--;
    for (int i = 0; i < cnt;i++){
      v.pop_front();
    }
  }

  void aarch64Asm::buildDDG(FUNCTION &code, GRAPH &ddg) {
    for (FUNCTION::iterator bit = code.begin(); bit != code.end(); ++bit){
      BLKGRAPH blk_graph;
      BLOCK blk = bit->second;
      BLOCK_ADDR blk_start = bit->first;
      map<OPERAND, deque<INSADDR>> destTable;
      destinationAnalyze(blk, destTable);
      map<INSADDR, INDEX> index;
      int cnt = 0;
      for (map<INSADDR, INSTRUCTION>::iterator it = blk.begin(); it != blk.end(); ++it)
      {
        if (!it->second.visiable) {
          continue;
        }
        NODE inst;
        inst.address = it->first;
        blk_graph.g.push_back(inst);
        index[it->first] = cnt;
        cnt++;
      }
      for (vector<NODE>::iterator it = blk_graph.g.begin(); it != blk_graph.g.end(); ++it){
        INSTRUCTION inst = blk[it->address];
        #ifdef DEBUG
          PrettyPrintInstruction(inst);
        #endif
        if (!inst.visiable)
          continue;
        for (vector<OPERAND>::iterator ot = inst.source.begin(); ot != inst.source.end(); ++ot)
        {
          #ifdef DEBUG
            cout << ot->content;
            
            cout << endl;
          #endif
          if (destTable.find(*ot) != destTable.end())
          {
            
            getPre(destTable[*ot], it->address);
            INSADDR destAddr = destTable[*ot][0];
            INDEX idx = index[destAddr];
            it->pre.push_back(idx);
          }
          else
          {
            it->pre.push_back(-1);
          }
        }
      }
      cnt = 0;
      for (vector<NODE>::iterator it = blk_graph.g.begin(); it != blk_graph.g.end(); ++it)
      {
        for (vector<INDEX>::iterator ot = it->pre.begin(); ot != it->pre.end(); ++ot){
          if(*ot == -1)
            continue;
          INSADDR destAddr = blk_graph.g[*ot].address;
          INDEX idx = index[destAddr];
          blk_graph.g[idx].post.push_back(cnt);
        }
        cnt++;
      }
      ddg[blk_start] = blk_graph;
    }
  }

  void aarch64Asm::findAllExits (GRAPH &ddg){
    int cnt = 0;
    for (GRAPH::iterator bit = ddg.begin(); bit != ddg.end(); ++bit) {
      for (vector<NODE>::iterator it = bit->second.g.begin(); it != bit->second.g.end(); ++it)
      {
        if (it->post.size() == 0)
        {
          bit->second.roots.push_back(cnt);
        }
        cnt++;
      }
    }
  }

  void aarch64Asm::DDAnalyze(string &function, FUNCTION &code, GRAPH &ddg){
    getFormattedCode(function, &code);
    for (FUNCTION::iterator bit = code.begin(); bit != code.end(); ++bit) {
      registerLocalize(function, bit->second);
#ifdef DEBUG
      cout << "After registerLocallize:" << endl;
      PrettyPrintCode(code);
      cout << endl;
#endif
      memoryLocalize(bit->second);
#ifdef DEBUG
      cout << "After memoryLocallize:" << endl;
      PrettyPrintCode(code);
      cout << endl;
#endif
      removeDataTransfer(function, bit->second);
#ifdef DEBUG
      cout << "After removeDataTransfer:" << endl;
      PrettyPrintCode(bit->second);
      cout << endl;
#endif
      renameOperands(bit->second);
    }
    removeFunctionPreface(code);
    removeFunctionEpilogue(code);
    removeADRP(code);
    buildDDG(code, ddg);
    findAllExits(ddg);
  }

  void aarch64Asm::PrettyPrintGraph(vector<NODE> &g, BLOCK &code) {
    for (vector<NODE>::iterator it = g.begin(); it != g.end(); ++it) {
      cout << it->address << ":\t";
      // PrettyPrintOperand(code[it->address].destination);
      cout << "Pre: ";
      for (auto ot : it->pre)
      {
        if (ot != -1){
          cout << g[ot].address <<" ";
        }
      }
      cout << "\tPost: ";
      for (auto ot : it->post)
      {
        if(ot == -1)
          continue;
        cout << g[ot].address << " ";
      }
      cout << endl;
    }
  }

  void aarch64Asm::PrettyPrintExits(BLKGRAPH &ddg){
    for(auto it: ddg.roots){
      cout << ddg.g[it].address << ", ";
    }
  }

  void aarch64Asm::PrettyPrintDDG(FUNCTION &code, GRAPH &ddg) {
    for(FUNCTION::iterator bit = code.begin(); bit!= code.end(); ++bit) {
      cout << "Block" << bit->first << ":" << endl;
      cout << "Instructions: " << endl;
      PrettyPrintBlock(bit->second);
      cout << endl;
      cout << "Edges: " << endl;
      PrettyPrintGraph(ddg[bit->first].g, bit->second);
      cout << endl;
      cout << "Exits: " << endl;
      PrettyPrintExits(ddg[bit->first]);
      cout << endl;
    }
  }

  void aarch64Asm::getStoreTable(map<OPERAND, pair<OPERAND, INSADDR>> &storeTable, BLOCK &code) {
    for (BLOCK::iterator it = code.begin(); it != code.end(); it++){
      if(isStore(it->second.mnemonic)) {
        if (it->second.source.size() == 1) {
          pair<OPERAND, INSADDR> p(it->second.destination, it->first);
          storeTable[it->second.source[0]] = p;
        }
      }
    }
  }

  void aarch64Asm::removeStore(BLOCK &code) {
    map<OPERAND, pair<OPERAND, INSADDR>> storeTable;
    getStoreTable(storeTable, code);
    for (BLOCK::reverse_iterator it = code.rbegin(); it != code.rend(); ++it)
    {
      if(storeTable.find(it->second.destination)!=storeTable.end() && it->second.visiable && !isStore(it->second.mnemonic)){
        if(storeTable[it->second.destination].second > it->first){
          code[storeTable[it->second.destination].second].visiable = false;
          it->second.destination = storeTable[it->second.destination].first;
        }
      }
    }
  }

  void aarch64Asm::colorLeftNodes (BLKGRAPH &ddg, vector<INDEX> &nodes) {
    for (vector<INDEX>::iterator it = nodes.begin(); it != nodes.end(); ++it){
        INDEX root = *it;
        stack<INDEX> s;
        if(root == -1)
          continue;
        while (root != -1  || !s.empty())
        {
          for(auto node : ddg.g[root].pre){
            if(node == -1)
              continue;
            if (ddg.g[node].color == -1)
              s.push(node);
          }
          if(!s.empty()){
            root = s.top();
            ddg.g[root].color = ddg.g[*it].color;
            s.pop();
          } else {
            root = -1;
          }
        }
      }
  }

  void aarch64Asm::getColored(GRAPH &ddg) {
    for (GRAPH::iterator bit = ddg.begin(); bit != ddg.end(); ++bit) {
      COLOR c = 0;
      vector<INDEX> nodes;
      int cnt = 0;
      for (vector<NODE>::iterator it = bit->second.g.begin(); it != bit->second.g.end(); ++it)
      {
        #ifdef DEBUG
        cout << it->address << ":" << it->post.size() << "\n";
        #endif
        if (it->post.size() > 1 || it->post.size() == 0)
        {
          it->color = c;
          nodes.push_back(cnt);
          c++;
        }
        cnt++;
      }
      colorLeftNodes(bit->second, nodes);
      bit->second.all_colors = c;
      getColorField(bit->second);
    }
  }

  void aarch64Asm::getColorField(BLKGRAPH &ddg) {
    int cnt = 0;
    for (auto n : ddg.g) 
    {
      ddg.colors[n.color].push_back(cnt);
      cnt++;
    }
  }

  void aarch64Asm::PrettyPrintColor(GRAPH &ddg) {
    for (GRAPH::iterator bit = ddg.begin(); bit != ddg.end(); ++bit){
      cout << "Block: " << bit->first << endl;
      for (COLOR c = 0; c < bit->second.all_colors; c++)
      {
        cout << "Color" << c << ": ";
        for (auto n : bit->second.colors[c])
        {
          cout << bit->second.g[n].address << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
  }

  void aarch64Asm::removeFunctionPreface (FUNCTION &code) {
    BLOCK * blk = &(code.begin()->second);
    int cnt = blk->size();
    for (BLOCK::reverse_iterator it = blk->rbegin(); it != blk->rend(); ++it)
    {
      if (it->second.mnemonic == "stp") {
        break;
      }
      cnt--;
    }
    for (BLOCK::iterator it = blk->begin(); it != blk->end(); ++it)
    {
      it->second.visiable = false;
      if (cnt-- == 0)
        break;
    }
  }

  void aarch64Asm::removeFunctionEpilogue (FUNCTION &code) {
    BLOCK * blk = &(code.end()->second);
    int cnt = 0;
    for (BLOCK::reverse_iterator it = blk->rbegin(); it != blk->rend(); ++it)
    {
      if(cnt == 1 && it->second.mnemonic == "ldr"){
        it->second.visiable = false;
      }
      else if(cnt > 1 && it->second.mnemonic == "ldp"){
        it->second.visiable = false;
      }
      else if(cnt == 1 && it->second.mnemonic == "add"){
        it->second.visiable = false;
      }
      cnt++;
    }
  }

  void aarch64Asm::removeADRP (FUNCTION &code) {
    for (FUNCTION::iterator bit = code.begin(); bit != code.end(); ++bit){
      for (BLOCK::iterator it = bit->second.begin(); it != bit->second.end(); ++it)
      {
        if (it->second.mnemonic == "adrp")
        {
          it->second.visiable = false;
          (++it)->second.visiable = false;
        }
        if (it->second.mnemonic == "adrl")
        {
          it->second.visiable = false;
        }
        if (it->second.mnemonic == "adr")
        {
          it->second.visiable = false;
        }
      }
    }
  }


  void aarch64Asm::colorOfdivOpt(map<INSADDR, INSTRUCTION> &code, GRAPH &ddg) {
    
  }

  void aarch64Asm::removeCsel(BLOCK &ins) {
    for (BLOCK::iterator it = ins.begin(); it != ins.end(); ++it){
      if (it->second.mnemonic == "csel"){
        it->second.visiable = false;
      }
    }
  }

  void aarch64Asm::removeJmp(BLOCK &ins) {
    vector<string> jmp_op = {"cbz", "cbnz", "tbz", "tbnz", "b.eq", "b.ge", "b.gt", "b.lt", "b.le", "b.ne", "b", "bl", "br", "blr", "ret", "cmp", "b.hi", "b.hs", "csel"};
    vector<string> one_jmp = {"cbz", "cbnz", "tbz", "tbnz"};
    vector<string> two_jmp = {"b.eq", "b.ge", "b.gt", "b.lt", "b.le", "b.ne", "b.hi", "b.hs"};
    vector<string> direct_jmp = {"b", "bl", "br", "blr", "ret"};

    // first label jmp operator directly
    for (auto it = jmp_op.begin(); it != jmp_op.end(); it++) {
        for (auto m_it = ins.rbegin(); m_it != ins.rend(); m_it++) {
            string op = m_it->second.mnemonic;
            if (op == *it) {
                m_it->second.visiable = false;
            }
        }
    }
    
    // then label util instruction based on last operator
    vector<string> v_one = {"cmp", "cset", "csel"};
    vector<string> v_two = {"cmp", "csel"};
    vector<string> v_direct = {"csel"};

    string last_ins = (--(ins.end()))->second.mnemonic;
    string last_op = last_ins;

    vector<string> v;
    if (std::count(one_jmp.begin(), one_jmp.end(),  last_op )) {
        v = v_one;
    } else if (std::count(two_jmp.begin(), two_jmp.end(),  last_op )) {
        v = v_two;
    } else if (std::count(direct_jmp.begin(), direct_jmp.end(),  last_op )) {
        v = v_direct;
    } else {
        return;
    }

    for (auto it = v.begin(); it != v.end(); it++) {
        for (auto m_it = ins.rbegin(); m_it != ins.rend(); m_it++) {
            string op = m_it->second.mnemonic;
            if (op == *it) {
                m_it->second.visiable = false;
                break;
            }
        }
    }

    return;    
  
  }

  void aarch64Asm::renameOperands(BLOCK &code) {
    map<string, int> names;
    int cnt = 0;
    for (BLOCK::iterator it = code.begin(); it != code.end(); ++it)
    {
      if (!it->second.visiable)
        continue;
      if(names.find(it->second.destination.content) == names.end()) {
        names[it->second.destination.content] = cnt;
        cnt++;
      }
      for (vector<OPERAND>::iterator ot = it->second.source.begin(); ot != it->second.source.end(); ++ot){
        if (names.find(ot->content) == names.end()){
          names[ot->content] = cnt;
          cnt++;
        }
      }
    }

    for (BLOCK::iterator it = code.begin(); it != code.end(); ++it)
    {
      if (!it->second.visiable)
        continue;
      if(names.find(it->second.destination.content) != names.end()) {
        it->second.destination.alias = names[it->second.destination.content];
      }
      for (vector<OPERAND>::iterator ot = it->second.source.begin(); ot != it->second.source.end(); ++ot){
        if (names.find(ot->content) != names.end()){
          ot->alias = names[ot->content];
        }
      }
    }
  }

}
}