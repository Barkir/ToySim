require_relative "../toy_isa"

asm7 = MicroAsm.new
asm7.prog do
  subi r1, r0, 2500
  subi r2, r0, 7
  xor r1, r1, r2

  label :nested_loop


  label :mid_loop
  subi r4, r0, 3

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6


  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6

  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6


  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6
  add r5, r5, r1
  add r6, r6, r2
  xor r7, r5, r6

  movn r8, r5, r5
  movn r9, r6, r6


  label :inner_end

  subi r3, r3, 1

  subi r1, r1, 1
  beq r1, r0, :nested_end
  jmp :nested_loop
  label :nested_end
end
