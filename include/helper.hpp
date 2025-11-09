#pragma once

enum toyErrors get_commands(std::vector<uint32_t> *commands, const std::string& filename, size_t *fsz);
size_t getFileSize(std::ifstream& file);


template<typename T>
void hexDump(const std::vector<T>& buffer);

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

