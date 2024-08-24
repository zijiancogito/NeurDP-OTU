#include "code.h"
#include "../options/removeIR.h"
#include <string>
// #define DEBUG
namespace code
{
namespace ir{

typedef struct OPERAND{
  std::string type;
  int value;
  std::string content = "void";
  friend bool operator<(const struct OPERAND &k1, const struct OPERAND &k2);
} OPERAND;

inline bool operator < (const struct OPERAND &k1, const struct OPERAND &k2) {
  return k1.value < k2.value;
}

typedef struct{
  std::string mnemonic;
  std::vector<OPERAND> sources;
  OPERAND dest;
  bool visiable = true;
} INSTRUCTION;

typedef struct std::map<int, INSTRUCTION> BB;


typedef std::map<std::string, BB> CODE;

typedef struct EDGE
{
  int block;
  int index;
  friend bool operator==(const struct EDGE &k1, const struct EDGE &k2);
} EDGE;
inline bool operator == (const struct EDGE &k1, const struct EDGE &k2) {
  return (k1.block == k2.block && k1.index == k2.index);
}

typedef struct
{
  std::string block;
  int index;
} POS;

typedef struct
{
  int index; // pos in this block in code
  std::vector<EDGE> post; //->
  std::vector<EDGE> pre; //<-
  COLOR color = -1;
} NODE;

/*name和index结合可以获取当前指令在code中的位置*/

typedef struct{
  std::vector<NODE> b;
  std::vector<int> roots;
  std::string name;
} BLOCK;

typedef struct {
  std::vector<BLOCK> g;
  COLOR all_colors = 0;
  std::map<COLOR, std::vector<EDGE>> colors;
} GRAPH;

class Ir : public Code <options::IR::PASSES>{
public:
  std::map<std::string, Json::Value *> functions;
  
public:
  Ir (std::string &filename)
    : Code(filename)
  {
    init();
  };
  ~Ir(){};
  void init() override;
  void getOpcodeSequence(std::string &function, std::vector<std::string> &s) override;
  void getRemovedOpcodeSequence(std::string &function, options::IR::PASSES passes, std::vector<std::string> &s) override;
  void getFunctionsName(std::vector<std::string> &FunctionNames) override;
  void getFormattedCode(std::string &function, CODE &code);
  void DDAnalyze(CODE &code, GRAPH &ddg);
  void PrettyPrintCode(CODE &code);
  void PrettyPrintBB(BB &bb);
  void PrettyPrintInstruction(INSTRUCTION &inst);
  void PrettyPrintOperand(OPERAND &op);
  void extractRawCode(std::string &function, CODE &code);
  void PrettyPrintGraph(CODE &code, GRAPH &ddg);
  void getColored(GRAPH &ddg);
  void PrettyPrintColor(GRAPH &ddg);
  void getColorField(GRAPH &ddg);

private:
  void removeLoad(CODE &code);
  void removeStore(CODE &code);
  void removeAlloca(CODE &code);
  void buildVarTable(Json::Value &bbs, std::map<std::string, int> &varTable);
  void getLoadTable(CODE &code, std::map<OPERAND, OPERAND> &loadTable);
  void getStoreTable(CODE &code, std::map<OPERAND, std::tuple<OPERAND, int, std::string>> &storeTable);
  bool isLoad(std::string &opcode);
  bool isStore(std::string &opcode);
  bool isAlloca(std::string &opcode);
  bool isCall(std::string &opcode);
  bool isReturn(std::string &opcode);
  void getDestTable(CODE &code, std::map<OPERAND, std::deque<POS>> &destTable);
  void buildDDG(CODE &code, GRAPH &ddg);
  void getPre(std::deque<POS> &v, int addr);
  void findAllExits(GRAPH &ddg);
  void colorLeftNodes(GRAPH &ddg, std::vector<EDGE> &nodes);

  static void debugPrint(std::string s){
    #ifdef DEBUG
    std::cout << "Debug Information: " << s << std::endl;
    #endif
  };
};
}
}