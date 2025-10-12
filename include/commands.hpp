// those are opcodes (soon...)
enum toyCommands {
    TOY_JMP,
    TOY_CBIT,
    TOY_SUBI,
    TOY_MOVN,
    TOY_BEQ,
    TOY_BEXT,
    TOY_LDP,
    TOY_ADD,
    TOY_LD,
    TOY_CLS,
    TOY_RORI,
    TOY_ST,
    TOY_XOR,
    TOY_SYSCALL
};

using executeFunc = void(*)(SPU&, enum toyCommands);

// structure to create a structure array with all the execute functions.
struct commandHandler {
    enum toyCommands opcode;
    executeFunc func;
};
