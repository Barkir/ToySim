require_relative "../toy_isa"

asm6 = MicroAsm.new
asm6.prog do
  subi r1, r0, 12000
  subi r2, r0, 1
  subi r3, r0, 1
  xor r1, r1, r2

  label :fib_loop

  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3


  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3


  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3
  add r5, r5, r2
  xor r6, r2, r3
  movn r4, r2, r2
  add r2, r2, r3
  movn r3, r4, r4

  add r5, r5, r2
  xor r6, r2, r3

  subi r1, r1, 1
  beq r1, r0, :fib_end
  jmp :fib_loop
  label :fib_end
end
