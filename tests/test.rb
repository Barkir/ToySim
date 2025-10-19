require_relative "../toy_isa"

asm = MicroAsm.new

asm.prog do
    movn r1, r2, 48
    movn r1, r2, 48
    label :hello
    jmp :hello
    cbit r1, r6, 65
    subi r28, r31, 543
    beq r21, r9, 43
    bext r5, r7, r29
    ldp r1, r2, 43.r1
    add r1, r2, r3
    ld r1, 57.r8
    cls r6, r9
    rori r8, r9, 745
    st r1, 68.r17
    xor r1, r5, r8
    syscall
    hlt
end
