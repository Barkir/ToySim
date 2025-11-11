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
// this function is not working correct for all cases
// it is createad for better architecture in the future
// now all of the instructions are in the same basic block (cuz im bad at writing branches 4now)
BasicBlock* setCurrentBasicBlock(LLSPU& spu, Function *F) {
    spu.curBlock = &F->getEntryBlock();
    return spu.curBlock;
}

void setInsertPoint(LLSPU& spu) {
    if (spu.curBlock->empty()) {
        spu.Builder.SetInsertPoint(spu.curBlock);
    } else {
        spu.Builder.SetInsertPoint(&spu.curBlock->back());
    }
}

ThreadSafeModule createDemoModule(const std::vector<uint32_t> &commands, size_t fsize) {


    std::vector<uint8_t>  commands_1byte(commands.size() * sizeof(uint32_t));
    memcpy(commands_1byte.data(), commands.data(), commands_1byte.size());

    auto Context = std::make_unique<LLVMContext>();
    auto M = std::make_unique<Module>("test", *Context);

    Function *mainF = Function::Create(FunctionType::get(Type::getInt32Ty(*Context), {}, false), Function::ExternalLinkage,
                                        "main", M.get());
    BasicBlock *BB = BasicBlock::Create(*Context, "entryAF", mainF);
    IRBuilder<> builder(BB);
    LLSPU spu(fsize, Context, builder);

    size_t cm_sz = commands_1byte.size();
    while (spu.pc < cm_sz) {
        auto command = getCommand(commands_1byte, spu.pc);
        ToyInstruction commandObj(command);

        std::cerr << spu.pc << " vs " << cm_sz << "\n";
        uint32_t opcode = commandObj.getOpcode();

        setCurrentBasicBlock(spu, mainF);
        setInsertPoint(spu);

        switch (opcode) {
            case TOY_XOR:
                lljitXOR(commandObj, spu, *Context);
                break;
            case TOY_CBIT:
                lljitXOR(commandObj, spu, *Context);

            case TOY_SUBI:
                lljitSUBI(commandObj, spu, *Context);
        }
    }
    fprintf(stderr, "IN THE END\n");
    Value *Zero = builder.getInt32(0);
    builder.CreateRet(Zero);

    outs() << *mainF;
    return ThreadSafeModule(std::move(M), std::move(Context));
}

int main(int argc, char **argv) {
    std::vector<std::string> original_args;
    for (int i = 0; i < argc; ++i) {
        original_args.push_back(argv[i]);
    }

    if  (argc >= 2) {

        std::string filename = argv[1];
        std::vector<uint32_t> commands;
        size_t fsize = 0;
        if (get_commands(&commands, filename, &fsize)) {
            return TOY_FAILED;
        }

        InitLLVM X(argc, argv);

        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();

        // std::string output_filename = "output_" + dyn_cast<std::string>(argv[1]) + ".ll";

        // cl::ParseCommandLineOptions(argc, argv, "whatever");
        // ExitOnErr.setBanner(std::string(argv[0]) + ": ");

        auto J = ExitOnErr(LLJITBuilder().create());
        auto M = createDemoModule(commands, fsize);
        ExitOnErr(J->addIRModule(std::move(M)));
    }
}
