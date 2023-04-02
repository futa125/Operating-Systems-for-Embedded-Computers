#include <stdio.h>
#include <kernel/memory.h>

int demo() {
    printf("Running demo!\n");

    size_t i;
    int* a[15];

    for (i = 0; i < 15; i++) {
        printf("a[%d]=kmalloc(100)\n", i);
        a[i] = kmalloc(100);
    }

    for (i = 0; i < 4; i++) {
        printf("kfree(a[%d])\n", i);
        kfree(a[i]);
    }

    printf("a[0]=kmalloc(300)\n");
    a[0] = kmalloc(300);
	
    for (i = 4; i < 15; i++) {
        printf("kfree(a[%d])\n", i);
        kfree(a[i]);
    }

    return 0;
}