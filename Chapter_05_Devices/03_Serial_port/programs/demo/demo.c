#include <stdio.h>
#include <kernel/memory.h>

int demo() {
    size_t i;
    int* a[15];

    for (i = 0; i < 15; i++) {
        printf("a[%d]=kmalloc(100)\n", i);
        a[i] = kmalloc(100);
        printf("\n");
    }

    for (i = 0; i < 4; i++) {
        printf("kfree(a[%d])\n", i);
        kfree(a[i]);
        printf("\n");
    }

    printf("a[0]=kmalloc(316)\n");
    a[0] = kmalloc(316);
    printf("\n");
	
    for (i = 4; i < 15; i++) {
        printf("kfree(a[%d])\n", i);
        kfree(a[i]);
        printf("\n");
    }

    return 0;
}