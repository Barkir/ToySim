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
#include <unordered_map>
#include <functional>

#include "errors.hpp"
#include "helper.hpp"
#include "commands_jit.hpp"
// #include "commands.hpp"

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
// BasicBlock* setCurrentBasicBlock(LLSPU& spu, Function *F) {
//     spu.curBlock = &F->getEntryBlock();
//     return spu.curBlock;
// }
//
// void setInsertPoint(LLSPU& spu) {
//     if (spu.curBlock->empty()) {
//         spu.Builder.SetInsertPoint(spu.curBlock);
//     } else {
//         spu.Builder.SetInsertPoint(&spu.curBlock->back());
//     }
// }

ThreadSafeModule createModule(LLSPU& spu, ToyInstruction& commandObj, const std::string funcName) {
    auto Context = std::make_unique<LLVMContext>();
    auto M = std::make_unique<Module>("jit", *Context);

    Function *mainF = Function::Create(FunctionType::get(Type::getInt32Ty(*Context), {}, false),
                                       Function::ExternalLinkage,
                                       funcName,
                                       M.get());

    BasicBlock *BB = BasicBlock::Create(*Context, "entry", mainF);
    IRBuilder<> builder(BB);

    switch (commandObj.getOpcode()) {
        case TOY_XOR:
            lljitXOR(commandObj, spu, *Context, builder);
            break;

        case TOY_SUBI:
            lljitSUBI(commandObj, spu, *Context, builder);
            break;

        case TOY_MOVN:
            lljitMOVN(commandObj, spu, *Context, builder);
            break;
        }
}

// ThreadSafeModule createDemoModule(const std::vector<uint32_t> &commands, size_t fsize) {
//
//
//     std::vector<uint8_t>  commands_1byte(commands.size() * sizeof(uint32_t));
//     memcpy(commands_1byte.data(), commands.data(), commands_1byte.size());
//
//     auto Context = std::make_unique<LLVMContext>();
//     auto M = std::make_unique<Module>("test", *Context);
//
//     Function *mainF = Function::Create(FunctionType::get(Type::getInt32Ty(*Context), {}, false), Function::ExternalLinkage,
//                                         "main", M.get());
//
//     BasicBlock *BB = BasicBlock::Create(*Context, "entryAF", mainF);
//     IRBuilder<> builder(BB);
//     LLSPU spu(fsize, Context, builder);
//
//     size_t cm_sz = commands_1byte.size();
//     while (spu.pc < cm_sz) {
//         auto command = getCommand(commands_1byte, spu.pc);
//         ToyInstruction commandObj(command);
//
//         std::cerr << spu.pc << " vs " << cm_sz << "\n";
//         uint32_t opcode = commandObj.getOpcode();
//
//         setCurrentBasicBlock(spu, mainF);
//         setInsertPoint(spu);
//
//         switch (opcode) {
//             case TOY_XOR:
//                 lljitXOR(commandObj, spu, *Context);
//                 break;
//             case TOY_CBIT:
//                 lljitXOR(commandObj, spu, *Context);
//                 break;
//
//             case TOY_SUBI:
//                 lljitSUBI(commandObj, spu, *Context);
//                 break;
//
//             case TOY_MOVN:
//                 lljitMOVN(commandObj, spu, *Context);
//                 break;
//         }
//     }
//     fprintf(stderr, "IN THE END\n");
//     Value *Zero = builder.getInt32(0);
//     builder.CreateRet(Zero);
//
//     outs() << *mainF;
//     return ThreadSafeModule(std::move(M), std::move(Context));
// }

std::string generateFunctionName(uint32_t opcode, uint32_t pc) {
    std::stringstream resultStream;

    resultStream << "opcode" << opcode << "pc" << pc;

    return resultStream.str();
}

void runProcessor(const std::vector<uint32_t> &commands, size_t fsize) {

    std::vector<uint8_t>  commands_1byte(commands.size() * sizeof(uint32_t));
    memcpy(commands_1byte.data(), commands.data(), commands_1byte.size());

    auto context = std::make_unique<LLVMContext>();

    LLSPU spu(fsize, context);

    std::unordered_map<uint32_t, int> hot_instructions;
    // std::unordered_map<uint32_t, > hot_binaries;

    size_t cm_sz = commands_1byte.size();
    while (spu.pc < cm_sz) {


        auto command = getCommand(commands_1byte, spu.pc);
        LLSPUInstruction commandObj(command);

        // std::cerr << spu.pc << " vs " << cm_sz << "\n";
        uint32_t opcode = commandObj.getOpcode();

        ++hot_instructions[spu.pc];
        if (hot_instructions[spu.pc] > JIT_THRESHOLD) {
            // call binary translation
            // hot_binaries[spu.pc]();
            continue;
        }

        if (hot_instructions[spu.pc] == JIT_THRESHOLD) {
            // creating a builder to contain binary there
            auto J = ExitOnErr(LLJITBuilder().create());

            std::string functionName = generateFunctionName(opcode, spu.pc);
            auto tsm = createModule(spu, commandObj, functionName);
        }
        switch (opcode) {
            case TOY_XOR:
                // callXOR(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_MOVN:
                // callMOVN(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_ADD:
                // callADD(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_SUBI:
                // callSUBI(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_JMP:
                // callJMP(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_BEQ:
                // callBEQ(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_SYSCALL:
                // callSYSCALL(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_LD:
                // callLD(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_LDP:
                // callLDP(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_CLS:
                // callCLS(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_RORI:
                // callRORI(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_ST:
                // callST(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_CBIT:
                // callCBIT(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;
        }
    }

    std::cout << "HALT. <<:" << std::endl;
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

        auto J = ExitOnErr(LLJITBuilder().create());

        runProcessor(commands, fsize);

        // ExitOnErr(J->addIRModule(std::move(M)));

    }
}
