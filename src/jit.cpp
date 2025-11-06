#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

#include "errors.hpp"
#include "helper.hpp"

int main() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    auto jit = llvm::orc::LLJITBuilder().create();
    if (!jit) {
        llvm::errs() << "FAIL! JIT NOT CREATED: " << jit.takeError() << "\n";
    }

    auto context = std::make_unique<llvm::LLVMContext>();
    auto module = std::make_unique<llvm::Module>("jit_module", *context);

}

void translateBytecode(llvm::orc::LLJIT& jit, const std::vector<uint8_t> commands, size_t pc) {

}
