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

#include "commands.hpp"

using namespace llvm;


// const size_t PC_INC = 4;
const size_t NUM_REGS = 32;

struct LLSPU : public SPU {

    public: // inner structures
        std::unordered_map<int32_t, Value*> ssaMap;
        std::vector<Value*> regs;

    public: // llvm-referred
        std::unique_ptr<LLVMContext>& Ctx;
        BasicBlock* curBlock;

    public: // counters etc.
        uint32_t regCounter;
    public: // constructror
        LLSPU(size_t capIn, std::unique_ptr<LLVMContext>& CtxIn) : SPU(capIn), Ctx(CtxIn) {
            regCounter = 0;
            regs.resize(NUM_REGS);
        }

};


Value* LoadToReg        (int numReg, LLSPU& spu, LLVMContext &Ctx,                  IRBuilder<>& Builder);
Value *CreateXorToReg   (int numReg, Value *r1, Value *r2, LLSPU& spu,              IRBuilder<>& Builder);
Value *CreateCbitToReg  (int numReg, Value *rs, Value *offset, LLSPU& spu,          IRBuilder<>& Builder);
Value *CreateSubToReg   (int numReg, Value *rs, Value *imm, LLSPU& spu,             IRBuilder<>& Builder);
Value *CreateMovnToReg  (int numReg, Value *rd, Value *rs, Value *rt, LLSPU& spu,   IRBuilder<>& Builder);

void lljitXOR(ToyInstruction &command, LLSPU &SPU,  LLVMContext &Ctx, IRBuilder<>& Builder);
void lljitCBIT(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder);
void lljitSUBI(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder);
void lljitMOVN(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder);

using LLfuncIt = std::function<void (ToyInstruction&, LLSPU&, LLVMContext&, IRBuilder<>&)>;
static const std::unordered_map<uint32_t, LLfuncIt> OPCODE_LLMAP {
    {TOY_XOR,       lljitXOR         },
    {TOY_CBIT,      lljitCBIT        },
    {TOY_SUBI,      lljitSUBI        },
    {TOY_MOVN,      lljitMOVN        }

};


class LLSPUInstruction : public ToyInstruction {
    public:
    LLSPUInstruction(uint32_t command) : ToyInstruction(command) {}

    uint32_t getOpcode() const override {
        uint32_t opcode1 = (command >> OPCODE_OFFSET) & OPCODE_MASK;
        uint32_t opcode2 =  command & OPCODE_MASK;


        // std::cout << std::bitset<32>(opcode1) << "\n";
        // std::cout << std::bitset<32>(opcode2) << "\n";

        auto it1 = OPCODE_LLMAP.find(opcode1);
        auto it2 = OPCODE_LLMAP.find(opcode2);

        if (it1 != OPCODE_LLMAP.end()) {
            // ON_DEBUG(commandDump(it1->second, command));
            return it1->first;
        }
        else if (it2 != OPCODE_LLMAP.end()) {
            // ON_DEBUG(commandDump(it2->second, command));
            return it2->first;
        }

        return TOY_WRONG_OPCODE;
        }

};
