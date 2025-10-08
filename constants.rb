module Constants
    INSTRUCTION_SET = { # constant value written in CAPITAL LETTERS (this is a hash table)
        'J'    => 0b010111,
        'CBIT' => 0b111011,
        'SUBI' => 0b001111,
        'MOVN' => 0b000101,
        'BEQ'  => 0b100110,
        'BEXT' => 0b110110,
        'LDP'  => 0b001110,
        'ADD'  => 0b000110,
        'LD'   => 0b100010,
        'CLS'  => 0b101101,
        'RORI' => 0b111111,
        'ST'   => 0b111010,
        'XOR'  => 0b011011,
        'SYSCALL' => 0b000111
    }.freeze # nobody can change me!

    INSTRUCTION_OFFSET = {
        'J'    => 2,
        'CBIT' => 3,
        'SUBI' => 3,
        'MOVN' => 3,
        'BEQ'  => 3,
        'BEXT' => 3,
        'LDP'  => 3,
        'ADD'  => 3,
        'LD'   => 2,
        'CLS'  => 2,
        'RORI' => 3,
        'ST'   => 2,
        'XOR'  => 3,
        'SYSCALL' => 1
    }.freeze # nobody can change me!

    # for all numbers from 0 to 15 we create an array [R{i}, i].
    # then we turn it to hash_table with .to_h and then we make it constant by .freeze
    REGISTERS = (0..15).map {|i| ["R#{i}", i]}.to_h.freeze
end
