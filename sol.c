/*
Q27: Euler discovered the remarkable quadratic formula:
n^2 + n + 41
It turns out that the formula will produce 40 primes for the consecutive integer values 0 < n < 39. However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
The incredible formula n^2 - 79n + 1601 was discovered, which produces 80 primes for the consecutive values 0  n  79. The product of the coefficients, -79 and 1601, is -126479.

Considering quadratics of the form:

n^2 + an + b, where |a| < 1000 and |b| < 1000 
where |n| is the modulus/absolute value of n 
e.g. |11| = 11 and |-4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.
*/

/*
Notice b cannot be even. If b is even, then substituting n=2 will give an even number which is clearly not a prime. b also determines the upper limit of n for the production of primes, since subsituting n=b will produce a result divisible by b.
We already know that there exists a quadratic that produces 80 primes. As such we only need to check the cases when |b| >= 81 (not 80 since 80 is even)
b also cannot be negative since that will lead to the substitution of n=0 to produce a negative number. So we just need to make sure b >= 81 AND b is odd. We effectively reduced our search area by 75%.

Now if b is odd, then we can deduce that a must be odd. This is because substituiting n=1 gives 1+a+b. 1+b is odd+odd=even. If a is even then the result is even and will not be prime.

b must also be prime. If b is not prime, then we can express it as a product of 2 factors (not 1 nor itself). Setting n to be either of the factors will produce a result divisible by the factor (since both n^2 and an are divisible by n). The largest b possible is 999 and its square root is about 33. So non prime values for b will certainly fail before n=33.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void sieve(int n, bool** primes, int** allprimes) {
    *primes = (bool*)malloc(sizeof(bool) * (n + 1));
    int c = n - 1;
    memset(*primes, true, sizeof(bool) * (n + 1));
    for (int i = 2; i * i <= n; i++) {
        if ((*primes)[i]) {
            for (int j = i * i; j <= n; j += i) {
                if ((*primes)[j]) c--;
                (*primes)[j] = false;
            }
        }
    }

    *allprimes = (int*)malloc((c + 1) * sizeof(int)); (*allprimes)[c] = -1;
    int index = 0;
    for (int i = 2; i < n; i++) {
        if ((*primes)[i]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return;
}

int main() {
    int N = 10000;
    bool* primes;
    int* allprimes;
    sieve(N, &primes, &allprimes);

    //83 is the 23rd prime, so for values of b we start from index 22.
    int prod, n, a, b, p, longest = -1;
    for (int i = 22; allprimes[i] != -1 && allprimes[i] < 1000; i++) {
        b = allprimes[i];
        for (a = -999; a < 1000; a += 2) {
            n = 0; p = n * n + a * n + b;
            while (primes[p]) {
                n++; p = n * n + a * n + b;
            }
            if (n > longest) {
                longest = n; prod = a * b;
                printf("%d, %d, %d\n", prod, a, b);
            }
        }
    }

    printf("%d, %d\n", prod, longest);
    return 0;
}