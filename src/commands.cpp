#include <cstdint>
#include <iostream>
#include <bitset>
#include <cstring>
#include <vector>

#include "errors.hpp"
#include "helper.hpp"
#include "commands.hpp"


uint32_t swapEndian(uint32_t value) {
    return __builtin_bswap32(value);
}

int32_t sign_extend(int32_t value, uint32_t bit_length) {
    if (bit_length >= 32)
        return value;

    uint32_t sign_bit = value & (1 << (bit_length - 1));

    if (sign_bit) {
        uint32_t mask = (1 << bit_length) - 1;
        return value | (~mask);
    } else {
        uint32_t mask = (1 << bit_length) - 1;
        return value & mask;
    }
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


void callXOR(SPU& spu, ToyInstruction command) {

    uint32_t rs = command.getFirstReg();  ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command.getSecondReg(); ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    uint32_t rd = command.getThirdReg();  ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET, rd));

//  -----------------------------------
    spu.regs[rd] = spu.regs[rs] ^ spu.regs[rt];
    spu.pc += PC_INC; // 1-byte addressing

    // handle pc incrementing
    // pc, next_pc
}

void callMOVN(SPU& spu, ToyInstruction command) {

    uint32_t rs = command.getFirstReg();  ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command.getSecondReg(); ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    uint32_t rd = command.getThirdReg();  ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET, rd));

//  -----------------------------------
    if (spu.regs[rt] != 0) {
        spu.regs[rd] = spu.regs[rs];
    }

    spu.pc += PC_INC;
}

void callADD(SPU& spu, ToyInstruction command) {

    uint32_t rs = command.getFirstReg();  ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command.getSecondReg(); ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    uint32_t rd = command.getThirdReg();  ON_DEBUG(fprintf(stdout, "rd = %d\n" RESET, rd));

//  -----------------------------------
    spu.regs[rd] = spu.regs[rs] + spu.regs[rt];
    spu.pc += PC_INC;
}

void callSYSCALL(SPU& spu, ToyInstruction command) {
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
    spu.pc += PC_INC;
}

void callSUBI(SPU& spu, ToyInstruction command) {

    uint32_t rs = command.getFirstReg();  ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command.getSecondReg(); ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    int32_t imm = command.getImm();       ON_DEBUG(fprintf(stdout, "imm = %d\n" RESET, imm));

//  -----------------------------------
    spu.regs[rt] = spu.regs[rs] - sign_extend(imm, IMM_SIZE);
    spu.pc += PC_INC;
}

void callJMP(SPU& spu, ToyInstruction command) {

    int16_t offset = command.getJmpOffset(); ON_DEBUG(fprintf(stdout, GREEN "\t offset = %d\n" RESET, offset));
    spu.pc = spu.pc + offset;
}

void callBEQ(SPU& spu, ToyInstruction command) {

    uint32_t rs = command.getFirstReg();      ON_DEBUG(fprintf(stdout, GREEN "\t rs = %d; ", rs));
    uint32_t rt = command.getSecondReg();     ON_DEBUG(fprintf(stdout, "rt = %d; ",         rt));
    int32_t offset = command.getBeqOffset();  ON_DEBUG(fprintf(stdout, "offset = %d\n" RESET, offset));

    //0x0000ffff <- signextension
    //0xffffffff

//  -----------------------------------
    if (spu.regs[rs] == spu.regs[rt]) {
        spu.pc += sign_extend(offset, BEQ_OFFSET_SIZE);
    } else {
        spu.pc += PC_INC;
    }
}

int32_t cbit(int32_t value, uint32_t offset) {
    return value & ~(1 << (offset));
}

void callCBIT(SPU& spu, ToyInstruction command) {

    uint32_t rd = command.getFirstReg();      ON_DEBUG(fprintf(stdout, GREEN "\t rd = %d; ", rd));
    uint32_t rs = command.getSecondReg();     ON_DEBUG(fprintf(stdout, "rs = %d; ",         rs));
    uint32_t imm5 = command.getThirdReg();    ON_DEBUG(fprintf(stdout, "imm5 = %d\n" RESET, imm5)); // TODO: find any way to handle bad naming


//  -----------------------------------
    spu.regs[rd] = cbit(spu.regs[rs], imm5); // that's magic 4sure
    spu.pc += PC_INC;

}

int32_t bext(int32_t rs1, int32_t rs2) {
    int32_t result = 0;
    int32_t bit_index = 0;

    for (int i = 0; i < REG_SIZE; i++) {
        if (rs2 & (1 << i)) {
            int32_t bit = (rs1 >> i) & i;

            result |= (bit << bit_index);
            bit_index++;
        }
    }

    return result;
}

void callBEXT(SPU& spu, ToyInstruction command) {

    uint32_t rd  = command.getFirstReg();     ON_DEBUG(fprintf(stdout, GREEN "\t rd = %d; ", rd));
    uint32_t rs1 = command.getSecondReg();    ON_DEBUG(fprintf(stdout, "rs1 = %d; ",         rs1));
    uint32_t rs2 = command.getThirdReg();     ON_DEBUG(fprintf(stdout, "rs2 = %d\n" RESET, rs2));

//  -----------------------------------

    spu.regs[rd] = bext(spu.regs[rs1], spu.regs[rs2]);
    spu.pc += PC_INC;
}

void callLDP(SPU& spu, ToyInstruction command) {

    uint32_t base   = command.getFirstReg();    ON_DEBUG(fprintf(stdout, GREEN "\t base = %d; ", base));
    uint32_t rt1    = command.getSecondReg();    ON_DEBUG(fprintf(stdout, "rt1 = %d; ",         rt1));
    uint32_t rt2    = command.getThirdReg();     ON_DEBUG(fprintf(stdout, "rt2 = %d; ", rt2));
    uint32_t offset = command.getLdpOffset(); ON_DEBUG(fprintf(stdout, "offset = %d\n" RESET, offset));

//  -----------------------------------
    int32_t addr  = spu.regs[base] + sign_extend(offset, LDP_OFFSET_SIZE);

    memcpy(&(spu.memory[addr]),   &spu.regs[rt1], sizeof(uint32_t));
    memcpy(&(spu.memory[addr+4]), &spu.regs[rt2], sizeof(uint32_t));

    spu.pc += PC_INC;
}

void callLD(SPU& spu, ToyInstruction command) {

    uint32_t base = command.getFirstReg();    ON_DEBUG(fprintf(stdout, GREEN "\t base = %d; ", base));
    uint32_t rt = command.getSecondReg();     ON_DEBUG(fprintf(stdout, "rt1 = %d; ",         rt));
    uint32_t offset = command.getLdOffset();  ON_DEBUG(fprintf(stdout, "offset = %d\n" RESET, offset));

//  -----------------------------------
    memcpy(&spu.regs[rt], &spu.memory[spu.regs[base] + sign_extend(offset, LD_OFFSET_SIZE)], sizeof(uint32_t));
    spu.pc += PC_INC;
}

uint32_t cls(int32_t rs) {
    uint32_t result = 0;
    for (int i = 0; i < REG_SIZE; i++) {
        result += (rs >> i) & 1;
    }

    return result;
}

void callCLS(SPU& spu, ToyInstruction command) {
    uint32_t rd = command.getFirstReg();    ON_DEBUG(fprintf(stdout, GREEN "\t rd = %d; ", rd));
    uint32_t rs = command.getSecondReg();   ON_DEBUG(fprintf(stdout, "rs = %d\n" RESET, rs));

//  -----------------------------------
    spu.regs[rd] = cls(spu.regs[rs]);
    spu.pc += PC_INC;
}

uint32_t rori(int32_t value, int32_t shift) {
    return (value >> (shift & 0x1F)) | (value << ((32 - shift) & 0x1F));
}

void callRORI(SPU& spu, ToyInstruction command) {
    uint32_t rd = command.getFirstReg();    ON_DEBUG(fprintf(stdout, GREEN "\t rd = %d; ", rd));
    uint32_t rs = command.getSecondReg();   ON_DEBUG(fprintf(stdout, "rs = %d; ", rs));
    int32_t imm5 = command.getThirdReg();   ON_DEBUG(fprintf(stdout, "imm5 = %d\n" RESET,  imm5));

//  -----------------------------------
    spu.regs[rd] = rori(spu.regs[rs], imm5);
    spu.pc += PC_INC;
}

void callST(SPU& spu, ToyInstruction command) {
    uint32_t base = command.getFirstReg();  ON_DEBUG(fprintf(stdout, GREEN "\t base = %d; ", base));
    uint32_t rt = command.getSecondReg();   ON_DEBUG(fprintf(stdout, "rt = %d; ", rt));
    int32_t offset = command.getStOffset(); ON_DEBUG(fprintf(stdout, "offset = %d\n" RESET, offset));
//  -----------------------------------
    memcpy(&spu.memory[spu.regs[base] + sign_extend(offset, ST_OFFSET_SIZE)], &spu.regs[rt], sizeof(uint32_t));
    spu.pc += PC_INC;
}


// ------------------------------------------------------#

uint32_t ToyInstruction::getOpcode() {

    // uint32 contains data in little-endian, i need to read these bytes
    // in big-endian

    // std::cout << std::bitset<32>(swappedCommand) << "\n";

    uint32_t opcode1 = (command >> OPCODE_OFFSET) & OPCODE_MASK;
    uint32_t opcode2 =  command & OPCODE_MASK;


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


