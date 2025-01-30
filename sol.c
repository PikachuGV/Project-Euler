/*
We shall say that an n-digit number is pandigital if it makes use of all the digits $1$ to $n$ exactly once. For example, $2143$ is a $4$-digit pandigital and is also prime.
What is the largest n-digit pandigital prime that exists?
*/

/*
n < 8. Bcos if n is 8 or 9, sum of digits = 36 or 45 which is divisible by 3, thus number is divisible by 3.

Current largest possible n is thus 7.
Same logic mean n cannot be 6 or 5 too.
We know that n is minimally 4. Thus we are looking at n=4 and n=7 only

The pandigital prime must not end with an even number or 5.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) ((a > b) ? a : b)

bool isPandigital(int digits, int n) {
    int b, d = 0;
    while (n != 0) {
        b = 1 << ((n % 10) - 1);
        if ((b & d) != 0) return false;
        n /= 10; d |= b;
        
    }
    return (d == ((1 << digits) - 1));
}

int sieve(int start, int n, int **allprimes) {
    bool primes[n - start + 1];
    int c = n - start + 1, s;
    memset(primes, true, sizeof(primes));
    for (int i = 2; i * i <= n; i++) {
        if (i > start && !primes[i]) continue;
        if (i * i < start) {
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            s = i * i;
        }
        for (int j = s; j <= n; j += i) {
            if (primes[j - start]) c--;
            primes[j - start] = false;
        }
    }

    *allprimes = (int*)malloc(c * sizeof(int));

    int index = 0;
    for (int i = start; i < n; i++) {
        if (primes[i - start]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

int main() {
    int largest, p, P, *primes;
    largest = 0;
    
    p = sieve (7000000, 8000000, &primes);
    for (int i = 0; i < p; i++) {
        P = primes[i];
        if (isPandigital(7, P) && P > largest) largest = P;
    }
    if (P == 0) {
        free(primes);
        p = sieve(1000, 10000, &primes);
        for (int i = 0; i < p; i++) {
            P = primes[i];
            if (isPandigital(4, P) && P > largest) largest = P;
        }
    }
    
    printf("%d\n", largest);
    return 0;
}
