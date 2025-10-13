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
        ON_DEBUG(commandDump(it1->second, command));
        return it1->first;
    }
    else if (it2 != OPCODE_MAP.end()) {
        ON_DEBUG(commandDump(it2->second, command));
        return it2->first;
    }

    return TOY_WRONG_OPCODE;
}

void commandDump(std::string commandName, uint32_t command) {
    std::cout << CYAN << commandName << RESET << "\t" << std::bitset<32>(command) <<"\n";
}

void spuDump(SPU& spu) {
    fprintf(stdout, YELLOW "---------------------------------\n" RESET, spu.pc);
    fprintf(stdout, YELLOW "\tPC = %d\n" RESET, spu.pc);
    fprintf(stdout, BLUE "╔═══════════════════════════════╗\n║ " RESET);
    for (int i = 0; i < 32; i++) {
        if (i % 4 == 0 && i != 0) {
            fprintf(stdout, BLUE "║\n║ " RESET);
        }
        if (spu.regs[i] != 0)
            fprintf(stdout, GREEN "%-5d\t" RESET, spu.regs[i]);
        else
            fprintf(stdout, RED "%-5d\t" RESET, spu.regs[i]);
    }
    fprintf(stdout, BLUE "║\n╚═══════════════════════════════╝\n" RESET);
    fprintf(stdout, YELLOW "---------------------------------\n" RESET, spu.pc);
}


void callXOR(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; ON_DEBUG(fprintf(stdout, "rt = %d; ",         rt));
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET ,  rd));

    spu.regs[rd] = spu.regs[rs] ^ spu.regs[rt];
    spu.pc++;
}

void callMOVN(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; ON_DEBUG(fprintf(stdout, "rt = %d; ",         rt));
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET ,  rd));

    if (spu.regs[rt] != 0) {
        spu.regs[rd] = spu.regs[rs];
    }

    spu.pc++;
}

void callADD(SPU& spu, uint32_t command) {

    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; ON_DEBUG(fprintf(stdout, "rt = %d; ",         rt));
    uint32_t rd = command >> THIRD_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET ,  rd));

    spu.regs[rd] = spu.regs[rs] + spu.regs[rt];
    spu.pc++;
}

void callSYSCALL(SPU& spu, uint32_t command) {
    switch (spu.regs[TOY_R8]) {
        case TOY_PRINT:
            std::cout << spu.regs[TOY_R1] << "\n";
            break;

        case TOY_INPUT:
            int value = 0;
            std::cin >> value;
            spu.regs[TOY_R0] = value;
            break;
    }
    spu.pc++;
}

void callSUBI(SPU& spu, uint32_t command) {
    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK;   ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = (command >> SECOND_ARG_OFFSET) & REG_MASK; ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    int32_t imm = command & IMM_OFFSET;                      ON_DEBUG(fprintf(stdout, "imm = %d\n" RESET, imm));

    spu.regs[rt] = spu.regs[rs] - imm;
    spu.pc++;
}

void callJMP(SPU& spu, uint32_t command) {
    int16_t offset = command & JMP_OFFSET; ON_DEBUG(fprintf(stdout, GREEN "\t offset = %d\n" RESET, offset));
    spu.pc = spu.pc + offset;
}

void callBEQ(SPU& spu, uint32_t command) {
    uint32_t rs = command >> FIRST_ARG_OFFSET  & REG_MASK; ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command >> SECOND_ARG_OFFSET & REG_MASK; ON_DEBUG(fprintf(stdout, "rt = %d; ",         rt));
    int32_t offset = command & BEQ_OFFSET;                 ON_DEBUG(fprintf(stdout, "offset = %d\n" RESET, offset));

    if (spu.regs[rs] == spu.regs[rt]) {
        spu.pc += offset;
    } else {
        spu.pc++;
    }
}
