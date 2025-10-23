require_relative "../toy_isa"


asm4 = MicroAsm.new
asm4.prog do
  subi r3, r3, 1
  subi r2, r2, 1000
  xor r3, r3, r2


  label :inner_loop
  add r4, r4, r1
  add r5, r5, r2
  xor r6, r4, r5

  movn r7, r4, r4
  movn r8, r5, r5

  subi r3, r3, 1
  beq r3, r0, :inner_end
  jmp :inner_loop
  label :inner_end

  add r1, r1, r2
  subi r2, r2, 1
  beq r2, r0, :outer_end
  label :outer_end
end
