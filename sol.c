/*
The smallest number expressible as the sum of a prime square, prime cube, and prime fourth power is 28. In fact, there are exactly four numbers below fifty that can be expressed in such a way:

28 = 2^2 + 2^3 + 2^4
33 = 3^2 + 2^3 + 2^4
49 = 5^2 + 2^3 + 2^4
47 = 2^2 + 3^3 + 2^4

How many numbers below fifty million can be expressed as the sum of a prime square, prime cube, and prime fourth power?
*/

/*
Notice the question never expected us to find the numbers that can be expressed in such a way. The question only cares about how many of such numbers there are.

This means that we can loop through all the prime fourth powers and prime cubes for which the sum is below 50 million. Now we count how many prime squares there are between 0 and (50mil - sum)

Notice the fourth root of 50 million is 84.089
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int N = 50000000;

int *squares(int *arr, int len) {
    int *sq = malloc(len*sizeof(int));
    for (int i = 0; i < len; i++) {
        sq[i] = arr[i] * arr[i];
    }

    return sq;
}


int sieve(int start, int end, int **allprimes, bool **isPrime) {
    int size = end - start + 1;
    *isPrime = malloc(size * sizeof(bool));
    int c = end - start + 1, s;
    memset(*isPrime, true, sizeof(bool) * size);

    //i represents the multiple that we are sieving out now. We only need to sieve until i = sqrt(end) since any number above sqrt(end) is either a prime or a multiple of some number below sqrt(end).
    for (int i = 2; i * i <= end; i++) {
        if (i > start && !(*isPrime)[i - start]) continue;
        if (i * i < start) {
            //We set the start multiple to be start if start is already a multiple of i. Else we find the next multiple of i greater than start.
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            //If i * i >= start then we have to start from i * i directly. 
            s = i * i;
        }
        //This loops through all multiples of i from start bound to end bound
        for (int j = s; j <= end; j += i) {
            if ((*isPrime)[j - start]) c--;
            (*isPrime)[j - start] = false;
        }
    }

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = start; i <= end; i++) {
        if ((*isPrime)[i - start]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

int main() {
    bool *isPrime; int *primes, c = 0;
    int np = sieve(2, 7071, &primes, &isPrime);
    int *primeSquares = squares(primes, np);
    int p, n;
    bool *seen = calloc(N+1, sizeof(bool)); 
    for (int i = 0; i < np; i++) {
        p = primes[i];
        n = N - (p*p*p*p);
        if (n < 0) break;
        for (int j = 0; j < np; j++) {
            p = primes[j];
            n -= p*p*p;
            if (n < 0) break;
            for (int k = 0; k < np; k++) {
                if (primeSquares[k] >= n) break;
                if (seen[N-n+primeSquares[k]]) continue;
                c++; seen[N-n+primeSquares[k]] = true;
            }
            n += p*p*p;
        }
    }
    printf("%d ", c);
    return 0;
}