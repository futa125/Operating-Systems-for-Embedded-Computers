#include <types/basic.h>

void copy(char* to, char* from, size_t size_d) {
	for (size_t i = 0; i < size_d; i++) {
		to[i] = from[i];
	}
}

void premjesti (void) 
{
	extern size_t size_instr, size_constants, size_data;
	extern char instr_RAM, instr_ROM, constants_ROM, constants_RAM, data_ROM, data_RAM;

	copy(&instr_RAM, &instr_ROM, (size_t) &size_instr);
	copy(&constants_RAM, &constants_ROM, (size_t) &size_constants);
	copy(&data_RAM, &data_ROM, (size_t) &size_data);
}