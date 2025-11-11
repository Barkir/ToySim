#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <bitset>
#include <cstring>

#include "errors.hpp"

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

size_t getFileSize(std::ifstream& file);
enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename, size_t *fsz);

// -----------------------------------------------------------------------------------------------



enum commandHelpers {
    FIRST_REG           = 1,
    SECOND_REG          = 2,
    THIRD_REG           = 3,
    UNKNOWN_REG         = -1,
    OPCODE_MASK         = 0x3F,
    REG_MASK            = 0x1F,
    FIRST_ARG_OFFSET    = 21,
    SECOND_ARG_OFFSET   = 16,
    THIRD_ARG_OFFSET    = 11,
    OPCODE_OFFSET       = 26,
    JMP_OFFSET          = 0x3FFFFFF,
    IMM_OFFSET          = 0xFFFF,
    BEQ_OFFSET          = 0xFFFF,
    LDP_OFFSET          = 0x7FF,
    LD_OFFSET           = 0xFFFF,
    ST_OFFSET           = 0xFFFF

};

enum toyCommands {
    TOY_JMP     =0b010111,
    TOY_CBIT    =0b111011,
    TOY_SUBI    =0b001111,
    TOY_MOVN    =0b000101,
    TOY_BEQ     =0b100110,
    TOY_BEXT    =0b110110,
    TOY_LDP     =0b001110,
    TOY_ADD     =0b000110,
    TOY_LD      =0b100010,
    TOY_CLS     =0b101101,
    TOY_RORI    =0b111111,
    TOY_ST      =0b111010,
    TOY_XOR     =0b011011,
    TOY_SYSCALL =0b000111,

    TOY_WRONG_OPCODE=-1
};


class ToyInstruction {
    private:
        uint32_t command;
        uint32_t rd;
        uint32_t imm;
        uint32_t rs1;
        uint32_t rs2;

    public: // constructor
        ToyInstruction(uint32_t commandIn) : command(commandIn) {}


    public: // get functions

        uint32_t getFirstReg()    {
            rd = command >> FIRST_ARG_OFFSET  & REG_MASK;
            return rd;
        }

        uint32_t getSecondReg() {
            rs1 = command >> SECOND_ARG_OFFSET  & REG_MASK;
            return rs1;
        }

        uint32_t getThirdReg() {
            rs2 = command >> THIRD_ARG_OFFSET  & REG_MASK;
            return rs2;
        }

        int32_t getImm() {
            imm = command & IMM_OFFSET;
            return imm;
        }

        int32_t getJmpOffset() {
            return command & JMP_OFFSET;
        }

        int32_t getBeqOffset() {
            return command & BEQ_OFFSET;
        }

        int32_t getLdpOffset() {
            return command & LDP_OFFSET;
        }

        int32_t getLdOffset() {
            return command & LD_OFFSET;
        }

        int32_t getStOffset() {
            return command & ST_OFFSET;
        }

    public: // special functions
        uint32_t getOpcode();
};


