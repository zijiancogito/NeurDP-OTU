//===-- llvm-mc.cpp - Machine Code Hacking Driver ---------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This utility is a simple driver that allows command line hacking on machine
// code.
//
//===----------------------------------------------------------------------===//

#include "Disassembler.h"
#include "parser.h"

#include <sstream>
#include <iostream>
using namespace llvm;

static const Target *GetTarget(const char *ProgName) {
  // Figure out the target triple.
  Triple TheTriple(Triple::normalize("aarch64"));

  // Get the target specific parser.
  std::string Error;
  const Target *TheTarget = TargetRegistry::lookupTarget("aarch64", TheTriple,
                                                         Error);
  if (!TheTarget) {
    WithColor::error(errs(), ProgName) << Error;
    return nullptr;
  }

  // Update the triple name and return the found target.
  return TheTarget;
}

static std::unique_ptr<ToolOutputFile> GetOutputStream(StringRef Path, sys::fs::OpenFlags Flags) {
  std::error_code EC;
  auto Out = std::make_unique<llvm::ToolOutputFile>(Path, EC, Flags);
  if (EC) {
    WithColor::error() << EC.message() << '\n';
    return nullptr;
  }
  return Out;
}

static int AssembleInput(const char *ProgName, const Target *TheTarget,
                         SourceMgr &SrcMgr, MCContext &Ctx, MCStreamer &Str,
                         MCAsmInfo &MAI, MCSubtargetInfo &STI,
                         MCInstrInfo &MCII, MCTargetOptions const &MCOptions) {
  std::unique_ptr<MCAsmParser> Parser(
      createMCAsmParser(SrcMgr, Ctx, Str, MAI));
  std::unique_ptr<MCTargetAsmParser> TAP(
      TheTarget->createMCAsmParser(STI, *Parser, MCII, MCOptions));

  if (!TAP) {
    WithColor::error(errs(), ProgName)
        << "this target does not support assembly parsing.\n";
    return 1;
  }

  // int SymbolResult = fillCommandLineSymbols(*Parser);
  // if(SymbolResult)
  //   return SymbolResult;
  Parser->setTargetParser(*TAP);
  Parser->getLexer().setLexMasmIntegers(false);

  int Res = Parser->Run(false, true);

  return 0;
}

int parserInstruction(const MCTargetOptions &MCOptions, StringRef &InstStrRef, buffer_ostream &Out) {

  const char *ProgName = "./parser";
  const Target *TheTarget = GetTarget(ProgName);
  if (!TheTarget)
    return 1;
  // Now that GetTarget() has (potentially) replaced TripleName, it's safe to
  // construct the Triple object.
  Triple TheTriple("aarch64");
  ErrorOr<std::unique_ptr<MemoryBuffer>> BufferPtr =
      MemoryBuffer::getMemBufferCopy(InstStrRef);

  MemoryBuffer *Buffer = BufferPtr->get();

  SourceMgr SrcMgr;

  // Tell SrcMgr about this buffer, which is what the parser will pick up.
  SrcMgr.AddNewSourceBuffer(std::move(*BufferPtr), SMLoc());

  // Record the location of the include directories so that the lexer can find
  // it later.
  // SrcMgr.setIncludeDirs(IncludeDirs);

  std::unique_ptr<MCRegisterInfo> MRI(TheTarget->createMCRegInfo("aarch64"));
  assert(MRI && "Unable to create target register info!");

  std::unique_ptr<MCAsmInfo> MAI(
      TheTarget->createMCAsmInfo(*MRI, "aarch64", MCOptions));
  assert(MAI && "Unable to create target asm info!");

  MAI->setRelaxELFRelocations(false);

  MAI->setPreserveAsmComments(false);

  // FIXME: This is not pretty. MCContext has a ptr to MCObjectFileInfo and
  // MCObjectFileInfo needs a MCContext reference in order to initialize itself.
  MCObjectFileInfo MOFI;
  MCContext Ctx(MAI.get(), MRI.get(), &MOFI, &SrcMgr, &MCOptions);
  MOFI.InitMCObjectFileInfo(TheTriple, false, Ctx, false);

  Ctx.setGenDwarfForAssembly(false);
  // Default to 4 for dwarf version.
  unsigned DwarfVersion = MCOptions.DwarfVersion ? MCOptions.DwarfVersion : 4;
  if (DwarfVersion < 2 || DwarfVersion > 5) {
    errs() << ProgName << ": Dwarf version " << DwarfVersion
           << " is not supported." << '\n';
    return 1;
  }
  Ctx.setDwarfVersion(DwarfVersion);

  // Package up features to be passed to target/subtarget
  std::string FeaturesStr;

  sys::fs::OpenFlags Flags = (1) ? sys::fs::OF_Text: sys::fs::OF_None;
  raw_pwrite_stream *OS = &Out;
  // Out->keep();
  std::unique_ptr<MCStreamer> Str;

  std::unique_ptr<MCInstrInfo> MCII(TheTarget->createMCInstrInfo());
  std::unique_ptr<MCSubtargetInfo> STI(
      TheTarget->createMCSubtargetInfo("aarch64", "", FeaturesStr));

  MCInstPrinter *IP = nullptr;
  if (1) {
    IP = TheTarget->createMCInstPrinter(Triple("aarch64"), 0,
                                        *MAI, *MCII, *MRI);

    
    if (!IP) {
      WithColor::error()
          << "unable to create instruction printer for target triple '"
          << TheTriple.normalize() << "' with assembly variant " << ".\n";
      return 1;
    }

    // Set the display preference for hex vs. decimal immediates.
    IP->setPrintImmHex(false);

    // Set up the AsmStreamer.
    std::unique_ptr<MCCodeEmitter> CE;

    std::unique_ptr<MCAsmBackend> MAB(
        TheTarget->createMCAsmBackend(*STI, *MRI, MCOptions));
    auto FOut = std::make_unique<formatted_raw_ostream>(*OS);
    Str.reset(
        TheTarget->createAsmStreamer(Ctx, std::move(FOut), /*asmverbose*/ true,
                                     /*useDwarfDirectory*/ true, IP,
                                     std::move(CE), std::move(MAB), true));
    }
    
    int Res = AssembleInput(ProgName, TheTarget, SrcMgr, Ctx, *Str, *MAI, *STI, *MCII, MCOptions);
    
    
    return 0;
}

// int main(int argc, char **argv){
//   std::string s;
//   raw_string_ostream SS(s);
//   buffer_ostream Out(SS);
//   std::string inst = "adrp	x21, c";
//   StringRef ins(inst);
//   int res = parserInstruction(ins, Out);
//   llvm::outs() << Out.str() << "\n";
//   return 0;
// }