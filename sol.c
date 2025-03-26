/*
The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit number, 134217728=8^9, is a ninth power.
How many n-digit positive integers exist which are also an nth power?
*/

/*
Lets say the n-digit number is equal to a^n. Notice that 2<=a<10 since 10^n creates a n+1 digit number.
For every a, we can find range of n for which a^n has n digits.
This is equivalent to saying that n-1 <= lg(a^n) < n
-> n-1 <= nlga < n -> 1 - 1/n <= lga < 1
We just need 1 - 1/n <= lga since we know a < 10 -> lga < 1.
This gives us 1/n >= 1 - lga, n <= 1/(1 - lga).

Keeping a precalculated array of lga for 2 <= a <= 9 will help us in solving this problem.
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

//log10 a = logs[a - 2]
const double logs[] = {0.30102999566, 0.47712125472, 0.60205999132, 0.69897000433, 0.77815125038, 0.84509804001, 0.90308998699, 0.95424250943};

int main() {
    double start = get_time();
    int sum = 0;
    for (int a = 1; a < 10; a++) {
        sum += 1/(1 - logs[a - 2]);
    }
    double time = get_time() - start;
    printf("%d\nTime taken: %lf", sum, time);
    return 0;
}