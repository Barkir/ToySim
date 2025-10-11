require_relative "toy_isa"

asm = MicroAsm.new

asm.prog do
    movn r1, r31, 42
    syscall
    cls r1, r8
    rori r7, r2, 6
    st r1, 42.r2
    # bext r2, r8, r7
end
