#include "llsimple.h"
#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"

using namespace llvm;

int parseBC(StringRef &filename, llvm::raw_string_ostream &output)
{
  LLVMContext context;
  ErrorOr<std::unique_ptr<MemoryBuffer>> fileOrErr =
      MemoryBuffer::getFileOrSTDIN(filename);
  if (std::error_code ec = fileOrErr.getError()) {
    std::cerr << " Error opening input file: " + ec.message() << std::endl;
    return 2;
  }
  Expected<std::unique_ptr<Module>> moduleOrErr =
      parseBitcodeFile(fileOrErr.get()->getMemBufferRef(), context);
  if (std::error_code ec = fileOrErr.getError()) {
    std::cerr << "Error reading Modulle: " + ec.message() << std::endl;
    return 3;
  }
  std::unique_ptr<Module> m = std::move(moduleOrErr.get());
  std::cout << "Successfully read Module:" << std::endl;
  std::cout << " Name: " << m->getName().str() << std::endl;
  std::cout << " Target triple: " << m->getTargetTriple() << std::endl;
  for (auto iter1 = m->getFunctionList().begin();
       iter1 != m->getFunctionList().end(); iter1++)
  {
    Function &f = *iter1;
    output << "Function: " << f.getName().str() << "\n";
    for (auto iter2 = f.getBasicBlockList().begin();
          iter2 != f.getBasicBlockList().end(); iter2++) {
      BasicBlock &bb = *iter2;
      output << "BasicBlock: " << bb.getName().str() << "\n";
      for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {
        Instruction &inst = *iter3;
        output << "Instruction " << &inst << " : ";
        // output << "Return : ";
        output << " type(";
        inst.getType()->print(output, false, true);
        output << ") ";
        if (inst.hasName())
          output << inst.getName();
        else{
          output << "ptr" << &inst;
        }
        output << "  " << inst.getOpcodeName() << "  ";
        unsigned int i = 0;
        unsigned int opnt_cnt = inst.getNumOperands();
        Value **operands = (Value **)malloc(sizeof(Value *) * opnt_cnt);
        for (; i < opnt_cnt; i++)
        {
          Value *opnd = inst.getOperand(i);
          std::string o;
          // opnd->getType()->print(llvm::outs(), false, true);
          // llvm::outs() << "\n";
          output << "type(";
          opnd->getType()->print(output, false, true);
          output << ")";
          if (opnd->hasName())
            output << " " << opnd->getName() << " ";
          else{
            output << " ptr" << opnd << "  ";
          }
        }
        output << "\n";
      }
    }
    output << "ENDFunction\n\n";
  }
  return 0;
}

int writeToFile(StringRef filename, StringRef str) {
  std::error_code EC;
  llvm::raw_fd_ostream outf(filename, EC);
  outf << str;
  return 0;
}

// int main(int argc, char *argv[]) {
//   if (argc != 3) {
//     std::cerr << "Usage: " << argv[0] << "bitcode_filename" << std::endl;
//     return 1;
//   }
//   StringRef filename = argv[1];
//   std::string str;
//   llvm::raw_string_ostream output(str);
//   int res = parseBC(filename, output);
//   StringRef outfile = argv[2];
//   writeToFile(outfile, output.str());
//   return res;
// }