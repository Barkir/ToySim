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


const size_t PC_INC = 4;
const size_t NUM_REGS = 32;

struct LLSPU {
    std::vector<Value*> regs;
    uint32_t pc;
    size_t cap;

    LLSPU(size_t capIn) : cap(capIn), pc(0) {
        regs.reserve(NUM_REGS);
        for (int i = 0; i < NUM_REGS; i++) {
            Value *val = (Value*) calloc(sizeof(Value), 1);
            regs.push_back(val);
            ON_DEBUG(fprintf(stdout, "Allocated value %p and pushed it to vector.\n", val));
        }
    }
};

void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, Function *F);

using funcIt = std::function<void (ToyInstruction&, LLSPU&, LLVMContext&, Function*)>;
static const std::unordered_map<uint32_t, funcIt> OPCODE_LLMAP {
    {TOY_XOR,       lljitXOR         }
};
