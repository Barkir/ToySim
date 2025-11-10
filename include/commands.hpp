#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>

const size_t DEFAULT_MEMORY_SIZE = 1024;
const size_t REG_SIZE = 32;
const size_t IMM_SIZE = 16;
const size_t BEQ_OFFSET_SIZE = 16;
const size_t LDP_OFFSET_SIZE = 11;
const size_t LD_OFFSET_SIZE  = 16;
const size_t ST_OFFSET_SIZE  = 16;
const size_t PC_INC = 4;

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
struct MemorySPU {

    std::vector<int8_t> memory;

    public:
        MemorySPU(size_t cap) : memory(cap, 0) {} // initialize vector if size cap and value 0.


    public: // operators
    int8_t& operator[](int32_t index) {
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

void spuDump(SPU& spu);
void commandDump(std::string commandName, uint32_t command);

void callADD    (SPU& spu,      ToyInstruction command);
void callXOR    (SPU& spu,      ToyInstruction command);
void callMOVN   (SPU& spu,      ToyInstruction command);
void callSYSCALL(SPU& spu,      ToyInstruction command);
void callSUBI   (SPU& spu,      ToyInstruction command);
void callJMP    (SPU& spu,      ToyInstruction command);
void callBEQ    (SPU& spu,      ToyInstruction command);
void callLD     (SPU& spu,      ToyInstruction command);
void callLDP    (SPU& spu,      ToyInstruction command);
void callBEXT   (SPU& spu,      ToyInstruction command);
void callCBIT   (SPU& spu,      ToyInstruction command);
void callST     (SPU& spu,      ToyInstruction command);
void callRORI   (SPU& spu,      ToyInstruction command);
void callCLS    (SPU& spu,      ToyInstruction command);

using funcIt = std::function<void (SPU& spu, ToyInstruction)>;
static const std::unordered_map<uint32_t, funcIt> OPCODE_MAP {
    {TOY_JMP,       callJMP         },
    {TOY_CBIT,      callCBIT        },
    {TOY_SUBI,      callSUBI        },
    {TOY_MOVN,      callMOVN        },
    {TOY_BEQ,       callBEQ         },
    {TOY_BEXT,      callBEXT        },
    {TOY_LDP,       callLDP         },
    {TOY_ADD,       callADD         },
    {TOY_LD,        callLD          },
    {TOY_CLS,       callCLS         },
    {TOY_RORI,      callRORI        },
    {TOY_ST,        callST          },
    {TOY_XOR,       callXOR         },
    {TOY_SYSCALL,   callSYSCALL     }
};


using executeFunc = void(*)(SPU&, enum toyCommands);

// structure to create a structure array with all the execute functions.
struct commandHandler {
    enum toyCommands opcode;
    executeFunc func;
};

uint32_t swapEndian(uint32_t value);

