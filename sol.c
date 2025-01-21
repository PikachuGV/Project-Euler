/*
Q32: We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 * 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int pow

int main() {
    int c, M, N, K, m, n, k, S, *seen; 
    bool *digits;

    S = 9; k = S / 2;
    seen = malloc(0); 
    digits = malloc(S * sizeof(bool)); for(int i=0;i<S;i++)digits[i]=false;

    K = 0; for(int i=1;i<=k;i++)K=10*K+i;
    for (k; k < )


    return 0;
}