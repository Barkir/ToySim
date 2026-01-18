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



Value* LoadToReg(int numReg, LLSPU& spu, LLVMContext &Ctx, IRBuilder<>& Builder) {
    if (spu.regs[numReg] == nullptr) {
        spu.regs[numReg] = Builder.CreateAlloca(Type::getInt32Ty(Ctx), nullptr, "r" + std::to_string(spu.regCounter++));
        Value *zero = Builder.getInt32(0);
        Builder.CreateStore(zero, spu.regs[numReg]);
    } else if (spu.ssaMap.find(numReg) != spu.ssaMap.end()) {
        return spu.ssaMap[numReg];
    }


    Value *retVal = Builder.CreateLoad(Type::getInt32Ty(Ctx), spu.regs[numReg], "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;

    return retVal;
}

Value *CreateXorToReg(int numReg, Value *r1, Value *r2, LLSPU& spu, IRBuilder<>& Builder) {
    Value *retVal = Builder.CreateXor(r1, r2, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;

    return retVal;
}

Value *CreateCbitToReg(int numReg, Value *rs, Value *offset, LLSPU& spu, IRBuilder<>& Builder) {
    Value *one = Builder.getInt32(1);
    Value *firstOp = Builder.CreateShl(one, offset, "r" + std::to_string(spu.regCounter++));
    Value *secondOp= Builder.CreateAnd(firstOp, rs, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = secondOp;

    return secondOp;
}

Value *CreateSubToReg(int numReg, Value *rs, Value *imm, LLSPU& spu, IRBuilder<>& Builder) {
    Value *retVal = Builder.CreateSub(rs, imm, "r" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;
    return retVal;
}

Value *CreateMovnToReg(int numReg, Value *rd, Value *rs, Value *rt, LLSPU& spu, IRBuilder<>& Builder) {
    Value *zero = Builder.getInt32(0);
    Value *icmp = Builder.CreateICmpEQ(zero, rt, "icmp" + std::to_string(spu.regCounter));
    Value *retVal = Builder.CreateSelect(icmp, rd, rs, "select" + std::to_string(spu.regCounter++));
    spu.ssaMap[numReg] = retVal;
    return retVal;
}
//
// Value *CreateBextReg(int numReg, Value *rs1, Value *rs2, LLSPU &spu) {
//     Value *REG_ALLOCA = spu.Builder.CreateAlloca(Type::getInt32Ty(spu.Ctx), nullptr, "r" + std::to_string(spu.regCounter++));
//     Value *StoreReg   = spu.Builder.CreateStore(spu.Builder.getInt32(32), REG_ALLOCA);
//
//     Value *I_ALLOCA = spu.Builder.CreateAlloca(Type::getInt32Ty(spu.Ctx), nullptr, "r" + std::to_string(spu.regCounter++));
//     Value *StoreReg   = spu.Builder.CreateStore(spu.Builder.getInt32(0), REG_ALLOCA);
//
//     BasicBlock *cycle = BasicBlock::Create(ctx, "BextCycle" + std::to_string(spu.regCounter++));
// }


void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder) {

    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx, Builder);
    Value *RtVal = LoadToReg(command.getSecondReg(), SPU, Ctx, Builder);
    Value *RdVal = CreateXorToReg(command.getThirdReg(), RsVal, RtVal, SPU, Builder);

    SPU.pc += PC_INC;
}

void lljitCBIT(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder) {
    Value *RsVal = LoadToReg(command.getSecondReg(), SPU, Ctx, Builder);
    Value *Imm5  = Builder.getInt32(command.getThirdReg());
    Value *Rd    = CreateCbitToReg(command.getFirstReg(), RsVal, Imm5, SPU, Builder);

    SPU.pc += PC_INC;
}

void lljitSUBI(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder) {
    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx, Builder);
    Value *Imm   = Builder.getInt32(command.getImm());
    Value * rt   = CreateSubToReg(command.getSecondReg(), RsVal, Imm, SPU, Builder);

    SPU.pc += PC_INC;
}

void lljitMOVN(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder) {
    Value *RsVal = LoadToReg(command.getFirstReg(), SPU, Ctx, Builder);
    Value *RtVal = LoadToReg(command.getSecondReg(), SPU, Ctx, Builder);
    Value *RdVal = LoadToReg(command.getThirdReg(), SPU, Ctx, Builder);
    Value *Result = CreateMovnToReg(command.getThirdReg(), RdVal, RsVal, RtVal, SPU, Builder);

    SPU.pc += PC_INC;
}

void lljitSYSCALL(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, IRBuilder<>& Builder) {

}

// void lljitBEXT(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx) {
//     Value *Rs1 = LoadToReg(command.getSecondReg(), SPU, Ctx);
//     Value *Rs2 = LoadToReg(command.getThirdReg(), SPU, Ctx);
//     Value *Rd  = CreateBextToReg(command.getFirstReg(), Rs1, Rs2, SPU);
// }

// ----------------------------------------------------------#

