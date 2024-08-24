#include <iostream>
#include <string>

#include "llvm/Support/raw_ostream.h"


int fullParseBC(llvm::StringRef &filename, llvm::raw_string_ostream &output);

// int writeToFile(StringRef filename, StringRef str);
