require_relative "../toy_isa"

asm5 = MicroAsm.new
asm5.prog do
  subi r1, r0, 15000
  subi r2, r0, 1
  subi r3, r0, 2
  xor r1, r1, r3

  label :compute_loop
  add r4, r2, r3
  movn r5, r4, r4
  add r6, r6, r5

  add r2, r2, r3
  subi r3, r3, 1
  beq r3, r0, :reset
  jmp :skip_reset
  label :reset
  subi r3, r0, 2
  label :skip_reset

  subi r1, r1, 1
  beq r1, r0, :compute_end
  jmp :compute_loop
  label :compute_end
end
