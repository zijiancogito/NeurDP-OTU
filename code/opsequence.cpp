
#include "code/Ir.h"
// #include "code/aarch64real.h"
#include "CodeConfig.h"

#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>

#include <spawn.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <gflags/gflags.h>

#define DEBUGIR
#undef DEBUGIR

// #define DEBUGASM
#define DEBUGASM
#undef DEBUGASM
// #undef DEBUGASM
#define TRAIN
#undef TRAIN

#define DEBUGALL
// #undef DEBUGALL
#ifdef DEBUGASM
  #include "code/aarch64real.h"
#else
  #include "code/aarch64Asm.h"
#endif

using namespace std;
using namespace code;

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
      cout << "error：can not find or create the file which named \" demo.json\". \n";
    os << js;
    os.close();
  } else{
    cout << "dumpJson: Json parse failed.\n";
  }
  return 0;
}

#ifdef TRAIN

void processAsm(map<INSADDR, aarch64::INSTRUCTION> &asm_code,
                aarch64::GRAPH &asm_ddg,
                COLOR c,
                stringstream &tmp){
  // 找到当前颜色的指令
  tmp << "{";
  tmp << "\"instructions\""
      << ":"
      << "[";
  int cnt = 0;
  for (auto asm_index : asm_ddg.colors[c])
  {
    // 指令索引
    int index = cnt;
    if (cnt != 0)
      tmp << ",";
    tmp << "{";
    tmp << "\"index\""
        << ":"
        << "\"" << index << "\"";
    tmp << ",";
    tmp << "\"addr\""
        << ":"
        << "\"" << asm_ddg.g[asm_index].address << "\"";
    tmp << ",";
    string mne = asm_code[asm_ddg.g[asm_index].address].mnemonic;
    tmp << "\"mnemonic\""
        << ":"
        << "\"" << mne << "\"";
    tmp << ",";
    string dest = asm_code[asm_ddg.g[asm_index].address].destination.content;
    int alias = asm_code[asm_ddg.g[asm_index].address].destination.alias;
    tmp << "\"dest\""
        << ":";
    if(alias!=-1){
      tmp << "\"%" << alias << "\"";
    } else {
      tmp << "\"" << dest << "\"";
    }

    tmp << ",";
    /*这里可以加入其他数据的分析，例如类型*/
    tmp << "\"src\""
        << ":"
        << "["; //start of src
    int op_cnt = 0;
    for (auto src : asm_code[asm_ddg.g[asm_index].address].source)
    {
      string s = src.content;
      int a = src.alias;
      if (s == "void")
      {
        continue;
      }
      if (op_cnt != 0)
        tmp << ",";
      if(a != -1){
        tmp << "\"%" << a << "\"";
      } else {
        tmp << "\"" << s << "\"";
      }
      op_cnt++;
    }
    tmp << "]"; //end of src
    tmp << "}";

    cnt++;
  }
  tmp << "]"; // instruction end
  tmp << ",";
  tmp << "\"edges\""
      << ":"
      << "["; //start of edges
  // 构建节点之间的关系
  vector<string> edges;
  int i = 0;
  for (auto node_i : asm_ddg.colors[c])
  {
    int j = 0;
    for (auto node_j : asm_ddg.colors[c])
    {
      if (node_i == node_j){
        j++;
        continue;
      }
      /*判断 nodei 是否是 nodej的前驱节点*/
      if(find(asm_ddg.g[node_i].pre.begin(), asm_ddg.g[node_i].pre.end(), node_j) != asm_ddg.g[node_i].pre.end()){
        //节点之间的关系
        string r = "[\"" + to_string(i) + "\",\"" + to_string(j) + "\"]";
        edges.push_back(r);
      }
      j++;
    }
    i++;
  }
  cnt = 0;
  for (auto e : edges)
  {
    if (cnt != 0)
      tmp << ",";
    tmp << e;
    cnt++;
  }
  tmp << "]"; // end of edges;
  tmp << "}"; //end
}

void processIR(ir::CODE &ir_code,
               ir::GRAPH &ir_ddg,
               COLOR c,
               stringstream &tmp) {
  tmp << "{";
  tmp << "\"instructions\""
      << ":"
      << "[";
  int cnt = 0;
  for (auto ir_index : ir_ddg.colors[c])
  {
    ir::POS p = {ir_ddg.g[ir_index.block].name, ir_ddg.g[ir_index.block].b[ir_index.index].index};
    int index = cnt;
    if(cnt!=0)
      tmp << ",";
    tmp << "{";
    tmp << "\"index\""
        << ":"
        << "\"" << index << "\"";
    tmp << ",";
    string mne = ir_code[p.block][p.index].mnemonic;
    tmp << "\"mnemonic\""
        << ":"
        << "\"" << mne << "\"";
    tmp << ",";
    string dest = ir_code[p.block][p.index].dest.content;
    tmp << "\"dest\""
        << ":"
        << "\"" << dest << "\"";
    tmp << ",";
    tmp << "\"src\""
        << ":"
        << "["; //start of src
    int op_cnt = 0;
    for (auto src : ir_code[p.block][p.index].sources)
    {
      int s = src.value;
      if (s == -1){
        continue;
      }
      if(op_cnt != 0)
        tmp << ",";
      tmp << "\"%" << s << "\"";
      op_cnt++;
    }
    tmp << "]"; //end of src
    tmp << "}";
    cnt++;
  }
  // 处理边
  tmp << "]"; // instruction end
  tmp << ",";
  tmp << "\"edges\""
      << ":"
      << "["; //start of edges

  vector<string> edges;
  int i = 0;
  for (auto node_i : ir_ddg.colors[c])
  {
    int j = 0;
    for (auto node_j : ir_ddg.colors[c])
    {
      if(find(ir_ddg.g[node_i.block].b[node_i.index].pre.begin(), ir_ddg.g[node_i.block].b[node_i.index].pre.end(), node_j) != ir_ddg.g[node_i.block].b[node_i.index].pre.end()) {
        string r = "[\"" + to_string(i) + "\",\"" + to_string(j) + "\"]";
        edges.push_back(r);
      }
      j++;
    }
    i++;
  }
  cnt = 0;
  for (auto e : edges)
  {
    if(cnt != 0)
      tmp << ",";
    tmp << e;
    cnt++;
  }
  tmp << "]"; // end of edges;
  tmp << "}"; //end
}

bool graphMatch(map<INSADDR, aarch64::INSTRUCTION> &asm_code,
                aarch64::GRAPH &asm_ddg,
                ir::CODE &ir_code,
                ir::GRAPH &ir_ddg,
                stringstream &json_stream){
  if(asm_ddg.all_colors == ir_ddg.all_colors){
    json_stream << "[";
    for (COLOR c = 0; c < asm_ddg.all_colors; c++)
    {
      stringstream asm_json_stream;
      processAsm(asm_code, asm_ddg, c, asm_json_stream);
      stringstream ir_json_stream;
      processIR(ir_code, ir_ddg, c, ir_json_stream);
      json_stream << "{\"color\":" << "\"" << c << "\"" << ",";
      json_stream << "\"asm\":" << asm_json_stream.str() << ",";
      json_stream << "\"ir\":" << ir_json_stream.str() << "}";
      if ( c < asm_ddg.all_colors -1 ){
        json_stream << ",";
      }
    }
    json_stream << ']';
    return true;
  }
  return false;
}

void getMSequence(string asmfilename, string irfilename, string jsonfile)
{
  aarch64::aarch64Asm AsmObject(asmfilename);
  ir::Ir IrObject(irfilename);
  vector<string> AsmFunctions, IrFunctions;
  // Use Asm functions' name as index.
  AsmObject.getFunctionsName(AsmFunctions);
  IrObject.getFunctionsName(IrFunctions);
  stringstream jss;
  jss << "{\"filename\":" << "\"" << asmfilename << "\"" << ",";
  jss << "\"functions\": [";
  int cnt = 0;
  for (vector<string>::iterator it = AsmFunctions.begin(); it != AsmFunctions.end(); ++it)
  {
    string name = *it;
    if (std::find(IrFunctions.begin(), IrFunctions.end(), name) == IrFunctions.end()){
      continue;
    }
    if (name == "main") {
      continue;
    }
    map<INSADDR, aarch64::INSTRUCTION> asm_code;
    aarch64::GRAPH asm_ddg;
    AsmObject.DDAnalyze(name, asm_code, asm_ddg);
    AsmObject.getColored(asm_ddg);

    // IR
    ir::CODE ir_code;
    IrObject.getFormattedCode(name, ir_code);
    ir::GRAPH ir_ddg;
    IrObject.DDAnalyze(ir_code, ir_ddg);
    IrObject.getColored(ir_ddg);
    stringstream tmp;
    bool res = graphMatch(asm_code, asm_ddg, ir_code, ir_ddg, tmp);
    if (res){
      if(cnt != 0)
        jss << ",";
      cnt++;
      jss << "{\"function\":\"" << name << "\", \"graph\":";
      jss << tmp.str();
      jss << "}";
    }
  }
  jss << "]";
  jss << "}";
  string str = jss.str();
  dumpJson(str, jsonfile);
}

void getAsmSequence(string asmfilename, string jsonfile){
  aarch64::aarch64Asm AsmObject(asmfilename);
  vector<string> AsmFunctions;
  // Use Asm functions' name as index.
  // cout << asmfilename << endl;
  AsmObject.getFunctionsName(AsmFunctions);
  stringstream jss;
  jss << "{\"filename\":" << "\"" << asmfilename << "\"" << ",";
  jss << "\"functions\": [";
  int cnt = 0;
  for (vector<string>::iterator it = AsmFunctions.begin(); it != AsmFunctions.end(); ++it)
  {
    string name = *it;
    // cout << name << endl;
    map<INSADDR, aarch64::INSTRUCTION> asm_code;
    aarch64::GRAPH asm_ddg;
    AsmObject.DDAnalyze(name, asm_code, asm_ddg);
    AsmObject.getColored(asm_ddg);

    stringstream json_stream;
    json_stream << "[";

    for (COLOR c = 0; c < asm_ddg.all_colors; c++)
    {
      stringstream asm_json_stream;
      processAsm(asm_code, asm_ddg, c, asm_json_stream);
      json_stream << "{\"color\":" << "\"" << c << "\"" << ",";
      json_stream << "\"asm\":" << asm_json_stream.str() << "}";
      if ( c < asm_ddg.all_colors -1 ){
        json_stream << ",";
      }
    }

    json_stream << ']';
    if(cnt != 0)
      jss << ",";
    cnt++;
    jss << "{\"function\":\"" << name << "\", \"graph\":";
    jss << json_stream.str();
    jss << "}";
  }
  jss << "]";
  jss << "}";
  string str = jss.str();
  dumpJson(str, jsonfile);
}

void getIRSequence(string irfilename, string jsonfile){
  ir::Ir IrObject(irfilename);
  vector<string> IrFunctions;
  IrObject.getFunctionsName(IrFunctions);
  stringstream jss;
  jss << "{\"filename\":" << "\"" << irfilename << "\"" << ",";
  jss << "\"functions\": [";
  int cnt = 0;
  for (vector<string>::iterator it = IrFunctions.begin(); it != IrFunctions.end(); ++it)
  {
    string name = *it;
    ir::CODE ir_code;
    IrObject.getFormattedCode(name, ir_code);
    ir::GRAPH ir_ddg;
    IrObject.DDAnalyze(ir_code, ir_ddg);
    IrObject.getColored(ir_ddg);
    stringstream json_stream;

    for (COLOR c = 0; c < ir_ddg.all_colors; c++)
    {
      stringstream ir_json_stream;
      processIR(ir_code, ir_ddg, c, ir_json_stream);
      json_stream << "{\"color\":" << "\"" << c << "\"" << ",";
      json_stream << "\"ir\":" << ir_json_stream.str() << "}";
      if ( c < ir_ddg.all_colors -1 ){
        json_stream << ",";
      }
    }
    json_stream << ']';
    if(cnt != 0)
      jss << ",";
    cnt++;
    jss << "{\"function\":\"" << name << "\", \"graph\":";
    jss << json_stream.str();
    jss << "}";
  }
  jss << "]";
  jss << "}";
  string str = jss.str();
  dumpJson(str, jsonfile);
}

int oneSimple(std::string dir, int id, int opt){
  std::string path = dir + "/case" + to_string(id) + "/o" + to_string(opt);
  std::string asmfile = path + "/main_o" + to_string(opt) + "-aarch64-dis.json";
  std::string irfile = path + "/main_o" + to_string(opt) + "-aarch64-ir.json";
  std::string outfile = path + "/main_o" + to_string(opt) + "-aarch64-graph.json";
  // int res = parseBC(filename, output);
  getMSequence(asmfile, irfile, outfile);
  return 0;
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

void testIR(ir::CODE &ir_code,
               ir::GRAPH &ir_ddg) {
  for (COLOR c = 0; c < ir_ddg.all_colors; c++){
    stringstream tmp;
    processIR(ir_code, ir_ddg, c, tmp);
  }
}
#endif

#ifdef DEBUGASM

void processAsm(real::BLOCK &asm_code,
                real::BLKGRAPH &asm_ddg,
                COLOR c,
                stringstream &tmp){
  // 找到当前颜色的指令
  tmp << "{";
  tmp << "\"instructions\""
      << ":"
      << "[";
  int cnt = 0;
  for (auto asm_index : asm_ddg.colors[c])
  {
    // 指令索引
    int index = cnt;
    if (cnt != 0)
      tmp << ",";
    tmp << "{";
    tmp << "\"index\""
        << ":"
        << "\"" << index << "\"";
    tmp << ",";
    tmp << "\"addr\""
        << ":"
        << "\"" << asm_ddg.g[asm_index].address << "\"";
    tmp << ",";
    string mne = asm_code[asm_ddg.g[asm_index].address].mnemonic;
    tmp << "\"mnemonic\""
        << ":"
        << "\"" << mne << "\"";
    tmp << ",";
    string dest = asm_code[asm_ddg.g[asm_index].address].destination.content;
    int alias = asm_code[asm_ddg.g[asm_index].address].destination.alias;
    tmp << "\"dest\""
        << ":";
    if(alias!=-1){
      tmp << "\"%" << alias << "\"";
    } else {
      tmp << "\"" << dest << "\"";
    }

    tmp << ",";
    /*这里可以加入其他数据的分析，例如类型*/
    tmp << "\"src\""
        << ":"
        << "["; //start of src
    int op_cnt = 0;
    for (auto src : asm_code[asm_ddg.g[asm_index].address].source)
    {
      string s = src.content;
      int a = src.alias;
      if (s == "void")
      {
        continue;
      }
      if (op_cnt != 0)
        tmp << ",";
      if (a != -1){
        tmp << "\"%" << a << "\"";
      } else {
        tmp << "\"" << s << "\"";
      }
      op_cnt++;
    }
    tmp << "]"; //end of src
    tmp << "}";

    cnt++;
  }
  tmp << "]"; // instruction end
  tmp << ",";
  tmp << "\"edges\""
      << ":"
      << "["; //start of edges
  // 构建节点之间的关系
  vector<string> edges;
  int i = 0;
  for (auto node_i : asm_ddg.colors[c])
  {
    int j = 0;
    for (auto node_j : asm_ddg.colors[c])
    {
      if (node_i == node_j){
        j++;
        continue;
      }
      /*判断 nodei 是否是 nodej的前驱节点*/
      if(find(asm_ddg.g[node_i].pre.begin(), asm_ddg.g[node_i].pre.end(), node_j) != asm_ddg.g[node_i].pre.end()){
        //节点之间的关系
        string r = "[\"" + to_string(i) + "\",\"" + to_string(j) + "\"]";
        edges.push_back(r);
      }
      j++;
    }
    i++;
  }
  cnt = 0;
  for (auto e : edges)
  {
    if (cnt != 0)
      tmp << ",";
    tmp << e;
    cnt++;
  }
  tmp << "]"; // end of edges;
  tmp << "}"; //end
}

void getAsmSequence(string asmfilename, string jsonfile){
  real::aarch64Asm AsmObject(asmfilename);
  vector<string> AsmFunctions;
  // Use Asm functions' name as index.
  // cout << asmfilename << endl;
  AsmObject.getFunctionsName(AsmFunctions);
  stringstream jss;
  jss << "{\"filename\":" << "\"" << asmfilename << "\"" << ",";
  jss << "\"functions\": [";
  int cnt = 0;
  for (vector<string>::iterator it = AsmFunctions.begin(); it != AsmFunctions.end(); ++it)
  {
    string name = *it;
    // cout << name << endl;
    real::FUNCTION asm_code;
    real::GRAPH asm_ddg;
    AsmObject.DDAnalyze(name, asm_code, asm_ddg);
    AsmObject.PrettyPrintCode(asm_code);
    AsmObject.getColored(asm_ddg);
    stringstream blk_stream;
    int blk_cnt = 0;
    blk_stream << "[";
    for (real::GRAPH::iterator bit = asm_ddg.begin(); bit != asm_ddg.end(); ++bit)
    {
      stringstream json_stream;
      json_stream << "[";
      real::BLOCK_ADDR start = bit->first;
      real::BLOCK blk_code = asm_code[start];
      real::BLKGRAPH blk_ddg = bit->second;
      for (COLOR c = 0; c < blk_ddg.all_colors; c++)
      {
        stringstream asm_json_stream;
        processAsm(blk_code, blk_ddg, c, asm_json_stream);
        json_stream << "{\"color\":"
                    << "\"" << c << "\""
                    << ",";
        json_stream << "\"asm\":" << asm_json_stream.str() << "}";
        if (c < blk_ddg.all_colors - 1)
        {
          json_stream << ",";
        }
      }
      json_stream << ']';

      if(blk_cnt != 0)
        blk_stream << ",";
      blk_cnt++;
      blk_stream << "{\"block\":\"" << start << "\", \"graph\":";
      blk_stream << json_stream.str();
      blk_stream << "}";
    }
    blk_stream << "]";
    if (cnt != 0)
    {
      jss << ",";
    }
    cnt++;
    jss << "{\"function\":\"" << name << "\", \"blocks\":";
    jss << blk_stream.str();
    jss << "}";
  }
  jss << "]";
  jss << "}";
  string str = jss.str();
  // cout << str;
  dumpJson(str, jsonfile);
}


#endif

#define DEBUG
#undef DEBUG
#ifdef DEBUG
void testASM(string asmfilename) {
  aarch64::aarch64Asm AsmObject(asmfilename);
  vector<string> AsmFunctions;
  // Use Asm functions' name as index.
  AsmObject.getFunctionsName(AsmFunctions);
  int cnt = 0;
  for (vector<string>::iterator it = AsmFunctions.begin(); it != AsmFunctions.end(); ++it)
  {
    string name = *it;
    map<INSADDR, aarch64::INSTRUCTION> asm_code;
    aarch64::GRAPH asm_ddg;
    AsmObject.DDAnalyze(name, asm_code, asm_ddg);
    AsmObject.getColored(asm_ddg);

    cout << name << endl;
    AsmObject.printRawCode(name);
    cout << "-------------------------------\n";
    AsmObject.PrettyPrintCode(asm_code);
    cout << "-------------------------------\n";
    // AsmObject.PrettyPrintColor(asm_ddg);
    // cout << "-------------------------------\n";

  }
}
#endif

#ifdef DEBUGIR
void testIR(string irfilename)
{
  ir::Ir IrObject(irfilename);
  vector<string> IrFunctions;
  // Use Asm functions' name as index.
  IrObject.getFunctionsName(IrFunctions);
  int cnt = 0;
  for (vector<string>::iterator it = IrFunctions.begin(); it != IrFunctions.end(); ++it)
  {
    string name = *it;
    cout << name << endl;
    if (std::find(IrFunctions.begin(), IrFunctions.end(), name) == IrFunctions.end())
    {
      continue;
    }
    if (name == "main") {
      continue;
    }

    // IR
    ir::CODE ir_code;
    IrObject.getFormattedCode(name, ir_code);
    ir::GRAPH ir_ddg;
    IrObject.DDAnalyze(ir_code, ir_ddg);
    IrObject.getColored(ir_ddg);
    IrObject.PrettyPrintCode(ir_code);
    cout << "-------------------------------\n";
    IrObject.PrettyPrintColor(ir_ddg);
    cout << "-------------------------------\n";
    // testIR(ir_code, ir_ddg);
  }
}
#endif

#ifdef DEBUGALL
void test(string asmfilename, string irfilename)
{
  aarch64::aarch64Asm AsmObject(asmfilename);
  ir::Ir IrObject(irfilename);
  vector<string> AsmFunctions, IrFunctions;
  // Use Asm functions' name as index.
  AsmObject.getFunctionsName(AsmFunctions);
  IrObject.getFunctionsName(IrFunctions);
  int cnt = 0;
  for (vector<string>::iterator it = AsmFunctions.begin(); it != AsmFunctions.end(); ++it)
  {
    string name = *it;
    cout << name << endl;
    if (std::find(IrFunctions.begin(), IrFunctions.end(), name) == IrFunctions.end())
    {
      continue;
    }
    if (name == "main") {
      continue;
    }
    map<INSADDR, aarch64::INSTRUCTION> asm_code;
    aarch64::GRAPH asm_ddg;
    AsmObject.DDAnalyze(name, asm_code, asm_ddg);
    AsmObject.getColored(asm_ddg);
    AsmObject.printRawCode(name);
    cout << "-------------------------------\n";
    AsmObject.PrettyPrintCode(asm_code);
    cout << "-------------------------------\n";
    AsmObject.PrettyPrintColor(asm_ddg);
    cout << "-------------------------------\n";

    // IR
    ir::CODE ir_code;
    IrObject.getFormattedCode(name, ir_code);
    ir::GRAPH ir_ddg;
    IrObject.DDAnalyze(ir_code, ir_ddg);
    IrObject.getColored(ir_ddg);
    IrObject.PrettyPrintCode(ir_code);
    cout << "-------------------------------\n";
    IrObject.PrettyPrintColor(ir_ddg);
    cout << "-------------------------------\n";
    // testIR(ir_code, ir_ddg);
  }
}
#endif
DEFINE_string(mode, "all", "mode: all, asm, ir.");
DEFINE_bool(batch, false, "batch process.");
DEFINE_string(asmfile, "case0", "if mode=asm/all and batch=False.");
DEFINE_string(asmgraph, "case0-asm.json", "if mode=asm and batch=False. A *.json is needed.");
DEFINE_string(irfile, "case0.ll", "if mode=all/ir and batch=False.");
DEFINE_string(irgraph, "case0-ir.json", "if mode=ir and batch=False.");
DEFINE_string(dir, "./", "if mode=all and batch=True.");
DEFINE_string(out, "case0-graph.json", "if mode=all and batch=False.");
DEFINE_int32(n_sample, 100000, "samples of batch. default=50000");

int main(int argc, char *argv[])
{
#ifdef DEBUG
  testASM(argv[1]);
#else
#ifdef DEBUGALL
  test(argv[1], argv[2]);
#else
#ifdef DEBUGIR
  testIR(argv[1]);
#else
  gflags::ParseCommandLineFlags(&argc, &argv, true);
#ifdef DEBUGASM
  if(FLAGS_batch == false || FLAGS_mode == "asm"){
#ifdef DEBUGASM
    getAsmSequence(FLAGS_asmfile, FLAGS_asmgraph);
#endif
  }
#else
#ifdef TRAIN
  if (FLAGS_batch == false || FLAGS_mode == "ir")
  {
    getIRSequence(FLAGS_irfile, FLAGS_irgraph);
  }
  else if (FLAGS_batch == true || FLAGS_mode == "all")
  {
    // optSimple(dir, 0);
    batchSimple(FLAGS_dir, FLAGS_n_sample);
  }
  else
  {
    std::cerr << "Invalid options. \n" << "Please use --help to get the usage of this tool." << std::endl;
  }
#endif //TRAIN
#endif
#endif
#endif  //DEBUG_ASM

#endif //DEBUG
  return 0;
}
