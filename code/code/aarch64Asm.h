#include "code.h"
#include "../options/removeASM.h"
#include <string>
#include <regex>

#define INDEX int
#define INSADDR long unsigned int
// #define DEBUG

using namespace std;
namespace code
{
namespace aarch64{
enum AArch64Reg
{
  X0,
  X1,
  X2,
  X3,
  X4,
  X5,
  X6,
  X7,
  X8,
  X9,
  X10,
  X11,
  X12,
  X13,
  X14,
  X15,
  X16,
  X17,
  X18,
  X19,
  X20,
  X21,
  X22,
  X23,
  X24,
  X25,
  X26,
  X27,
  X28,
  X29,
  X30,
  SP,
  XZR,
  UNK
};

enum OperandType
{
  VARIABLE,
  REGISTER,
  LABEL,
  IMMEDIATE,
  UNKTYPE
};

typedef struct
{
  AArch64Reg reg;
  INDEX index;
} REG;

typedef struct ADDR{
  REG base;
  int offset;
  friend bool operator<(const struct ADDR &k1, const struct ADDR &k2);
} ADDR;
inline bool operator < (const struct ADDR &k1, const struct ADDR &k2) {
  return k1.base.reg < k2.base.reg || (k1.base.reg == k2.base.reg && k1.base.index < k2.base.index) || (k1.base.reg == k2.base.reg && k1.base.index && k2.base.index && k1.offset < k2.offset);
}


typedef union OP
{
  REG reg;
  int imm;
  ADDR var;
} OP;

typedef struct OPERAND{
  OperandType type = UNKTYPE;
  string content = "void";
  int alias = -1;
  OP operand;
  friend bool operator<(const struct OPERAND &k1, const struct OPERAND &k2);
  friend OPERAND operator+(const struct OPERAND &k1, const struct OPERAND &k2);
} OPERAND;

inline bool operator < (const struct OPERAND &k1, const struct OPERAND &k2) {
  
  return k1.content < k2.content;
}
inline OPERAND operator + (const struct OPERAND &k1, const struct OPERAND &k2) {
  OPERAND k;
  k.type = VARIABLE;
  OP op;
  ADDR addr;
  addr.base = k1.operand.reg;
  addr.offset = k2.operand.imm;
  op.var = addr;
  k.operand = op;
  k.content = k1.content+k2.content;
  return k;
}

typedef struct
{
  string mnemonic;
  OPERAND destination;
  vector<OPERAND> source;
  bool visiable = true;
} INSTRUCTION;

typedef map<INSADDR, INSTRUCTION> BLOCK;

typedef unsigned long int BLOCK_ADDR;

typedef map<BLOCK_ADDR, BLOCK> FUNCTION;

typedef struct
{
  INSADDR address;
  vector<INDEX> post; // ->
  vector<INDEX> pre;  // <-
  COLOR color = -1;
} NODE;

typedef struct{
  vector<NODE> g;
  vector<INDEX> roots;
  COLOR all_colors = 0;
  map<COLOR, vector<INDEX>> colors;
} GRAPH;

class aarch64Asm : public Code<options::aarch64::PASSES>
{
public:
  std::map<std::string, Json::Value *> functions;
public:
  aarch64Asm (std::string &filename)
    : Code(filename)
  {
    init();
  };
  ~aarch64Asm(){};
  void init() override;

  void getOpcodeSequence(std::string &function, std::vector<std::string> &s) override;

  void getRemovedOpcodeSequence(std::string &function, options::aarch64::PASSES passes, std::vector<std::string> &s) override;

  void getFunctionsName(std::vector<std::string> &FunctionNames) override;

  void getFormattedCode(std::string &function, std::map<INSADDR, INSTRUCTION> *code);
  void removeDataTransfer(std::string &function, map<INSADDR, INSTRUCTION> &code);
  void printRawCode(std::string &function);
  void PrettyPrintCode(map<INSADDR, INSTRUCTION> &code);

  void DDAnalyze(string &function, map<INSADDR, INSTRUCTION> &code, GRAPH &ddg);

  void PrettyPrintDDG(map<INSADDR, INSTRUCTION> &code, GRAPH &ddg);
  void getColored(GRAPH &ddg);
  void PrettyPrintColor(GRAPH &ddg);
  void PrettyPrintGraph(vector<NODE> &g, map<INSADDR, INSTRUCTION> &code);
  void getColorField(GRAPH &ddg);

  void getSorted(GRAPH &ddg);

private:
  void extractRawCode(std::string &function, std::map<INSADDR, std::string> *code, bool replace=true);

  bool parseRawInstruction(std::string &inst, std::vector<std::string> * res);

  void parseRawInstruction(std::string &inst, INSTRUCTION *instruction);
  void parseOperands(std::string &operand_str, std::vector<OPERAND> *operands);
  string replaceVariable(std::string &operand_str);
  void replaceLabel(std::string &inst, std::string &label);
  ADDR parseLocalVariable(std::string &operand);
  int parseLabel(std::string &operand);
  int parseImmediate(std::string &operand);
  void PrettyPrintInstruction(INSTRUCTION &inst);
  void PrettyPrintOperand(OPERAND &op);
  bool isCall(std::string &mnemonic);
  bool isStore(std::string &mnemonic);
  bool isRet(std::string &mnemonic);
  void buildReturnValue(OPERAND &ret);
  void buildParam(map<INSADDR, INSTRUCTION> *code);
  void fixReturnValue(map<INSADDR, INSTRUCTION> *code);
  bool dataTransferInstruction(std::string &mnemonic);
  void rootMap(map<OPERAND, OPERAND> &localVar);
  void registerLocalize(std::string &function, map<INSADDR, INSTRUCTION> &code);
  void localVariableMap(map<INSADDR, INSTRUCTION> &code, std::map<OPERAND, OPERAND> &localVar);
  void destinationAnalyze(map<INSADDR, INSTRUCTION> &code, map<OPERAND, deque<INSADDR>> &destTable);
  void buildDDG(map<INSADDR, INSTRUCTION> &code, GRAPH &ddg);
  void findAllExits(GRAPH &ddg);
  
  void PrettyPrintExits(GRAPH &ddg);
  void getPre(deque<INSADDR> &v, INSADDR addr);
  void getStoreTable(map<OPERAND, pair<OPERAND, INSADDR>> &storeTable, map<INSADDR, INSTRUCTION> &code);
  void removeStore(map<INSADDR, INSTRUCTION> &code);
  // void removeVoid(map<INSADDR, INSTRUCTION> &code);
  void removeFunctionPreface(map<INSADDR, INSTRUCTION> &code);
  void removeFunctionEpilogue(map<INSADDR, INSTRUCTION> &code);
  void colorLeftNodes(GRAPH &ddg, std::vector<INDEX> &nodes);
  void memoryLocalize(map<INSADDR, INSTRUCTION> &code);
  void removeADRP(map<INSADDR, INSTRUCTION> &code);
  void renameOperands(BLOCK &code);

  static bool isMul(string mne) {
    if (mne == "mul" or mne == "smull") {
      return true;
    }
    return false;
  };

  static bool isLSR(string mne) {
    if (mne == "lsr") {
      return true;
    }
    return false;
  };

  static bool isASR(string mne) {
    if (mne == "asr") {
      return true;
    }
    return false;
  }
// machine-related optimize
  void colorOfdivOpt(map<INSADDR, INSTRUCTION> &code, GRAPH &ddg);
  void isDivOptBlock();
  static AArch64Reg getRegister(const string &reg)
  {
    if (reg=="x0" || reg=="w0"){
      return X0;
    }
    if (reg=="x1" || reg=="w1"){
      return X1;
    }
    if (reg=="x2" || reg=="w2"){
      return X2;
    }
    if (reg=="x3" || reg=="w3"){
      return X3;
    }
    if (reg=="x4" || reg=="w4"){
      return X4;
    }
    if (reg=="x5" || reg=="w5"){
      return X5;
    }
    if (reg=="x6" || reg=="w6"){
      return X6;
    }
    if (reg=="x7" || reg=="w7"){
      return X7;
    }
    if (reg=="x8" || reg=="w8"){
      return X8;
    }
    if (reg=="x9" || reg=="w9"){
      return X9;
    }
    if (reg=="x10" || reg=="w10"){
      return X10;
    }
    if (reg=="x11" || reg=="w11"){
      return X11;
    }
    if (reg=="x12" || reg=="w12"){
      return X12;
    }
    if (reg=="x13" || reg=="w13"){
      return X13;
    }
    if (reg=="x14" || reg=="w14"){
      return X14;
    }
    if (reg=="x15" || reg=="w15"){
      return X15;
    }
    if (reg=="x16" || reg=="w16"){
      return X16;
    }
    if (reg=="x17" || reg=="w17"){
      return X17;
    }
    if (reg=="x18" || reg=="w18"){
      return X18;
    }
    if (reg=="x19" || reg=="w19"){
      return X19;
    }
    if (reg=="x20" || reg=="w20"){
      return X20;
    }
    if (reg=="x21" || reg=="w21"){
      return X21;
    }
    if (reg=="x22" || reg=="w22"){
      return X22;
    }
    if (reg=="x23" || reg=="w23"){
      return X23;
    }
    if (reg=="x24" || reg=="w24"){
      return X24;
    }
    if (reg=="x25" || reg=="w25"){
      return X25;
    }
    if (reg=="x26" || reg=="w26"){
      return X26;
    }
    if (reg=="x27" || reg=="w27"){
      return X27;
    }
    if (reg=="x28" || reg=="w28"){
      return X28;
    }
    if (reg=="x29" || reg=="w29"){
      return X29;
    }
    if (reg=="x30" || reg=="w30"){
      return X30;
    }
    if (reg=="sp" || reg=="wsp"){
      return SP;
    }
    if (reg=="xzr" || reg=="wzr"){
      return XZR;
    }
    return UNK;
  };
  static OperandType getType(const string &operand){
    string var_pat = "LOCAL";
    string reg_pat = "([wx]([0-9]|1[0-9]|2[0-9]|30))|([w]*sp)|([wx]zr)";
    string lab_pat = "(<.*>)";
    string imm_pat = "#[\\-]{0,1}[0-9]+";
    regex var_reg(var_pat);
    regex reg_reg(reg_pat);
    regex lab_reg(lab_pat);
    regex imm_reg(imm_pat);
    if(regex_match(operand, var_reg))
      return VARIABLE;
    else if(regex_match(operand, reg_reg))
      return REGISTER;
    else if (regex_match(operand, lab_reg))
      return LABEL;
    else if (regex_match(operand, imm_reg))
      return IMMEDIATE;
    else
      return UNKTYPE;
  };
  static string getRegisterName(AArch64Reg reg){
    string name;
    switch (reg)
    {
    case X0:
      name = "x0";
      break;
    case X1:
      name = "x1";
      break;
    case X2:
      name = "x2";
      break;
    case X3:
      name = "x3";
      break;
    case X4:
      name = "x4";
      break;
    case X5:
      name = "x5";
      break;
    case X6:
      name = "x6";
      break;
    case X7:
      name = "x7";
      break;
    case X8:
      name = "x8";
      break;
    case X9:
      name = "x9";
      break;
    case X10:
      name = "x10";
      break;
    case X11:
      name = "x11";
      break;
    case X12:
      name = "x12";
      break;
    case X13:
      name = "x13";
      break;
    case X14:
      name = "x14";
      break;
    case X15:
      name = "x15";
      break;
    case X16:
      name = "x16";
      break;
    case X17:
      name = "x17";
      break;
    case X18:
      name = "x18";
      break;
    case X19:
      name = "x19";
      break;
    case X20:
      name = "x20";
      break;
    case X21:
      name = "x21";
      break;
    case X22:
      name = "x22";
      break;
    case X23:
      name = "x23";
      break;
    case X24:
      name = "x24";
      break;
    case X25:
      name = "x25";
      break;
    case X26:
      name = "x26";
      break;
    case X27:
      name = "x27";
      break;
    case X28:
      name = "x28";
      break;
    case X29:
      name = "x29";
      break;
    case X30:
      name = "x30";
      break;
    case SP:
      name = "sp";
      break;
    case XZR:
      name = "xzr";
      break;
    default:
      name = "unk";
      break;
    }
    return name;
  };
  static string getTypeName(OperandType ot){
    string name;
    switch (ot)
    {
    case VARIABLE:
      name = "VARIABLE";
      break;
    case REGISTER:
      name = "REGISTER";
      break;
    case LABEL:
      name = "LABEL";
      break;
    case IMMEDIATE:
      name = "IMMEDIATE";
      break;
    default:
      name = "UNKTYPE";
      break;
    }
    return name;
  };

  static void debugPrint(string &s){
    #ifdef DEBUG
    cout << "Debug Information: " << s << endl;
    #endif
  };

};
} //aarch64
} // namespace code
