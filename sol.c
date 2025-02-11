/*
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/

/*
Notice the last 10 digits is determined by the last 10 digits of the base.
Also notice that we can perform lesser multiplications by splitting the exponent into its base 2 bits.
Consider 20^20. 20 = 0b10100. So 20^20 = 20^4 * 20^16. This is easier to calculate as 20^4 = (20^2)^2 and 20^16 = ((20^4)^2)^2).
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ULL unsigned long long

ULL mul(ULL a, ULL b) {
    if (a > 9999999999ULL || b > 9999999999ULL) {exit(1000);}
    ULL d, ans = 0, t = 10000000000ULL;
    for (int i = 0; i < 10; i++) {
        d = b % 10;
        ans += ((a * d) % t) * (10000000000ULL / t); ans %= 10000000000; 
        b /= 10; t /= 10;
    }
    return ans;
}

ULL ltd(int n) {
    ULL N = (ULL)n;
    ULL t = 1;
    if ((n & 1) != 0) {
        t *= n;
    }
    for (int i = 1; i < 10; i++) {
        if ((1<<i) > n) break;
        N = mul(N, N) % 10000000000;
        if ((n & (1<<i)) != 0) {
            t = mul(t, N);
        }
    }
    return t;
}

int main() {
    ULL s = 0, l;
    for (int i = 1; i <= 1000; i++) {
        l = ltd(i);
        s += l;
    }
    printf("%llu\n", s % 10000000000);
    return 0;
}