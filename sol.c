/*
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
How many circular primes are there below one million?
*/

/*
Obviously we need to get all primes below 1000000.
We can ignore all primes that start with an even number since they will surely lead to a rotation that is even.
We can also ignore all primes that start with 5 since they will lead to a rotation ending in 5, which makes it divisible by 5.

Repetitions will be a concern. If we naively loop through all the primes and check whether there are circular, we are bound to have repetitions. As an example, we find that 197 is circular. That also means that we will find that 719 is circular.

We can solve it by creating an array where each boolean element represents whether a prime is checked. This array will have length equal to the number of primes. As we check a prime, we also check whether we have checked this prime before. If we have, we do not bother checking it again and move on to the next prime.
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int sieve(int n, int **allprimes) {
    bool primes[n + 1];
    int c = n - 1;
    memset(primes, true, sizeof(primes));
    for (int i = 2; i * i <= n; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= n; j += i) {
                if (primes[j]) c--;
                primes[j] = false;
            }
        }
    }

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = 2; i < n; i++) {
        if (primes[i]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int digits(int n) {
    int c = 1;
    while (n != 0) {
        n /= 10; c++;
    }
    return c;
}

int main() {
    int N, l, p, P, c, d, *primes;
    N = 1000000;
    l = sieve(N, &primes);
    c = 0;

    bool seen[c];
    memset(seen, false, sizeof(seen));

    for (int i = 0; i < l; i++) {
        P = primes[i];
        if (P / 10 == 0) {
            c++; continue;
        }

        p = P / power(10, d - 1); d = digits(P);

        while (p != P) {
            if ()
        }
    }

    return 0;
}