/*
Consider the fraction, n/d, where n and d are positive integers. If n < d and HCF(n,d)=1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d < 8 in ascending order of size, we get:
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
It can be seen that 2/5 is the fraction immediately to the left of 3/7.
By listing the set of reduced proper fractions for d < 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int D = 1000000;

const int tn = 3, td = 7;

int *primes, c; 

int sieve(int start, int end, int **allprimes) {
    int size = end - start + 1;
    bool *primes = malloc(size * sizeof(bool));
    int c = end - start + 1, s;
    memset(primes, true, sizeof(bool) * size);

    //i represents the multiple that we are sieving out now. We only need to sieve until i = sqrt(end) since any number above sqrt(end) is either a prime or a multiple of some number below sqrt(end).
    for (int i = 2; i * i <= end; i++) {
        if (i > start && !primes[i - start]) continue;
        if (i * i < start) {
            //We set the start multiple to be start if start is already a multiple of i. Else we find the next multiple of i greater than start.
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            //If i * i >= start then we have to start from i * i directly. 
            s = i * i;
        }
        //This loops through all multiples of i from start bound to end bound
        for (int j = s; j <= end; j += i) {
            if (primes[j - start]) c--;
            primes[j - start] = false;
        }
    }

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = start; i < end; i++) {
        if (primes[i - start]) {
            (*allprimes)[index] = i; index++;
        }
    }
    free(primes);
    return c;
}

int isCoPrime(int a, int b) {
    //Binary GCD Algorithm
    
    if ((a&1)==0 && (b&1)==0) return 0;

    while ((a&1)==0) a>>=1;
    while ((b&1)==0) b>>=1;

    if (a==b) return a==1 ? 1 : 0;
    return (a>b) ? isCoPrime(a-b, b) : isCoPrime(a, b-a);
}

int main() {
    c = sieve(2, D, &primes);

    int n, maxn = 0, maxd = 1;
    for (int d = 2; d <= D; d++) {
        //n/d < tn/td: n * td < d * tn
        for (int n = d * tn / td; n > 0; n--) {
            if (n == tn && d == td) continue;
            if (!isCoPrime(n, d)) continue; 
            if (n * maxd < d * maxn) break;
            maxd = d; maxn = n;
        }
    }

    printf("%d, %d\n", maxn, maxd);
    return 0;
}