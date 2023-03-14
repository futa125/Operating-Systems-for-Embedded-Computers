#include <stdio.h>
#include "trig.h"
#include "arith.h"
#include "bin.h"

int main() {
    printf("Cos of 60 degrees: %.2f\n", cosdeg(60));
    printf("Sin of 90 degrees: %.2f\n", sindeg(90));
    printf("\n");
    printf("Add 5 and 3: %.2f\n", add(5, 3));
    printf("Sub 10.3 and 5.8: %.2f\n", sub(10.3, 5.8));
    printf("Mul 3.14 and 2.71828: %.2f\n", mul(3.14, 2.71828));
    printf("Sub 10.3 and 5.8: %.2f\n", sub(10.3, 5.8));
    printf("\n");
    printf("Binary AND of 136 and 93: %d\n", binand(136, 93));
    printf("Binary OR of 136 and 93: %d\n", binor(136, 93));
}