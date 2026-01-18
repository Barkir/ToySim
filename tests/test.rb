require_relative "../toy_isa"

asm = MicroAsm.new

asm.prog do
    subi r1, r1, 50

    label :cycle_start
        subi r2, r2, 1
        beq r2, r1, :cycle_end
        subi r0, r0, 30000
        label :prog_start
        subi r8, r8, 1
        beq r8, r0, :prog_end
        jmp :prog_start

    label :prog_end
    jmp :cycle_start
    label :cycle_end
end
