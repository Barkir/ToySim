#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"

using namespace llvm;
using namespace llvm::orc;

void lljitXOR(ToyInstruction &command, LLVMContext &Ctx, Function *F, LLSPU &SPU) {
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
}
