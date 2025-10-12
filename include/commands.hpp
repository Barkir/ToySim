// those are opcodes (soon...)
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
    TOY_SYSCALL =0b000111
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



