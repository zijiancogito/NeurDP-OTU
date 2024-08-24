#include <iostream>
#include <cstring>
#include <spawn.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "llvm/Support/raw_ostream.h"
#include "llvm-objdump.h"
#include <gflags/gflags.h>

using namespace std;
using namespace llvm;


int oneDis(std::string outfile, std::string objfile)
{
  std::string str;
  llvm::raw_string_ostream output(str);
  int res = disasm(objfile, outfile);
  return res;
}

void optDis(std::string dir, int id){
  for (int i = 0; i < 3;i++){
		std::string path = dir + "/case" + to_string(id) + "/o" + to_string(i);
		std::string objfile = path + "/main_o" + to_string(i) + "-aarch64.o";
		std::string outfile = path + "/main_o" + to_string(i) + "-aarch64-dis.json";
    int ret = oneDis(outfile, objfile);
    if (ret != 0){
      std::cout << "case" << id << " : O" << i << " failed." << std::endl;
    }
  }
}

int batchDis(std::string dir, int n_sample) {
  pid_t pid;
  std::vector<int> provList;
  int id;
  for (int i = 0; i < n_sample; i = i + 1000)
  {
    provList.push_back(i);
  }
  for (std::vector<int>::iterator it = provList.begin(); it != provList.end(); ++it)
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
      optDis(dir, k+id);
    break;
  case -1:
    std::cout << "Fail to fork." << std::endl;
    break;
  default:
    break;
  }
  return 0;
}

int test() {
  std::string path = "/root/cross_compile/case0";
  for (int opt = 0; opt < 3;opt++) {
    std::string objfile = path + "/o" +to_string(opt) + "/main_o" + to_string(opt) + "-aarch64.o";
    std::string outfile = path + "/o" +to_string(opt) + "/main_o" + to_string(opt) + "-aarch64-dis.json";
    std::string str;
    llvm::raw_string_ostream output(str);
    int res = disasm(objfile, outfile);
  }
  return 0;
}

DEFINE_int32(mode, 0, "Process one file or batch. 0 is one. 1 is batch");
DEFINE_string(infile, "case0", "Filename. Specify is mode=0.");
DEFINE_string(outfile, "case0.json", "Output file. Specify is mode=0.");
DEFINE_string(path, "./", "Dir of input files. Specify is mode=1");
DEFINE_int32(thread, 1, "Thread number.");
DEFINE_int32(n_sample, 100000, "n_sample");

int main(int argc, char *argv[])
{
	// test();
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	if(FLAGS_mode == 0){
		oneDis(FLAGS_outfile, FLAGS_infile);
	} else if (FLAGS_mode == 1) {
		batchDis(FLAGS_path, FLAGS_n_sample);
	} else {
		std::cerr << "Invalid mode. \n" << "Please use --help to get the usage of this tool." << std::endl;
	}
  return 0;
}
