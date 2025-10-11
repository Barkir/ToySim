require_relative "toy_isa"

asm = MicroAsm.new

asm.prog do
    jmp :helel
    movn r1, r2, 48
    movn r1, r2, 48
    movn r1, r2, 48
    movn r1, r2, 48
    movn r1, r2, 48
    movn r1, r2, 48
    label :helel
    hlt
end
