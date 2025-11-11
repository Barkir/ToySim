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
#include <unordered_map>

using namespace llvm;


const size_t PC_INC = 4;
const size_t NUM_REGS = 32;

struct LLSPU {

    public: // inner structures
        std::unordered_map<int32_t, Value*> ssaMap;
        std::vector<Value*> regs;

    public: // counters etc.
        uint32_t pc;
        size_t cap;
        uint32_t regCounter;

    public: // llvm-referred
        std::unique_ptr<LLVMContext>& Ctx;
        IRBuilder<>& Builder;
        BasicBlock* curBlock;

    public: // constructror
        LLSPU(size_t capIn, std::unique_ptr<LLVMContext>& CtxIn, IRBuilder<>& BuilderIn) : cap(capIn), Ctx(CtxIn), pc(0),
                                                                                           Builder(BuilderIn), regCounter(0) {
            regs.resize(NUM_REGS);
        }

};

void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx);
void lljitCBIT(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx);
void lljitSUBI(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx);

using funcIt = std::function<void (ToyInstruction&, LLSPU&, LLVMContext&)>;
static const std::unordered_map<uint32_t, funcIt> OPCODE_LLMAP {
    {TOY_XOR,       lljitXOR         },
    {TOY_CBIT,      lljitCBIT        },
    {TOY_SUBI,      lljitSUBI        }
};
