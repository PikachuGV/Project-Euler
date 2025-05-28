/*
Euler's totient function, φ(n) [sometimes called the phi function], is defined as the number of positive integers not exceeding n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than or equal to nine and relatively prime to nine, φ(9)=6.

n    Relatively_Prime       φ(n)    n/φ(n)
2           1                1        2
3          1,2               2       1.5
4          1,3               2        2
5        1,2,3,4             4       1.25    
6          1,5               2        3
7      1,2,3,4,5,6           6      1.1666...
8        1,3,5,7             4        2
9      1,2,4,5,7,8           6       1.5
10       1,3,7,9             4       2.5

It can be seen that n = 6 produces a maximum n/φ(n) for n <= 10.
Find the value of n <= 1,000,000 for which n/φ(n) is a maximum.
*/

/*
Lets say we have the prime factorisation of n to be product of (pi)^ai for 1<=i<=n
A quick google search shows that totient(n) = product of (pi - 1) * pi^(ki - 1)  for all prime p dividing n.
However, naively searching all totient values from 1 to 1mil will take forever.

We could make an array of 1000001 elements, with array[i] representing the totient value of i.
Initially, we set array[i] = i.
Now we loop through all the primes below sqrt(1mil) = 1000.
For each prime, we go to array[j*prime] until j*prime >= 1000000.
We then divide array[j*prime] by prime and multiply it by (prime-1).

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

const int N = 1000000;
int *primes, c;

int sieve(int start, int end, int **allprimes) {
    bool primes[end - start + 1];
    int c = end - start + 1, s;
    memset(primes, true, sizeof(primes));

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

    return c;
}

int* primeFactor(int *allprimes, int c, int n, int *npfactors) {
    int p, *primes = malloc(0), len = 0;
    for (int i = 0; i < c; i++) {
        p = allprimes[i];
        if ((n % p) == 0) {
            len++; primes = realloc(primes, len * sizeof(int));
            primes[len - 1] = p;

            while ((n % p) == 0) n/=p;
        }
    }

    *npfactors = len;
    return primes;
}

int totient(int n) {
    int nMultiples = 0, nPMultiples = 0, N = n, p;
    bool numbers[n + 1]; memset(numbers, true, sizeof(numbers));
    numbers[0] = false;
    for (int i = 0; i < c; i++) {
        p = primes[i];
        if ((n % p) == 0) {
            N /= p;
            N *= (p - 1);
            while ((n % p) == 0) n/=p;
        }
    }
    return n;
}



int main() {
    double start = get_time();
    int p, *t, maxn; double maxv,v;
    
    c = sieve(2, 100, &primes);
    t = malloc((N + 1) * sizeof(int));
    for (int n = 0; n <= N; n++) t[n] = n;
    maxv = 0;

    for (int i = 0; i < c; i++) {
        p = primes[i];
        for (int n = p; n <= N; n += p) {
            t[n] /= p;
            t[n] *= (p - 1);
        }
    }
    for (int n = 2; n <= N; n++) {
        v = (double)n / (double)(t[n]);

        if (v > maxv) {
            maxv = v; maxn = n;
        }
    }

    printf("%d: %lf\n", maxn, maxv);
    printf("Time taken: %lf\n", get_time() - start);


    return 0;
}