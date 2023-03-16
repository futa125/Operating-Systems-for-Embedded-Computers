#include <stdio.h>
#include <math.h>
#include "lab1y.h"

void lab1y() {
    int x = time(NULL);
    printf("lab1y pokrenut u t=%d, sin(t)=%F\n", x, sin(x));
}