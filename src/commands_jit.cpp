#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constant.h"

#include <iostream>

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"

using namespace llvm;
using namespace llvm::orc;



Value* LoadToReg(int numReg, LLSPU& spu, LLVMContext &Ctx) {
    if (spu.regs[numReg] == nullptr) {
        spu.regs[numReg] = spu.Builder.CreateAlloca(Type::getInt32Ty(Ctx), nullptr, "r" + std::to_string(spu.regCounter));
        Constant* constInt32 = ConstantInt::get(Type::getInt32Ty(Ctx), 0);
        spu.Builder.CreateStore(constInt32, spu.regs[numReg]);
        spu.regCounter++;
    }

    Value *retVal = spu.Builder.CreateLoad(Type::getInt32Ty(Ctx), spu.regs[numReg], "r" + std::to_string(spu.regCounter));
    spu.ssaMap[numReg] = retVal;
    spu.regCounter++;
    return retVal;
}

Value *CreateXorToReg(int numReg, Value *r1, Value *r2, LLSPU& spu) {
    Value *retVal = spu.Builder.CreateXor(r1, r2, "r" + std::to_string(spu.regCounter));
    spu.ssaMap[numReg] = retVal;
    spu.regCounter++;
    return retVal;
}

void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, Function *F) {
    BasicBlock *BB = &F->getEntryBlock();
    IRBuilder<> Builder(BB);

    if (BB->empty()) {
        Builder.SetInsertPoint(BB);
    } else {
        Builder.SetInsertPoint(&BB->back());
    }

    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx);
    Value *RtVal = LoadToReg(command.getSecondReg(), SPU, Ctx);
    Value *RdVal = CreateXorToReg(command.getThirdReg(), RsVal, RtVal, SPU);

    SPU.pc += PC_INC;
}

void lljitCBIT(ToyInstruction &commands, LLSPU &SPU, LLVMContext &Ctx, Function *F) {

}

// ----------------------------------------------------------#

uint32_t ToyInstruction::getOpcode() {
    uint32_t opcode1 = (command >> OPCODE_OFFSET) & OPCODE_MASK;
    uint32_t opcode2 =  command & OPCODE_MASK;


    // std::cout << std::bitset<32>(opcode1) << "\n";
    // std::cout << std::bitset<32>(opcode2) << "\n";

    auto it1 = OPCODE_LLMAP.find(opcode1);
    auto it2 = OPCODE_LLMAP.find(opcode2);

    if (it1 != OPCODE_LLMAP.end()) {
        ON_DEBUG(commandDump(it1->second, command));
        return it1->first;
    }
    else if (it2 != OPCODE_LLMAP.end()) {
        ON_DEBUG(commandDump(it2->second, command));
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}

