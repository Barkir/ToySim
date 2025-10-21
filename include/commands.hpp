#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>

#define DEBUG
#ifdef DEBUG
#define ON_DEBUG(code) code
#else
#define ON_DEBUG(code)
#endif

const size_t DEFAULT_MEMORY_SIZE = 1024;
const size_t REG_SIZE = 32;
const size_t IMM_SIZE = 16;
const size_t BEQ_OFFSET_SIZE = 16;
const size_t LDP_OFFSET_SIZE = 11;
const size_t LD_OFFSET_SIZE  = 16;
const size_t ST_OFFSET_SIZE  = 16;
const size_t PC_INC = 4;

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


enum toyRegs {
    TOY_R0 = 0,
    TOY_R1,
    TOY_R2,
    TOY_R3,
    TOY_R4,
    TOY_R5,
    TOY_R6,
    TOY_R7,
    TOY_R8,
    TOY_R9,
    TOY_R10,
    TOY_R11,
    TOY_R12,
    TOY_R13,
    TOY_R14,
    TOY_R15,
    TOY_R16,
    TOY_R17,
    TOY_R18,
    TOY_R19,
    TOY_R20,
    TOY_R21,
    TOY_R22,
    TOY_R23,
    TOY_R24,
    TOY_R25,
    TOY_R26,
    TOY_R27,
    TOY_R28,
    TOY_R29,
    TOY_R30,
    TOY_R31 = 31
};

enum toySyscalls {
    TOY_INPUT = 1,
    TOY_PRINT = 2
};

static const std::unordered_map<uint32_t, std::string> OPCODE_MAP {
    {TOY_JMP,       "JMP"       },
    {TOY_CBIT,      "CBIT"      },
    {TOY_SUBI,      "SUBI"      },
    {TOY_MOVN,      "MOVN"      },
    {TOY_BEQ,       "BEQ"       },
    {TOY_BEXT,      "BEXT"      },
    {TOY_LDP,       "LDP"       },
    {TOY_ADD,       "ADD"       },
    {TOY_LD,        "LD"        },
    {TOY_CLS,       "CLS"       },
    {TOY_RORI,      "RORI"      },
    {TOY_ST,        "ST"        },
    {TOY_XOR,       "XOR"       },
    {TOY_SYSCALL,   "SYSCALL"   }
};

struct MemorySPU {

    std::vector<int32_t> memory;

    public:
        MemorySPU(size_t cap) : memory(cap, 0) {} // initialize vector if size cap and value 0.


    public: // operators
    int32_t& operator[](int32_t index) {
        return memory[index];
    }


};

struct SPU {

    int32_t pc;
    uint32_t regs[32];
    size_t cap;

    MemorySPU memory; // class for memory


    SPU(size_t capIn) : memory(capIn), cap(capIn), pc(0), regs({}) {} // constructor

};

class Instruction {
    private:
        uint32_t command;
        uint32_t rd;
        int32_t imm;
        uint32_t rs1;
        uint32_t rs2;

    public: // constructor
        Instruction(uint32_t commandIn) : command(commandIn) {}

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

using executeFunc = void(*)(SPU&, enum toyCommands);

// structure to create a structure array with all the execute functions.
struct commandHandler {
    enum toyCommands opcode;
    executeFunc func;
};

uint32_t swapEndian(uint32_t value);


void spuDump(SPU& spu);
void commandDump(std::string commandName, uint32_t command);

void callADD    (SPU& spu,      Instruction command);
void callXOR    (SPU& spu,      Instruction command);
void callMOVN   (SPU& spu,      Instruction command);
void callSYSCALL(SPU& spu,      Instruction command);
void callSUBI   (SPU& spu,      Instruction command);
void callJMP    (SPU& spu,      Instruction command);
void callBEQ    (SPU& spu,      Instruction command);
void callLD     (SPU& spu,      Instruction command);
void callLDP    (SPU& spu,      Instruction command);
void callBEXT   (SPU& spu,      Instruction command);
void callCBIT   (SPU& spu,      Instruction command);
void callST     (SPU& spu,      Instruction command);
void callRORI   (SPU& spu,      Instruction command);
void callCLS    (SPU& spu,      Instruction command);

