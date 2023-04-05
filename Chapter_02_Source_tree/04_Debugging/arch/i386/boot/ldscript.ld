/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

STACK_END_ADDRESS = 0x800000;

SECTIONS {
	.code LOAD_ADDR :
	{
		*?/boot/startup.asm.o ( .text* )
		*?/boot/premjesti.o ( .text* ) 	
	}
	size_code = SIZEOF(.code);

	instructions_relocate = 0x200000;
	instructions_load = LOAD_ADDR + size_code;
	.instructions instructions_relocate : AT (instructions_load)
	{
		*( .text* );
	}
	size_instructions = SIZEOF(.instructions);

	constants_relocate = instructions_relocate + size_instructions;
	constants_load = instructions_load + size_instructions;
	.constants constants_relocate : AT (constants_load)
	{
		* ( .rodata* )
	}
	size_constants = SIZEOF(.constants);

	data_relocate = constants_relocate + size_constants;
	data_load = constants_load + size_constants;
	.data data_relocate : AT (data_load)
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
