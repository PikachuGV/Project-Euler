/*
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.
Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:
d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPandigital(long long n) {
    int b, d = 0;
    while (n != 0) {
        b = 1 << (n % 10);
        if ((b & d) != 0) return false;
        d |= b; n /= 10;
    }
    return (bool)(d == ((1 << 10) - 1));
}

int main() {
    int val, arr[10];
    int primes[] = {2, 3, 5, 7, 11, 13, 17};
    bool out;
    long long t, sum = 0L;
    for (long long n = 1023456789LL; n <= 10000000000LL; n++) {
        if (isPandigital(n)) {
            t = n;
            for (int i = 9; i >= 0; i--) {
                arr[i] = t % 10; t /= 10;
            }
            

            out = false;
            for (int i = 1; i < 8; i++) {
                val = (100 * arr[i]) + 10 * arr[i+1] + arr[i+2];
                if ((val % primes[i - 1]) != 0) {
                    out = true; break;
                }
            }

            if (!out) {
                printf("%lld\n", n);
                sum += n;
            }
        }
    }

    printf("%lld\n", sum);

    return 0;
}