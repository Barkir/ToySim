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
        spu.regs[numReg] = spu.Builder.CreateAlloca(Type::getInt32Ty(Ctx), nullptr, "r" + std::to_string(spu.regCounter++));
        Value *zero = spu.Builder.getInt32(0);
        spu.Builder.CreateStore(zero, spu.regs[numReg]);
    } else if (spu.ssaMap.find(numReg) != spu.ssaMap.end()) {
        return spu.ssaMap[numReg];
    }


    Value *retVal = spu.Builder.CreateLoad(Type::getInt32Ty(Ctx), spu.regs[numReg], "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;

    return retVal;
}

Value *CreateXorToReg(int numReg, Value *r1, Value *r2, LLSPU& spu) {
    Value *retVal = spu.Builder.CreateXor(r1, r2, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;

    return retVal;
}

Value *CreateCbitToReg(int numReg, Value *rs, Value *offset, LLSPU& spu) {
    Value *one = spu.Builder.getInt32(1);
    Value *firstOp = spu.Builder.CreateShl(one, offset, "r" + std::to_string(spu.regCounter++));
    Value *secondOp = spu.Builder.CreateAnd(firstOp, rs, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = secondOp;

    return secondOp;
}

Value *CreateSubToReg(int numReg, Value *rs, Value *imm, LLSPU& spu) {
    Value *retVal = spu.Builder.CreateSub(rs, imm, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;
    return retVal;
}

Value *CreateMovnToReg(int numReg, Value *rd, Value *rs, Value *rt, LLSPU& spu) {
    Value *zero = spu.Builder.getInt32(0);
    Value *icmp = spu.Builder.CreateICmpEQ(zero, rt);
    Value *retVal = spu.Builder.CreateSelect(icmp, rd, rs);
    spu.ssaMap[numReg] = retVal;
    return retVal;
}


void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx) {

    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx);
    Value *RtVal = LoadToReg(command.getSecondReg(), SPU, Ctx);
    Value *RdVal = CreateXorToReg(command.getThirdReg(), RsVal, RtVal, SPU);

    SPU.pc += PC_INC;
}

void lljitCBIT(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx) {
    Value *RsVal = LoadToReg(command.getSecondReg(), SPU, Ctx);
    Value *Imm5  = SPU.Builder.getInt32(command.getThirdReg());
    Value *Rd    = CreateCbitToReg(command.getFirstReg(), RsVal, Imm5, SPU);

    SPU.pc += PC_INC;
}

void lljitSUBI(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx) {
    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx);
    Value *Imm   = SPU.Builder.getInt32(command.getImm());
    Value * rt   = CreateSubToReg(command.getSecondReg(), RsVal, Imm, SPU);

    SPU.pc += PC_INC;
}

void lljitMOVN(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx) {
    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx);
    Value *RtVal = LoadToReg(command.getSecondReg(), SPU, Ctx);
    Value *RdVal = LoadToReg(command.getThirdReg(), SPU, Ctx);
    Value *Result = CreateMovnToReg(command.getThirdReg(), RdVal, RsVal, RtVal, SPU);

    SPU.pc += PC_INC;
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
        // ON_DEBUG(commandDump(it1->second, command));
        return it1->first;
    }
    else if (it2 != OPCODE_LLMAP.end()) {
        // ON_DEBUG(commandDump(it2->second, command));
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}

