/*
Q6: The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385.
The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 55^2 = 3025.
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int sumsq = 0, sqsum = 0;

    for (int i = 1; i <= 100; i++) {
        sumsq += i * i; sqsum += i;
    }

    sqsum *= sqsum;

    int diff = sumsq > sqsum? sumsq - sqsum : sqsum - sumsq;
    printf("%d\n", diff);

    return 0;
}