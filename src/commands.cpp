#include <cstdint>
#include <iostream>

#include "commands.hpp"

uint32_t swapEndian(uint32_t value) {
    return __builtin_bswap32(value);
}

enum toyCommands getOpcode(const uint32_t command) {

    uint32_t swapped = swapEndian(command);

    fprintf(stdout, "%x %b %b\n", swapped, swapped, swapped >> 27);
    uint32_t opcode1 = swapped & OPCODE_MASK;
    uint32_t opcode2 = (swapped >> OPCODE_OFFSET) & OPCODE_MASK;

    fprintf(stdout, "OPCODE1: %b\nOPCODE2: %b\n", opcode1, opcode2);
    auto it = OPCODE_MAP.find(opcode1);
    if (it != OPCODE_MAP.end())
        std::cout << it->second << "\n";
    return TOY_JMP;
}
