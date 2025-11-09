#pragma once

#include "llvm/IR/Value.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"

using namespace llvm;



struct LLSPU {
    std::vector<Value*> regs;
};

void lljitXOR(ToyInstruction &command, LLVMContext &Ctx, Function *F, LLSPU &SPU);
