#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>

#include <spawn.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <gflags/gflags.h>

// #include "llformat.h"
#include "llsimple-json.h"

using namespace std;
using namespace llvm;

int oneSimple(std::string dir, int id, int opt){
  std::string path = dir + "/case" + to_string(id) + "/o" + to_string(opt);
  std::string bcfile = path + "/main_o" + to_string(opt) + "-aarch64.bc";
  std::string outfile = path + "/main_o" + to_string(opt) + "-aarch64-ir.json";
  StringRef filename = bcfile;
  std::string str;
  llvm::raw_string_ostream output(str);
  // int res = parseBC(filename, output);
  int res = parseBCJson(filename, output);
  if (res == 0)
  {
    StringRef outf = outfile;
    // writeToFile(outf, output.str());
    dumpJson(output.str(), outfile);
  }
  else
  {
    std::cout << "Failed." << std::endl;
  }
  return res;
}

void optSimple(std::string dir, int id){
  for (int i = 0; i < 3;i++){
    int ret = oneSimple(dir, id, i);
    if (ret != 0){
      std::cout << "case" << id << " : O" << i << " failed." << std::endl;
    }
  }
}

int batchSimple(std::string dir, int n_sample) {
  pid_t pid;
  vector<int> provList;
  int id;
  for (int i = 0; i < n_sample; i = i + 1000)
  {
    provList.push_back(i);
  }
  for (vector<int>::iterator it = provList.begin(); it != provList.end(); ++it)
  {
    id = *it;
    pid = fork();
    if (pid == 0 || pid == -1)
    {
      break;
    }
  }
  switch (pid)
  {
  case 0:
    for (int k = 0; k < 1000; k++)
      // std::cout << k+id << std::endl;
      optSimple(dir, k+id);
    break;
  case -1:
    std::cout << "Fail to fork." << std::endl;
    break;
  default:
    break;
  }
  return 0;
}

DEFINE_int32(n_sample, 100000, "n_sample");
DEFINE_string(dir, "./", "path");

int main(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  //if (argc != 3) {
  //  std::cerr << "Usage: " << argv[0] << //" dir" << std::endl;
  //  return 1;
  //}
  // std::string dir= argv[1];
  // optSimple(dir, 0);
  batchSimple(FLAGS_dir, FLAGS_n_sample);
  return 0;
}