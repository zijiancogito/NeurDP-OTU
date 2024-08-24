
#include <string>
#include <iostream>
#include <map>

namespace options
{
  
  namespace IR
  {
  typedef struct{
    bool alloca = true;
    bool store = true;
    bool load = true;
  } PASSES;
  enum IRInst
  {
    LOAD,
    STORE,
    ALLOCA
  };
  static std::map<std::string, int> IRMAP = {
      {"load", IRInst(LOAD)},
      {"store", IRInst(STORE)},
      {"alloca", IRInst(ALLOCA)}};

  static bool isAlloca(int opcode){
    if (opcode == 2){
      return true;
    }
    return false;
  }
  static bool isStore(int opcode){
    if (opcode == 1){
      return true;
    }
    return false;
  }
  static bool isLoad(int opcode){
    if (opcode == 0){
      return true;
    }
    return false;
  }
  static bool removeInst(PASSES p, std::string &opname){
    int opcode;
    if (IRMAP.find(opname) == IRMAP.end())
    {
      opcode = 3;
    }else {
      opcode = IRMAP[opname];
    }
    if ((p.load && isLoad(opcode))
      ||(p.alloca && isAlloca(opcode))
      ||(p.store && isStore(opcode))){
      return true;
    }
    return false;
  }
  } // namespace IR
} // namespace options
