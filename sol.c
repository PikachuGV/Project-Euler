/*
Euler's totient function, φ(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6. The number 1 is considered to be relatively prime to every positive number, so φ(1)=1. 
Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.
*/

/*
To get the phi value for all the numbers we can use the same method we used in Q69.
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


const int TENS[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int ndigits(int n) {
    if (n < 0) n *= -1;
    if (n == 0) return 1;
    for (int i = 1; i < 10; i++) {
        if (n < TENS[i]) return i;
    }

    exit(1000);
}

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

bool isPermutation(int a, int b) {
    int d = ndigits(a);
    if (d != ndigits(b)) return false;
    int A[d], B[d];
    for (int i = d - 1; i >= 0; i--) {
        A[i] = a % 10; B[i] = b % 10;
        a /= 10; b /= 10;
    }
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (A[i] == B[j]) {B[j] = -1; break;}
        }
    }

    for (int i = 0; i < d; i++) {
        if (B[i] != -1) return false;
    }
    return true;
}

const int N = 10000000;
int *primes, c;

int* totientrange(int n) {
    int *t, p;
    t = malloc((N + 1) * sizeof(int));
    for (int m = 0; m <= N; m++) t[m] = m;
    
    for (int i = 0; i < c; i++) {
        p = primes[i];
        for (int m = p; m <= N; m += p) {
            t[m] /= p;
            t[m] *= (p - 1);
        }
    }



    return t;
}

int main() {
    double start = get_time();
    c = sieve(2, N, &primes);
    
    int *totients, maxn; double minv = (double)INT_MAX, v;
    totients = totientrange(N);
    //for (int i = 0; i < 100; i++) printf("%d ", totients[i]);

    for (int n = 2; n <= N; n++) {
        if (!isPermutation(n, totients[n])) continue;
        v = (double)n / (double)(totients[n]);

        if (v < minv) {
            minv = v;
            maxn = n;
        }
    }

    printf("%d, %lf: %d\n", maxn, minv, totients[maxn] );
    printf("Time taken: %lf\n", get_time() - start);

    return 0;
}

