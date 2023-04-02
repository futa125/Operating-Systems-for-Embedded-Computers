#include <types/basic.h>

void copy(char* to, char* from, size_t size_d) {
	for (size_t i = 0; i < size_d; i++) {
		to[i] = from[i];
	}
}

void premjesti (void) 
{
	extern size_t size_instructions, size_constants, size_data;
	extern char instructions_relocate, instructions_load, constants_relocate, constants_load, data_relocate, data_load;

	copy(&instructions_relocate, &instructions_load, (size_t) &size_instructions);
	copy(&constants_relocate, &constants_load, (size_t) &size_constants);
	copy(&data_relocate, &data_load, (size_t) &size_data);
}
