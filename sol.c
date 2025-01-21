/*
Q20: n! means n * (n - 1) * ... * 3 * 2 * 1.
For example, 10! = 10 * 9 * ... * 3 * 2 * 1 = 3628800, and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
Find the sum of the digits in the number 100!.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    short* digits = malloc(sizeof(short)); //First digit at the end, last at the front
    digits[0] = (short)1;
    int newdigit, carryover = 0, ndigits = 1, sum = 0;
    
    for (int i = 2; i <= 100; i++) {
        for (int j = 0; j < ndigits; j++) {
            newdigit = digits[j] * i + carryover;
            carryover = newdigit / 10;
            digits[j] = (short)(newdigit % 10);
        }

        

        if (carryover > 0) {
            int temp = carryover, originaldigits = ndigits;

            while (temp > 0) {
                ndigits++;
                temp /= 10;
            }

            digits = realloc(digits, ndigits * sizeof(short));
            for (int i = originaldigits; i < ndigits; i++) {
                digits[i] = carryover % 10;
                carryover /= 10;
            }
        }
    }

    for (int i = 0; i < ndigits; i++) sum += digits[i];

    printf("%d\n", sum);

    return 0;
}