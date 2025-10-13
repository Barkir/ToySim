#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <bitset>

#include "errors.hpp"
#include "interpreter.hpp"
#include "commands.hpp"

const std::string filename = "../result.bin";
const size_t COMMAND_SIZE = 4;

int main(void) {

    std::vector<uint32_t> commands;
    if (get_commands(&commands, filename)) {
        return TOY_FAILED;
    }

    hexDump(commands);

    init(commands);
}

// -------------------------------------------------------------------------------------------

void init(std::vector<uint32_t> commands) {
    struct SPU spu = {};


    while (spu.pc < commands.size()) {
        auto command = commands[spu.pc];

    // for (auto command = commands.begin(); command != commands.end(); command++) {
        // hexDump(commands);

        // uint32 contains data in little-endian, i need to read these bytes
        // in big-endian
        uint32_t swappedCommand = swapEndian(command);

        uint32_t opcode = getOpcode(swappedCommand);
        auto it = OPCODE_MAP.find(opcode);

        switch (it->first) {
            case TOY_XOR:
                callXOR(spu, swappedCommand);
                spuDump(spu);
                break;
            case TOY_MOVN:
                callMOVN(spu, swappedCommand);
                spuDump(spu);
                break;

            case TOY_ADD:
                callADD(spu, swappedCommand);
                spuDump(spu);
                break;

            case TOY_SUBI:
                callSUBI(spu, swappedCommand);
                spuDump(spu);
                break;

            case TOY_JMP:
                callJMP(spu, swappedCommand);
                spuDump(spu);
                break;

            case TOY_BEQ:
                callBEQ(spu, swappedCommand);
                spuDump(spu);
                break;

            case TOY_SYSCALL:
                callSYSCALL(spu, swappedCommand);
                spuDump(spu);
                break;
        }
        // std::cout << it->second << "\n";
    }
}

// returns an array of 32-bit commands
enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error reading file: " << filename << "\n";
        return TOY_FILE_READ_ERROR;
    }

    size_t fSize = getFileSize(file);
    if (fSize % COMMAND_SIZE || fSize == 0) {
        std::cerr << "WRONG FILE SIZE " << fSize << "\n";
        file.close();
        return TOY_WRONG_FILE_SIZE;
    }

    if (file.is_open()) {
        std::vector<char> buffer(fSize);
        file.read(buffer.data(), fSize);
        hexDump(buffer);

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



