#include <iostream>
#include <string>

#include "llvm/Support/raw_ostream.h"

int parseBC(llvm::StringRef &filename, llvm::raw_string_ostream &output);

int writeToFile(llvm::StringRef filename, llvm::StringRef str);
