#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <cstring>

#include "errors.hpp"
#include "interpreter.hpp"
#include "commands.hpp"

const std::string filename = "../result.bin";
const size_t COMMAND_SIZE = 4;

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
        Instruction commandObj(command);

        uint32_t opcode = commandObj.getOpcode();
        auto it = OPCODE_MAP.find(opcode);

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

// returns an array of 32-bit commands
enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename, size_t *fsz) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error reading file: " << filename << "\n";
        return TOY_FILE_READ_ERROR;
    }

    size_t fSize = getFileSize(file);
    *fsz = fSize;
    if (fSize % COMMAND_SIZE || fSize == 0) {
        std::cerr << "WRONG FILE SIZE " << fSize << "\n";
        file.close();
        return TOY_WRONG_FILE_SIZE;
    }

    if (file.is_open()) {
        std::vector<char> buffer(fSize);
        file.read(buffer.data(), fSize);
        ON_DEBUG(hexDump(buffer));

        *commands = std::vector<uint32_t>(
        reinterpret_cast<const uint32_t*>(buffer.data()),
        reinterpret_cast<const uint32_t*>(buffer.data()) + fSize / COMMAND_SIZE
        );

        return TOY_SUCCESS;
    }
    return TOY_FAILED;
}

// -----------------------------------------------------------------------------------------------

size_t getFileSize(std::ifstream& file) {
    if (!file.is_open()) return 0;

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    return size;
}

template<typename T>
void hexDump(const std::vector<T>& buffer) {
    fprintf(stdout, RED "╔═══════════════════════════════════╗\n" RESET);
    fprintf(stdout, RED "║" GREEN "  ▁▂▃▄▅▆▇▉ HEX DUMP ▉▇▆▅▄▃▂▁  " RED "║\n" RESET);
    fprintf(stdout, RED "╚═══════════════════════════════════╝\n" RESET);

    const unsigned char* rawData = reinterpret_cast<const unsigned char*>(buffer.data());
    size_t totalBytes = buffer.size() * sizeof(T);

    int cnt = 0;
    for (size_t i = 0; i < totalBytes; i++) {
        if (cnt % 4 == 0) {
            fprintf(stdout, CYAN "\n  0x%02X → " RESET, cnt / 4);
        }
        fprintf(stdout, MAGENTA "%02X " RESET, rawData[i]);
        cnt++;
    }

    fprintf(stdout, YELLOW "\n\n╔═══════════════════════════════════╗\n" RESET);
    fprintf(stdout, YELLOW "║" BLUE "    Items: %3zu | Bytes: %3zu    " YELLOW "║\n" RESET, buffer.size(), totalBytes);
    fprintf(stdout, YELLOW "╚═══════════════════════════════════╝\n" RESET);
}



