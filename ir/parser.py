import re
import os
import sys
import pdb
from multiprocessing import Pool

import json

REG = r'type\((.*)\) (.*)'
INST = r'Instruction (0x[0-9a-f]+) \:(.*)'
BB = r'BasicBlock\:\s([^\s]+)\n([\S\s]*)'
F = r'Function\:\s([^\s]+)([\S\s]*)ENDFunction'
FF = r'(Function\:([\S\s]+?)ENDFunction)'

def analyzeInstruction(inst):
  im = re.match(INST, inst)
  # print(inst)
  # pdb.set_trace()
  id = im[1]
  inst = im[2]
  tmp = inst.strip().split('  ')
  opcode = tmp[1]
  rm = re.match(REG, tmp[0].strip())
  ret = {'type': rm[1], 'value': rm[2]}
  operands = []
  for pair in tmp[2:]:
    m = re.match(REG, pair.strip())
    operands.append({'type': m[1], 'value': m[2]})
  return {'instruction': id, 'return': ret, 'opcode': opcode, 'operands': operands}

def analyzeBasicBlocks(bb):
  bm = re.match(BB, bb)
  addr = bm[1]
  insts = []
  for inst in bm[2].split('\n'):
    if inst.strip() != "":
      insts.append(analyzeInstruction(inst.strip()))
  return {'basicblock': addr, 'instructions': insts}

def analyzeFunction(func):
  # pdb.set_trace()
  fm = re.match(F, func)
  fname = fm[1]
  bbs = []
  for bb in fm[2].strip().split('\n\n'):
    # pdb.set_trace()
    if bb.strip() != "":
      bbs.append(analyzeBasicBlocks(bb))
  return {'function': fname, 'basicblocks': bbs}

def analyzeIRFile(inout):
  filename, outfile = inout
  with open(filename, 'r') as f:
    s = f.read()
    o = open(outfile, 'w')
    funcs = []
    for func in re.findall(FF, s):
      func = func[0]
      if func.strip() != "":
        funcs.append(analyzeFunction(func.strip()))

    json.dump({'filename': filename, 'functions': funcs}, o)
    o.close()

# - filename :
# - functions: [
#     - function: 
#     - basicblocks: [
#         - basicblock:
#         - instructions: [
#             - instruction:
#             - return:
#                 - type:
#                 - value:
#             - opcode:
#             - operands: [
#                 - type:
#                 - value:
#             ]
#         ]
#     ]
# ]

def file_path(dir, case, opt):
  return (os.path.join(os.path.abspath(dir), 
                       f'case{case}', 
                       f'o{opt}', 
                       f'main_o{opt}-simple.ll'),
      os.path.join(os.path.abspath(dir), 
                   f'case{case}', 
                   f'o{opt}', 
                   f'main_o{opt}-simple.json'))

def batchAnalyze(dir):
  files = []
  for i in range(20000):
    for j in range(3):
      files.append(file_path(dir, i, j))
  with Pool(20) as p:
    p.map(analyzeIRFile, files)

def main():
  if len(sys.argv) != 2:
    print("Usage: python parser.py <dir>.\n")
  batchAnalyze(sys.argv[1])

if __name__ == '__main__':
  main()