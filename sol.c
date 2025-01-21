/*
Q26: A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2 = 0.5
1/3 = 0.(3)
1/4 = 0.25
1/5 = 0.2
1/6 = 0.1(6)
1/7 = 0.(142857)
1/8 = 0.125
1/9 = 0.(1)
1/10 = 0.1

Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

/*
Take 1/7 as an example
10/7 = 1 remainder 3 (index 1)
30/7 = 4 remainder 2 (index 2)
20/7 = 2 remainder 6 (index 3)
60/7 = 8 remainder 4 (index 4)
40/7 = 5 remainder 5 (index 5)
50/7 = 7 remainder 1 (index 6)
10/7 = 1 remainder 3 (index 7)
The recurring pattern is seen when the quotient and remainders repeat. Hence the length is 6.

Take 1/6 as an example.
10/6 = 1 remainder 4
40/6 = 6 remainder 4
40/6 = 6 remainder 4
The length is 1

We can deduce that, ignoring 0s, the maximum possible recursion length is 9. If we repeat a non-zero digit, that means we will be repeating the cycles. For example, if we get the numbers 1,2,3,4,5,1, then the next one will be 2.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int N = 1000;
    int n, q, r, ans;
    int longest = -1;
    int qrp[10 * N];
    for (int i = 2; i < N; i++) {
        n = 10; memset(qrp, 0, sizeof(qrp));
        for (int c = 1; c < __INT_MAX__; c++) {
            q = n / i; r = n % i;
            if (r == 0) break;
            if (qrp[10 * q + r] != 0 && q != 0) {
                if (longest < c - qrp[10 * q + r]) {
                    ans = i; longest = c - qrp[10 * q + r];
                }
                break;
            }
            qrp[10 * q + r] = c;
            n = r * 10;
        }
    }
    printf("%d\n", ans);
    return 0;