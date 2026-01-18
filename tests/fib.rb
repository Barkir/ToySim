require_relative "../toy_isa"

asm = MicroAsm.new



asm.prog do
    subi r8, r8, 1
    subi r9, r9, 2
    xor r8, r8, r9
    syscall        # making a syscall 1 where we put number to r0

    movn r2, r8, r8
    movn r3, r8, r8
    label :prog_start
    beq r1, r0, :prog_end          # if r1 equals the number from syscall - we jump to prog_end

#-------------------------------------------------------------------------------
    movn r4, r2, r8                # r2 -> r4     (saving its' value)
    add r2, r2, r3                 # r2 = r2 + r3 (getting next fib)
    movn r3, r4, r8                # r4 -> r3     (saving prev fib to r3)

    add r1, r1, r8                 # r1 = r1 + r8 (incrementing r1)
    jmp :prog_start                # jumping to the start of the program
    label :prog_end

    add r8, r8, r8                  # syscall 2 - print number from r1
    movn r1, r2 , r8                 # r2 -> r1 (n fib is now in r1)
    syscall
end
