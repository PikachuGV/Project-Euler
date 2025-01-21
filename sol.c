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

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int ndigits(int n) {
    int i;
    for (i = 0; n != 0 && i < INT_MAX; i++) {
        n /= 10;
    }
    return i;
}

bool hasRepeat(bool **digits, int n, int ndig) {
    for (int i = 0; i < ndig; i++) {
        if ((*digits)[(n%10)-1] == true) {
            return true;
        }
        (*digits)[(n%10)-1] = true; n/=10;
    }
    return false;
}

bool all(bool *arr, int len) {
    for (int i = 0; i<len; i++) {
        if (!arr[i]) return false;
    }
    return true;
}

bool isIn(int *arr, int len, int n) {
    for (int i = 0; i<len; i++) {
        if (arr[i] == n) return true;
    }
    return false;
}

int main() {
    int c, M, N, K, m, n, k, S, *seen; 
    bool *digits;

    c = 0; S = 9; k = S / 2;
    seen = malloc(0); 
    digits = malloc(S * sizeof(bool)); for(int i=0;i<S;i++)digits[i]=false;

    K = 0; for(int i=1;i<=k;i++)K=10*K+i;

    for (K; K < power(10, k); K++) {

        for (M = 2; M < power(10, (S-k)/2); M++) {
            memset(digits, false, S * sizeof(bool));
            if (hasRepeat(&digits,K,k)) continue;
            if (M==39 && K==7254) {
                printf("");
            }
            if (M % 10 == 1) continue;
            if (K % M != 0) continue;

            N = K / M; m = ndigits(M); n = ndigits(N);
            if (m+n+k != S) continue;

            if (hasRepeat(&digits,M,m)) continue;
            if (hasRepeat(&digits,N,n)) continue;

            if (all(digits, S) && !isIn(seen, c, K)) {
                c++; seen = realloc(seen, c * sizeof(int));
                seen[c-1] = K;
                printf("%d, %d, %d\n", M, N, K);
            }
        }
    }
    
    int sum = 0;
    for (int i = 0; i<c;i++) sum+= seen[i];

    printf("%d\n", sum);

    return 0;
}