#include <cstdint>
#include <iostream>
#include <bitset>

#include "commands.hpp"
#include "errors.hpp"

uint32_t swapEndian(uint32_t value) {
    return __builtin_bswap32(value);
}

uint32_t getOpcode(const uint32_t command) {

    // uint32 contains data in little-endian, i need to read these bytes
    // in big-endian

    // std::cout << std::bitset<32>(swappedCommand) << "\n";

    uint32_t opcode1 = (command >> OPCODE_OFFSET) & OPCODE_MASK;
    uint32_t opcode2 = command & OPCODE_MASK;


    // std::cout << std::bitset<32>(opcode1) << "\n";
    // std::cout << std::bitset<32>(opcode2) << "\n";

    auto it1 = OPCODE_MAP.find(opcode1);
    auto it2 = OPCODE_MAP.find(opcode2);

    if (it1 != OPCODE_MAP.end()) {
        std::cout << CYAN << it1->second << RESET << "\t" << std::bitset<32>(command) <<"\n";
        return it1->first;
    }
    else if (it2 != OPCODE_MAP.end()) {
        std::cout << MAGENTA << it2->second << RESET << "\t" << std::bitset<32>(command) <<"\n";
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}

void spuDump(SPU& spu) {
    fprintf(stdout, YELLOW "---------------------------------\n" RESET, spu.pc);
    fprintf(stdout, YELLOW "\tPC = %d\n" RESET, spu.pc);
    fprintf(stdout, BLUE "╔═══════════════════════════════╗\n║ " RESET);
    for (int i = 0; i < sizeof(spu.regs) / sizeof(uint32_t); i++) {
        if (i % 4 == 0 && i != 0) {
            fprintf(stdout, BLUE "║\n║ " RESET);
        }
        if (spu.regs[i])
            fprintf(stdout, GREEN "%-5d\t" RESET, spu.regs[i]);
        else
            fprintf(stdout, RED "%-5d\t" RESET, spu.regs[i]);
    }
    fprintf(stdout, BLUE "║\n╚═══════════════════════════════╝\n" RESET);
    fprintf(stdout, YELLOW "---------------------------------\n" RESET, spu.pc);
}


void callXOR(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; fprintf(stdout, GREEN "\t rs = %d; ", rs);
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; fprintf(stdout, "rt = %d; ",         rt);
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; fprintf(stdout, "rd = %d\n" RESET ,  rd);

    spu.regs[rd] = spu.regs[rs] ^ spu.regs[rt];
    spu.pc++;
}

void callMOVN(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; fprintf(stdout, GREEN "\t rs = %d; ", rs);
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; fprintf(stdout, "rt = %d; ",         rt);
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; fprintf(stdout, "rd = %d\n" RESET ,  rd);

    if (spu.regs[rt] != 0) {
        spu.regs[rd] = spu.regs[rs];
    }

    spu.pc++;
}

void callADD(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; fprintf(stdout, GREEN "\t rs = %d; ", rs);
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; fprintf(stdout, "rt = %d; ",         rt);
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; fprintf(stdout, "rd = %d\n" RESET ,  rd);

    spu.regs[rd] = spu.regs[rs] + spu.regs[rt];
    spu.pc++;
}
