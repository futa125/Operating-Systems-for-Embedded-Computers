/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

STACK_END_ADDRESS = 0x800000;

SECTIONS {
	.code LOAD_ADDR :
	{
		/* instructions */
		*?/boot/startup.asm.o ( .text* )
		*?/boot/premjesti.o ( .text* ) 	
	}
	size_code = SIZEOF(.code);

	instr_RAM = 0x200000;
	instr_ROM = LOAD_ADDR + size_code;
	.instrukcije instr_RAM : AT (instr_ROM)
	{
		*( .text* );
	}
	size_instr = SIZEOF(.instrukcije);

	constants_RAM = 0x300000;
	constants_ROM = instr_ROM + size_instr;
	.constants constants_RAM : AT (constants_ROM)
	{
		* ( .rodata* )
	}
	size_constants = SIZEOF(.constants);

	data_RAM = 0x400000;
	data_ROM = constants_ROM + size_constants;
	.data data_RAM : AT (data_ROM)
	{
		* ( .data* .bss* COMMON* )
	}
	size_data = SIZEOF(.data);

	.stack STACK_END_ADDRESS - STACK_SIZE :
	{
		*(.stack)
	}

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */

/DISCARD/ : { *(.eh_frame*) }
#ifndef DEBUG
	/DISCARD/ : { *(*) }
#endif
	kernel_end_addr = .;
}
