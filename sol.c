/*
Consider the fraction, n/d, where n and d are positive integers. If n < d and HCF(n,d)=1, it is called a reduced proper fraction.
If we list the set of reduced proper fractions for d <= 8 in ascending order of size, we get:
1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
It can be seen that there are 21 elements in this set.
How many elements would be contained in the set of reduced proper fractions for d <= 1000000?
*/

/*
This question is essentially asking for the sum of the totient function from 2 to D (or 1 more than the summation from 1 to D).
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int D = 1000000;
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

int* totientrange(int n) {
    int *t, p;
    t = malloc((n + 1) * sizeof(int));
    for (int m = 0; m <= n; m++) t[m] = m;
    
    for (int i = 0; i < c; i++) {
        p = primes[i];
        for (int m = p; m <= n; m += p) {
            t[m] /= p;
            t[m] *= (p - 1);
        }
    }
    return t;
}

int main() {
    c = sieve(2, D, &primes);
    int *t = totientrange(D);
    unsigned long long s = 0ULL;

    for (int i = 2; i <= D; i++) {
        s += (unsigned long long)t[i];
    }

    printf("%llu\n",s);
    return 0;
}
