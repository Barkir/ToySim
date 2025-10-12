#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

#include "errors.hpp"
#include "interpreter.hpp"

const std::string filename = "../result.bin";
const size_t COMMAND_SIZE = 4;

int main(void) {

    std::vector<uint32_t> commands;
    if (get_commands(&commands, filename)) {
        return TOY_FAILED;
    }
}

// -------------------------------------------------------------------------------------------

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

void hexDump(std::vector<char> buffer) {
    fprintf(stdout, RED "===========sup=============\n" RESET);
    fprintf(stdout, GREEN "▁▂▃▄▅▆▇▉ (.) (.) ▉▇▆▅▄▃▂▁\n" RESET);
    int cnt = 0;
    for (char& c: buffer) {
        if (cnt % 4 == 0) {
            fprintf(stdout, CYAN "\n 0x%-2X ->" RESET, cnt / 4);
        }
        fprintf(stdout, "%4X", c);
        cnt++;
    }
    fprintf(stdout, RED "\n\n===========bye=============\n" RESET);
}




