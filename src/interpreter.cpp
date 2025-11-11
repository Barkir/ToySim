#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <cstring>

#include "errors.hpp"
#include "interpreter.hpp"
#include "helper.hpp"
#include "commands.hpp"

const std::string filename = "../result.bin";

int main(int argc, char* argv[]) {

    if (argc >= 2)
    {
        std::string filename = argv[1]; // not a magic number :)
        std::vector<uint32_t> commands;
        size_t fsize = 0;
        if (get_commands(&commands, filename, &fsize)) {
            return TOY_FAILED;
        }

        ON_DEBUG(hexDump(commands));
        init(commands, fsize);
    }
}

// -------------------------------------------------------------------------------------------

uint32_t getCommand(const std::vector<uint8_t> commands, size_t pc) {
    uint32_t command = 0;
    memcpy(&command, &commands[pc], 4);
    return command;
}

void init(std::vector<uint32_t> commands, size_t fsize) {
    struct SPU spu(fsize);

    std::vector<uint8_t>  commands_1byte(commands.size() * sizeof(uint32_t));
    memcpy(commands_1byte.data(), commands.data(), commands_1byte.size());

    size_t cm_sz = commands_1byte.size();
    while (spu.pc < cm_sz) {

        auto command = getCommand(commands_1byte, spu.pc);
        ToyInstruction commandObj(command);

        uint32_t opcode = commandObj.getOpcode();
        auto it = OPCODE_MAP.find(opcode);
        // it->second(spu, commandObj);
        // ON_DEBUG(spuDump(spu));

        switch (it->first) {
            case TOY_XOR:
                callXOR(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;
            case TOY_MOVN:
                callMOVN(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_ADD:
                callADD(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_SUBI:
                callSUBI(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_JMP:
                callJMP(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_BEQ:
                callBEQ(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_SYSCALL:
                callSYSCALL(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_LD:
                callLD(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_LDP:
                callLDP(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_CLS:
                callCLS(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_RORI:
                callRORI(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;

            case TOY_ST:
                callST(spu, commandObj);
                ON_DEBUG(spuDump(spu));
                break;
        }


    }

}


