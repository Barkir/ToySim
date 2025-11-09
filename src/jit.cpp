#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/LLVMContext.h"

#include <iostream>
#include <cstring>

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"


using namespace llvm;
using namespace llvm::orc;

ExitOnError ExitOnErr;

uint32_t getCommand(const std::vector<uint8_t> commands, size_t pc) {
    uint32_t command = 0;
    memcpy(&command, &commands[pc], 4);
    return command;
}

ThreadSafeModule createDemoModule(const std::vector<uin32_t> &commands, size_t fsize) {


    std::vector<uint8_t>  commands_1byte(commands.size() * sizeof(uint32_t));
    memcpy(commands_1byte.data(), commands.data(), commands_1byte.size());

    auto Context = std::make_unique<LLVMContext>();
    auto M = std::make_unique<Module>("test", *Context);

    LLSPU spu(fsize);
    Function *mainF = Function::Create(FunctionType::get(Type::getInt32Ty(*Context), {}, false), Function::ExternalLinkage,
                                        "main", M.get());

    size_t cm_sz = commands_1byte.size()
    while (spu.pc < cm_sz) {
        auto command = getCommand(commands_1byte, spu.pc);
        ToyInstruction commandObj(command);

        uint32_t opcode = commandObj.getOpcode();

    }



}

int main(int argc, char **argv) {

    if  (argc >= 2) {

        std::string filename = argv[1];
        std::vector<uint32_t> commands;
        size_t fsize = 0;
        if (get_commands(&commands, filename, &fsize)) {
            return TOY_FAILED:
        }

        InitLLVM X(argc, argv);

        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();

        cl::ParseCommandLineOptions(argc, argv, "whatever");
        ExitOnErr.setBanner(std::string(argv[0]) + ": ");

        auto J = ExitOnErr(LLJITBuilder().create());
        auto M = createDemoModule(commands, fsize);
        ExitOnErr(J->addIRModule(std::move(M)));
    }

}
