#include <unordered_map>
#include <cstdint>
#include <string>

const uint32_t OPCODE_MASK   = 0x3F;
const uint32_t OPCODE_OFFSET = 26;

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

struct SPU {

    uint32_t pc;
    uint32_t regs[32];
};

using executeFunc = void(*)(SPU&, enum toyCommands);

// structure to create a structure array with all the execute functions.
struct commandHandler {
    enum toyCommands opcode;
    executeFunc func;
};


uint32_t getOpcode(const uint32_t command);
uint32_t swapEndian(uint32_t value);



