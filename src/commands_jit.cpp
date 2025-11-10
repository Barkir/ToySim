#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"

#include <iostream>

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"

using namespace llvm;
using namespace llvm::orc;

void lljitXOR(ToyInstruction &command, LLSPU &SPU, LLVMContext &Ctx, Function *F) {
    BasicBlock *BB = &F->getEntryBlock();
    IRBuilder<> Builder(BB);

    if (BB->empty()) {
        Builder.SetInsertPoint(BB);
    } else {
        Builder.SetInsertPoint(&BB->back());
    }

    Value *RsVal = Builder.CreateLoad(Type::getInt32Ty(Ctx), SPU.regs[command.getFirstReg()], "rs_val");
    Value *RtVal = Builder.CreateLoad(Type::getInt32Ty(Ctx), SPU.regs[command.getSecondReg()], "rt_val");
    Value *XorResult = Builder.CreateXor(RsVal, RtVal, "xor_tmp");
    Builder.CreateStore(XorResult, SPU.regs[command.getThirdReg()]);
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
        ON_DEBUG(commandDump(it1->second, command));
        return it1->first;
    }
    else if (it2 != OPCODE_LLMAP.end()) {
        ON_DEBUG(commandDump(it2->second, command));
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}

