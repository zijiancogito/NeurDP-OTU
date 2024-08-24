
#include <string>
#include <iostream>
#include <map>

namespace options
{
  namespace aarch64
  {
    typedef struct{
      bool mov = true;
      bool store = true;
      bool load = true;
    } PASSES;
    enum optype
    {
      MOV,
      MVN,
      MOVZ,
      MOVN,
      MOVK = 4,

      LDR,
      LDURB,
      LDUR,
      LDURH,
      LDURSB,
      LDURSH,
      LDURSW,
      LDRB,
      LDRH,
      LDRSB,
      LDRSH,
      LDRSW,
      LDTR,
      LDTRB,
      LDTRSB,
      LDTRH,
      LDTRSH,
      LDTRSW,
      LDXR,
      LDXRB,
      LDXRH,
      LDAXR,
      LDAXRB,
      LDAXRH,
      LDAR,
      LDARB,
      LDARH,
      LDP,
      LDPSW,
      LDNP,
      LDXP,
      LDAXP,

      STR,
      STRB,
      STRH,
      STUR,
      STURB,
      STURH,
      STTR,
      STTRB,
      STTRH,
      STXR,
      STXRB,
      STXRH,
      STP,
      STNP,
      STXP,

      OTHER
    };
    static std::map<std::string, int> INSTMAP = {
        {"mov", optype(MOV)},
        {"mvn", optype(MVN)},
        {"movz", optype(MOVZ)},
        {"movn", optype(MOVN)},
        {"movn", optype(MOVK)},

        {"ldr", optype(LDR)},
        {"ldurb", optype(LDURB)},
        {"ldur", optype(LDUR)},
        {"ldurh", optype(LDURH)},
        {"ldursb", optype(LDURSB)},
        {"ldursh", optype(LDURSH)},
        {"ldursw", optype(LDURSW)},
        {"ldrb", optype(LDRB)},
        {"ldrh", optype(LDRH)},
        {"ldrsb", optype(LDRSB)},
        {"ldrsh", optype(LDRSH)},
        {"ldrsw", optype(LDRSW)},
        {"ldtr", optype(LDTR)},
        {"ldtrb", optype(LDTRB)},
        {"ldtrsb", optype(LDTRSB)},
        {"ldtrh", optype(LDTRH)},
        {"ldtrsh", optype(LDTRSH)},
        {"ldtrsw", optype(LDTRSW)},
        {"ldxr", optype(LDXR)},
        {"ldxrb", optype(LDXRB)},
        {"ldxrh", optype(LDXRH)},
        {"ldaxr", optype(LDAXR)},
        {"ldaxrb", optype(LDAXRB)},
        {"ldaxrh", optype(LDAXRH)},
        {"ldar", optype(LDAR)},
        {"ldarb", optype(LDARB)},
        {"ldarh", optype(LDARH)},
        {"ldp", optype(LDP)},
        {"ldpsw", optype(LDPSW)},
        {"ldnp", optype(LDNP)},
        {"ldxp", optype(LDXP)},
        {"ldaxp", optype(LDAXP)},

        {"str", optype(STR)},
        {"strb", optype(STRB)},
        {"strh", optype(STRH)},
        {"stur", optype(STUR)},
        {"sturb", optype(STURB)},
        {"sturh", optype(STURH)},
        {"sttr", optype(STTR)},
        {"sttrb", optype(STTRB)},
        {"sttrh", optype(STTRH)},
        {"stxr", optype(STXR)},
        {"stxrb", optype(STXRB)},
        {"stxrh", optype(STXRH)},
        {"stp", optype(STP)},
        {"stnp", optype(STNP)},
        {"stxp", optype(STXP)},
    };
    static bool isMov(int opcode)
    {
      if (opcode >=0 && opcode <= 4)
        return true;
      return false;
    }

    static bool isStore(int opcode){
      if(opcode >=37 && opcode <=51)
        return true;
      return false;
    }
    static bool isLoad(int opcode){
      if (opcode >= 5 && opcode <= 36)
        return true;
      return false;
    }

    static bool removeInst(PASSES p, std::string &opname){
      int opcode;
      if (INSTMAP.find(opname) == INSTMAP.end())
      {
        opcode = -1;
      }else {
        opcode = INSTMAP[opname];
      }
      if ((p.load && isLoad(opcode))
        ||(p.mov && isMov(opcode))
        ||(p.store && isStore(opcode))){
        return true;
      }
      return false;
    }
  } // namespace aarch64
}