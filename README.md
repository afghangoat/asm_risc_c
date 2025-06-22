#RISC Emulator in C

A basic RISC asm interpreter written in C. (More like Mini-RISC)

##Instructions

The emulator currently contains these instructions:

- add
- sub
- mov
- inc
- jmp
- tst
- jnz
- jz
- cmp
- xor
- or
- and
- shl
- shr
- not
- hlt

##Usage

The register amount can be configured via setting the `REGISTER_AMM` macro value.

call `ASM_init_sequence` at the beginning of your code.
call `parse_line_ASM(ASM CODE HERE)` with the instructions you need.
call `ASM_execute_sequence(global_asm_commands)` to execute you assembly instructions.
If you want to check the register stats, call: `show_registers();`

Run:
`gcc asm_risc.c -o asm_risc`
`./asm_risc`