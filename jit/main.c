#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>

int main() {
    LLVMModuleRef module = LLVMModuleCreateWithName("test_module");
    printf("LLVM module created!\n");
    LLVMDisposeModule(module);
    return 0;
}
