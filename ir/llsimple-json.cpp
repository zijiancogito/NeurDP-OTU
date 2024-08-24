#include "llsimple-json.h"

using namespace llvm;

int parseBCJson(StringRef &filename, llvm::raw_string_ostream &output)
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
  char abs_path[200];
  realpath(filename.str().c_str(), abs_path);
  std::unique_ptr<Module> m = std::move(moduleOrErr.get());
  std::cout << "Successfully read Module:" << std::endl;
  std::cout << " Name: " << m->getName().str() << std::endl;
  std::cout << " Target triple: " << m->getTargetTriple() << std::endl;
  output << "{\"filename\":";
  output << "\"" << abs_path << "\"";
  output << ",";
  output << "\"functions\":";
  output << "[";
  for (auto iter1 = m->getFunctionList().begin();
       iter1 != m->getFunctionList().end(); iter1++)
  {
    Function &f = *iter1;
    output << "{\"function\":";
    output << "\"" << f.getName().str() << "\"";
    output << ",";
    output << "\"basicblocks\":";
    output << "[";
    // output << "Function: " << f.getName().str() << "\n";
    for (auto iter2 = f.getBasicBlockList().begin();
          iter2 != f.getBasicBlockList().end(); iter2++) {
      BasicBlock &bb = *iter2;
      output << "{\"basicblock\":";
      output << "\"" << bb.getName().str() << "\"";
      output << ",";
      output << "\"instructions\":";
      output << "[";
      for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {
        Instruction &inst = *iter3;
        output << "{";
        output << "\"instruction\":";
        output << "\"" << &inst << "\"";
        output << ",";
        output << "\"return\":";
        output << "{";
        output << "\"type\":";
        output << "\"";
        inst.getType()->print(output, false, true);
        output << "\"";
        output << ",";
        output << "\"value\":";
        output << "\"";
        if (inst.hasName())
          output << inst.getName();
        else{
          output << "ptr" << &inst;
        }
        output << "\"";
        output << "}";
        output << ",";
        output << "\"opcode\":";
        output << "\"";
        output << inst.getOpcodeName();
        output << "\"";
        output << ",";
        unsigned int i = 0;
        unsigned int opnt_cnt = inst.getNumOperands();
        output << "\"operands\":";
        output << "[";
        Value **operands = (Value **)malloc(sizeof(Value *) * opnt_cnt);
        for (; i < opnt_cnt; i++)
        {
          Value *opnd = inst.getOperand(i);
          std::string o;
          // opnd->getType()->print(llvm::outs(), false, true);
          // llvm::outs() << "\n";
          output << "{";
          output << "\"type\":";
          output << "\"";
          opnd->getType()->print(output, false, true);
          output << "\"";
          output << ",";
          output << "\"value\":";
          output << "\"";
          if (opnd->hasName())
            output <<opnd->getName();
          else{
            output << "ptr" << opnd;
          }
          output << "\"";
          output << "}";
          if (i < opnt_cnt - 1) output << ",";
        }
        output << "]";
        output << "}";
        iter3++;
        if (iter3 != bb.end()){
          output << ",";
        }
        iter3--;
      }
      output << "]";
      output << "}";
      iter2++;
      if (iter2 != f.getBasicBlockList().end())
      {
        output << ",";
      }
      iter2--;
    }
    output << "]";
    output << "}";
    iter1++;
    if (iter1 != m->getFunctionList().end()){
      output << ",";
    }
    iter1--;
  }
  output << "]";
  output << "}";
  return 0;
}

int dumpJson(std::string &jstr, std::string filename){
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(jstr, root, false))
  {
    std::ofstream os;
    Json::FastWriter writer;
    std::string js = writer.write(root);
    os.open(filename);
    if (!os.is_open())
      llvm::errs() << "error：can not find or create the file which named \" demo.json\". \n";
    os << js;
    os.close();
  } else{
    llvm::errs() << "Json parse failed.\n";
  }
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
//   int res = parseBCJson(filename, output);
//   llvm::outs() << output.str();
//   StringRef outfile = argv[2];
//   res = dumpJson(output.str(), outfile);
//   return 0;
// }
