#include <iostream>
#include <vector>
#include <fstream>

#include "errors.hpp"

const std::string filename = "result.bin";

int main(void) {

    std::vector<uint32_t> commands;
    if (get_commands(&commands, filename)) {
        return TOY_FAIL;
    }
}

// returns an array of 32-bit commands
enum ErrorFlags get_commands(std::vector<uint32_t> *commands, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error reading file: " << filename << "\n";
        return TOY_FILE_READ_ERROR;
    }


}




