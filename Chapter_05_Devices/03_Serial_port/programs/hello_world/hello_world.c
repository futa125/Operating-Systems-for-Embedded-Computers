/*! Hello world program */

#include <stdio.h>
#include <api/prog_info.h>
#include <kernel/memory.h>


int hello_world()
{
	void* a[15];
	size_t i;

	printf("a[0]=kmalloc(100)\n");
    a[0] = kmalloc(100);
    printf("\n");

	for (i = 1; i < 10; i++) {
		printf("a[%d]=kmalloc(200)\n", i);
        a[i] = kmalloc(200);
        printf("\n");
	}

	for (i = 0; i < 7; i++) {
        printf("kfree(a[%d])\n", i);
        kfree(a[i]);
        printf("\n");
    }

	printf("a[5]=kmalloc(100)\n", 5);
    a[i] = kmalloc(100);
    printf("\n");


	return 0;
}
