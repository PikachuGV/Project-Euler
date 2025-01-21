/*
Q16: 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26
What is the sum of the digits of the number 2^1000?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    short* digits = malloc(sizeof(short)); //First digit at the end, last at the front
    digits[0] = (short)1;
    int newdigit, carryover = 0, ndigits = 1, sum = 0;
    
    for (int i = 0; i < 1000; i++) {
        if (digits[ndigits - 1] >= 5) {
            ndigits++;
            digits = realloc(digits, ndigits * sizeof(short));
            digits[ndigits - 1] = 0;
        }
        for (int j = 0; j < ndigits; j++) {
            newdigit = digits[j] * 2 + carryover;
            carryover = newdigit / 10;
            digits[j] = newdigit % 10;
        }
    }

    for (int i = 0; i < ndigits; i++) sum += digits[i];

    printf("%d\n", sum);

    return 0;
}