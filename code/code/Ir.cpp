#include <regex>
#include "Ir.h"
using namespace std;
namespace code
{
  namespace ir
  {
    void Ir::init()
    {
      int function_size = root["functions"].size();
      // std::cout << function_size << std::endl;
      for (int i = 0; i < function_size; i++)
      {
        int bb_size = root["functions"][i]["basicblocks"].size();
        std::string function_name = root["functions"][i]["function"].asString();
        // std::cout << function_name << std::endl;
        functions[function_name] = &root["functions"][i]["basicblocks"];
      }
    }

    void Ir::getOpcodeSequence(std::string &function, std::vector<std::string> &s)
    {
      Json::Value *bbs = functions[function];
      int bbs_size = bbs->size();
      for (int i = 0; i < bbs_size; i++)
      {
        Json::Value insts = bbs[i]["instructions"];
        int instructions_size = insts.size();
        for (int j = 0; j < instructions_size; j++)
        {
          s.push_back(insts[j]["opcode"].asString());
        }
      }
    }

    void Ir::getRemovedOpcodeSequence(std::string &function, options::IR::PASSES passes, std::vector<std::string> &s)
    {
      Json::Value bbs = *functions[function];
      int bbs_size = bbs.size();
      for (int i = 0; i < bbs_size; i++)
      {
        Json::Value insts = bbs[i]["instructions"];
        int instructions_size = insts.size();
        // std::cout << instructions_size << std::endl;
        for (int j = 0; j < instructions_size; j++)
        {
          std::string opcode = insts[j]["opcode"].asString();
          // std::cout << opcode << std::endl;
          if (!options::IR::removeInst(passes, opcode))
          {
            // std::cout << opcode << std::endl;
            s.push_back(opcode);
          }
        }
      }
    }

    void Ir::getFunctionsName(std::vector<std::string> &FunctionNames)
    {
      for (std::map<std::string, Json::Value *>::iterator it = functions.begin(); it != functions.end(); ++it)
        FunctionNames.push_back(it->first);
    }

    void Ir::buildVarTable(Json::Value &bbs, std::map<std::string, int> &varTable) {
      int bbs_size = bbs.size();
      int cnt = 0;
      for (int i = 0; i < bbs_size; i++)
      {
        Json::Value insts = bbs[i]["instructions"];
        int instructions_size = insts.size();
        for (int j = 0; j < instructions_size; j++)
        {
          Json::Value inst = insts[j];
          // dest
          if (varTable.find(inst["return"]["value"].asString()) == varTable.end()) {
            varTable[inst["return"]["value"].asString()] = cnt;
            cnt++;
          }
          //source
          int src_size = inst["operands"].size();
          for (int k = 0; k < src_size;k++){
            Json::Value op = inst["operands"][k];
            if (varTable.find(op["value"].asString())==varTable.end()) {
              varTable[op["value"].asString()] = cnt;
              cnt++;
            }
          }
        }
      }
    }

    bool Ir::isCall(string &opcode) {
      if(opcode == "call")
        return true;
      return false;
    }

    void Ir::extractRawCode(string &function, CODE &code){
      Json::Value bbs = *(functions[function]);
      std::map<std::string, int> varTable;
      buildVarTable(bbs, varTable);
      int bbs_size = bbs.size();
      int cnt = 0;
      for (int i = 0; i < bbs_size; i++)
      {
        Json::Value insts = bbs[i]["instructions"];
        int instructions_size = insts.size();
        BB bb;
        string bb_label = bbs[i]["basicblock"].asString();
        for (int j = 0; j < instructions_size; j++)
        {
          INSTRUCTION inst;
          Json::Value ins = insts[j];
          inst.mnemonic = ins["opcode"].asString();
          std::vector<OPERAND> sources;
          int src_size = ins["operands"].size();
          for (int k = 0; k < src_size; k++){
            Json::Value src = ins["operands"][k];
            OPERAND s;
            s.type = src["type"].asString();
            s.value = varTable[src["value"].asString()];
            s.content = src["value"].asString();
            if (s.type == "void")
              s.content = "void";
            sources.push_back(s);
          }
          if(ins["return"]["type"].asString() != "void" || isCall(inst.mnemonic)){
            OPERAND dest;
            dest.type = ins["return"]["type"].asString();
            dest.value = varTable[ins["return"]["value"].asString()];
            dest.content = ins["return"]["value"].asString();
            if (dest.type == "void")
              dest.content = "void";
            inst.dest = dest;
            inst.sources = sources;
          } else {
            if(isStore(inst.mnemonic)){
              inst.dest = sources[sources.size() - 1];
              sources.pop_back();
              inst.sources = sources;
            } else {
              inst.sources = sources;
              OPERAND dest;
              dest.type = "void";
              dest.value = -1;
              dest.content = "void";
              inst.dest = dest;
            }
          }
          bb[cnt] = inst;
          cnt++;
        }
        code[bb_label] = bb;
      }
    }

    void Ir::PrettyPrintCode(CODE &code){
      for (map<string, BB>::iterator it = code.begin(); it != code.end(); ++it){
        cout << it->first << ":\n";
        PrettyPrintBB(it->second);
      }
    }

    void Ir::PrettyPrintBB(BB &bb){
      for (map<int, INSTRUCTION>::iterator it = bb.begin(); it != bb.end(); ++it){
        if(!(it->second.visiable))
          continue;
        cout << it->first << ":\t";
        PrettyPrintInstruction(it->second);
        cout << endl;
      }
    }

    void Ir::PrettyPrintInstruction(INSTRUCTION &inst)
    {
      cout << inst.mnemonic << "\t";
      PrettyPrintOperand(inst.dest);
      cout << "\t";
      for (vector<OPERAND>::iterator it = inst.sources.begin(); it != inst.sources.end(); ++it){
        PrettyPrintOperand(*it);
      }
    }

    void Ir::PrettyPrintOperand(OPERAND &op){
      if(op.type != "void") {
        cout << "(" << op.content << ")";
        cout << "%" << op.value;
        cout << ", ";
      }
    }

    void Ir::getFormattedCode(string &function, CODE &code)
    {
      extractRawCode(function, code);
      removeAlloca(code);
      removeLoad(code);
      removeStore(code);
    }

    bool Ir::isReturn (string &opcode){
      if (opcode == "ret")
        return true;
      return false;
    }

    bool Ir::isLoad (string &opcode){
      options::IR::PASSES p;
      p.alloca = false;
      p.store = false;
      return options::IR::removeInst(p, opcode);
    }
     
    bool Ir::isStore (string &opcode){
      options::IR::PASSES passes;
      passes.alloca = false;
      passes.load = false;
      return options::IR::removeInst(passes, opcode);
    }

    bool Ir::isAlloca (string &opcode){
      options::IR::PASSES passes;
      passes.load = false;
      passes.store = false;
      return options::IR::removeInst(passes, opcode);
    }

    void Ir::getLoadTable(CODE &code, map<OPERAND, OPERAND> &loadTable) {
      for (CODE::iterator it = code.begin(); it != code.end(); ++it){
        for (BB::iterator bt = it->second.begin(); bt != it->second.end();++bt){
          if(isLoad(bt->second.mnemonic)){
            loadTable[bt->second.dest] = bt->second.sources[0];
            bt->second.visiable = false;
          }
        }
      }
    }

    void Ir::removeAlloca(CODE &code){
      for (CODE::iterator it = code.begin(); it != code.end(); ++it){
        for (BB::iterator bt = it->second.begin(); bt != it->second.end();++bt){
          if(!bt->second.visiable)
            continue;
          if (isAlloca(bt->second.mnemonic))
          {
            bt->second.visiable = false;
          }
        }
      }
    }

    void Ir::removeLoad(CODE &code)
    {
      map<OPERAND, OPERAND> loadTable;
      getLoadTable(code, loadTable);
      for (CODE::iterator it = code.begin(); it != code.end(); ++it){
        for (BB::iterator bt = it->second.begin(); bt != it->second.end();++bt){
          if(!bt->second.visiable)
            continue;
          for (vector<OPERAND>::iterator ot = bt->second.sources.begin(); ot != bt->second.sources.end(); ++ot)
          {
            if(loadTable.find(*ot) != loadTable.end()){
              (*ot) = loadTable[*ot];
            }
          }
        }
      }
    }

    void Ir::getStoreTable(CODE &code, map<OPERAND, tuple<OPERAND, int, string>> &storeTable){
      for (CODE::iterator it = code.begin(); it != code.end(); ++it){
        for (BB::iterator bt = it->second.begin(); bt != it->second.end(); ++bt){
          if(isStore(bt->second.mnemonic)){
            tuple<OPERAND, int, string> p(bt->second.dest, bt->first, it->first);
            storeTable[bt->second.sources[0]] = p;
            // bt->second.visiable = false;
          }
        }
      }
    }

    void Ir::removeStore(CODE &code)
    {
      map<OPERAND, tuple<OPERAND, int, string>> storeTable;
      getStoreTable(code, storeTable);
      for (CODE::iterator it = code.begin(); it != code.end(); ++it){
        for (BB::reverse_iterator bt = it->second.rbegin(); bt != it->second.rend(); ++bt){
          if(!bt->second.visiable)
            continue;
          if(storeTable.find(bt->second.dest) != storeTable.end() && !isStore(bt->second.mnemonic)) {
            if(get<1>(storeTable[bt->second.dest]) > bt->first){
              code[get<2>(storeTable[bt->second.dest])][get<1>(storeTable[bt->second.dest])].visiable = false;
              bt->second.dest = get<0>(storeTable[bt->second.dest]);
            }
          }
        }
      }
    }

    void Ir::getDestTable(CODE &code, map<OPERAND, deque<POS>> &destTable) {
      for (CODE::iterator it = code.begin(); it != code.end(); ++it)
      {
        for (BB::iterator bt = it->second.begin(); bt != it->second.end(); ++bt){
          if(!bt->second.visiable)
            continue;
          if(bt->second.dest.type != "void") {
            POS p = {it->first, bt->first};
            destTable[bt->second.dest].push_back(p);
          }
        }
      }
      // for (auto it : destTable){
      //   PrettyPrintOperand((OPERAND&)it.first);
      //   cout << "\t";
      //   for (auto at : it.second){
      //     cout << at.index << " ";
      //   }
      //   cout << endl;
      // }
    }

    void Ir::getPre(deque<POS> &v, int addr){
      // TODO: 增加判断基本块的关系，当前只有一个基本块所以只考虑地址就可以
      int cnt = 0;
      for(auto it:v){
        if(addr > it.index){
          cnt++;
        } else {
          break;
        }
      }
      cnt--;
      for (int i = 0; i < cnt;i++){
        v.pop_front();
      }
    }

    void Ir::buildDDG (CODE &code, GRAPH &ddg){
      map<OPERAND, deque<POS>> destTable;
      getDestTable(code, destTable);
      map<string, pair<int, map<int, int>>> block_index; // 索引基本块在graph中的位置
      /*Step1: 首先对每一条指令，初始化图中所有的NODE节点*/
      int blk_cnt = 0; // blk在图中的索引
      for (CODE::iterator it = code.begin(); it != code.end(); ++it)
      {
        BLOCK blk;
        int cnt = 0;
        map<int, int> in_block_index;
        for (BB::iterator bt = it->second.begin(); bt != it->second.end(); ++bt)
        {
          if(!bt->second.visiable)
            continue;
          NODE inst;
          inst.index = bt->first;
          blk.b.push_back(inst);
          in_block_index[bt->first] = cnt;
          cnt++;
        }
        blk.name = it->first;
        ddg.g.push_back(blk);
        block_index[it->first] = pair<int, map<int, int>>(blk_cnt, in_block_index);
        blk_cnt++;
      }
      // Step2: 对图中的每一个节点，对他的所有源操作数遍历，根据destTable，寻找他所依赖的指令。
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        string blk_name = it->name;
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt)
        {
          INSTRUCTION inst = code[blk_name][nt->index]; // 根据当前所在的块和index索引，得到code中存储的当前指令。
          /*扫描当前指令的源操作数*/
          debugPrint(inst.mnemonic);
          for (vector<OPERAND>::iterator ot = inst.sources.begin(); ot != inst.sources.end(); ++ot)
          {
            // 如果在destTable中找到，说明他依赖那一条指令。
            if (destTable.find(*ot)!=destTable.end())
            {
              debugPrint(to_string(destTable[*ot][0].index));
              getPre(destTable[*ot], nt->index);
              debugPrint(to_string(destTable[*ot][0].index));
              string name = destTable[*ot][0].block;
              int index_in_code = destTable[*ot][0].index;
              EDGE e;
              // 寻找被依赖的指令在图中的位置，利用blockIndex表
              e.block = block_index[name].first;
              e.index = block_index[name].second[index_in_code];
              debugPrint(to_string(e.index));
              nt->pre.push_back(e);
            } else {
              EDGE e = {-1, -1};
              nt->pre.push_back(e);
            }
          }
        }
      }
      /* 根据前驱边，构建后继边，遍历图中的每一条前驱边*/
      int i = 0;
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        int j = 0;
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt)
        {
          for (vector<EDGE>::iterator gt = nt->pre.begin(); gt != nt->pre.end(); ++gt){
            if (gt->block == -1 || gt->index == -1){
              continue;
            }
            // 目标节点在graph中的位置
            EDGE e = {i, j};
            ddg.g[gt->block].b[gt->index].post.push_back(e);
          }
          j++;
        }
        i++;
      }
    }

    void Ir::findAllExits (GRAPH &ddg) {
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        int cnt = 0;
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt)
        {
          if(nt->post.size() == 0) {
            it->roots.push_back(cnt);
          }
          cnt++;
        }
      }
    }

    void Ir::DDAnalyze(CODE &code, GRAPH &ddg)
    {
      buildDDG(code, ddg);
      findAllExits(ddg);
    }

    void Ir::PrettyPrintGraph(CODE &code, GRAPH &ddg) {
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt) {
          cout << nt->index << ":\t";
          cout << code[it->name][nt->index].mnemonic << "\t";
          // PrettyPrintOperand(code[it->name][nt->index].dest);
          // for (vector<EDGE>::iterator et = nt->pre.begin(); et != nt->pre.end(); ++et){
          //   if(et->block == -1 || et->index == -1){
          //     continue;
          //   }
            // string name = ddg.g[et->block].name;
            // int index = ddg.g[et->block].b[et->index].index;
            // cout << "(" << index << ")";
            // PrettyPrintOperand(code[name][index].dest);
          // }
          for (vector<EDGE>::iterator et = nt->post.begin(); et != nt->post.end(); ++et){
            if(et->block == -1 or et->index == -1)
              continue;
            cout << ddg.g[et->block].name << ":" << ddg.g[et->block].b[et->index].index << " ";
          }
          cout << endl;
        }
      }
    }
  
    void Ir::colorLeftNodes (GRAPH &ddg, std::vector<EDGE> &nodes) {
      for (vector<EDGE>::iterator it = nodes.begin(); it != nodes.end(); ++it){
        EDGE root = *it;
        stack<EDGE> s;
        if(it->block == -1 || it->index == -1)
          continue;
        while ((root.block != -1 && root.index != -1) || !s.empty())
        {
          for(auto node : ddg.g[root.block].b[root.index].pre){
            if(node.index == -1 || node.block == -1)
              continue;
            if (ddg.g[node.block].b[node.index].color == -1)
              s.push(node);
          }
          if(!s.empty()){
            root = s.top();
            ddg.g[root.block].b[root.index].color = ddg.g[it->block].b[it->index].color;
            s.pop();
          } else {
            root.block = -1;
            root.index = -1;
          }
        }
      }
    }

    void Ir::getColored(GRAPH &ddg){
      COLOR c = 0;
      int blk_idx = 0;
      vector<EDGE> nodes;
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        int inst_idx = 0;
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt)
        {
          if(nt->post.size() > 1 || nt->post.size() == 0) {
            nt->color = c;
            c++;
            EDGE e = {blk_idx, inst_idx};
            nodes.push_back(e);
          }
          inst_idx++;
        }
        blk_idx++;
      }
      ddg.all_colors = c;
      colorLeftNodes(ddg, nodes);
      getColorField(ddg);
    }

    void Ir::PrettyPrintColor(GRAPH &ddg) {
      for (COLOR c = 0; c < ddg.all_colors; c++){
        cout << "Color" << c << ": ";
        for (auto n : ddg.colors[c]){
          cout << ddg.g[n.block].b[n.index].index << " ";
        }
        cout << endl;
      }
    }

    void Ir::getColorField(GRAPH &ddg) {
      int bcnt = 0;
      for (vector<BLOCK>::iterator it = ddg.g.begin(); it != ddg.g.end(); ++it)
      {
        int cnt = 0;
        for (vector<NODE>::iterator nt = it->b.begin(); nt != it->b.end(); ++nt)
        {
          EDGE p = {bcnt, cnt};
          ddg.colors[nt->color].push_back(p);
          cnt++;
        }
        bcnt++;
      }
    }
  }
}
