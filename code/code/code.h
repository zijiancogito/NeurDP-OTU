#pragma once

#include <jsoncpp/json/json.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#define COLOR int

namespace code
{
template<class T>
class Code {
public:
  Json::Value root;

public:
  Code(std::string &filename){
    Json::Reader reader;
    std::ifstream in(filename, std::ios::binary);
  
    if (!in.is_open())
    {
      std::cout << "Error opening file:" << filename << std::endl;
      exit(-1);
    }

    if (reader.parse(in, root)) {
      std::cout << "Load Json File: " << filename << " success." << std::endl;
    }
    else{
      std::cout << "Parse Json File: " << filename << " fail." << std::endl;
    }
  };
  ~Code(){};

  virtual void init(){};
  virtual void getRemovedOpcodeSequence(std::string &function, T passes, std::vector<std::string> &s) {};
  virtual void getOpcodeSequence(std::string &function, std::vector<std::string> &s) {};
  virtual void getFunctionsName(std::vector<std::string> &FunctionNames) {};

private:
};
} // namespace code
