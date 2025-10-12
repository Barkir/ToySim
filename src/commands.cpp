#include <cstdint>
#include <iostream>
#include <bitset>

#include "commands.hpp"

uint32_t swapEndian(uint32_t value) {
    return __builtin_bswap32(value);
}

uint32_t getOpcode(const uint32_t command) {

    // uint32 contains data in little-endian, i need to read these bytes
    // in big-endian
    uint32_t swappedCommand = swapEndian(command);

    // std::cout << std::bitset<32>(swappedCommand) << "\n";

    uint32_t opcode1 = swappedCommand & OPCODE_MASK;
    uint32_t opcode2 = (swappedCommand >> OPCODE_OFFSET) & OPCODE_MASK;


    // std::cout << std::bitset<32>(opcode1) << "\n";
    // std::cout << std::bitset<32>(opcode2) << "\n";

    auto it1 = OPCODE_MAP.find(opcode1);
    auto it2 = OPCODE_MAP.find(opcode2);

    if (it1 != OPCODE_MAP.end()) {
        return it1->first;
    }
    else if (it2 != OPCODE_MAP.end()) {
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}
