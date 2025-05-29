/*
It is possible to write ten as the sum of primes in exactly five different ways:

7 + 3
5 + 5
5 + 3 + 2
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2

What is the first value which can be written as the sum of primes in over five thousand different ways?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int *isPrime, c;

int* sieve(int start, int end, int *len) {
    int size = end - start + 1;
    int *primes = malloc(size * sizeof(int));
    int c = end - start + 1, s;

    for (int i = start; i <= end; i++) primes[i - start] = 1;

    if (start == 0) {primes[0] = 0; primes[1] = 0;}
    if (start == 1) {primes[1] = 0;}

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
            primes[j - start] = 0;
        }
    }
    
    *len = c;


    return primes;
}

int search(int n, int used) {
    int d, ways = 0;
    for (int i = n-1; i>0; i--) {
        if (!isPrime[i]) continue;
        if (i>used) continue;
        d = n-i;
        //printf("%d, %d, %d\n", i, d, used);
        if (d<=i && isPrime[d]) ways++;

        ways += search(d, i);
    }

    return ways;
}

int main() {
    isPrime = sieve(0, 100, &c);

    for (int n = 0; n <= 100; n++) {if (search(n, INT_MAX) > 5000) printf("%d, %d\n", n, search(n, INT_MAX)); fflush(stdout);}
    return 0;
}