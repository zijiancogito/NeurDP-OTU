#include <jsoncpp/json/json.h>
#include <string>
#include <fstream>
#include <iostream>

void loadJson(std::string &filename,
              Json::Value &root) {
  Json::Reader reader;
  
	std::ifstream in(filename, std::ios::binary);
 
	if (!in.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}

  if (reader.parse(in, root)) {
    std::cout << "Load Json File: " << filename << " success." << std::endl;
  }
  else{
    std::cout << "Parse Json File: " << filename << " fail." << std::endl;
  }
}