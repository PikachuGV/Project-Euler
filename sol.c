/*
The square root of 2 can be written as an infinite continued fraction.
sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + 1/(2 + ...))))
The infinite continued fraction can be written, sqrt(2) = [1; (2)], (2) indicates that 2 repeats ad infinitum. In a similar way, sqrt(23) = [4; (1, 3, 1, 8)].
It turns out that the sequence of partial values of continued fractions for square roots provide the best rational approximations. Let us consider the convergents for sqrt(2).

1 + 1/2 = 3/2 
1 + 1/(2 + 1/2) = 7/5
1 + 1/(2 + 1/(2 + 1/2)) = 17/12
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29

Hence the sequence of the first ten convergents for sqrt(2) are:
1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985, 3363/2378, ...
What is most surprising is that the important mathematical constant, e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, ... , 1, 2k, 1, ...].
The first ten terms in the sequence of convergents for e are:
2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
The sum of digits in the numerator of the 10th convergent is 1 + 4 + 5 + 7 = 17.
Find the sum of digits in the numerator of the 100th convergent of the continued fraction for e.
*/

/*
Let the ith convergent be denoted as pi / qi. It is known that
pi = ai * p(i-1) + p(i-2) and qi = ai * q(i-1) + q(i-2)
where p(-1) = 1, p0 = a0, q(-1) = 0, q0 = 1

We can first generate all ai for 0<=i<100. Then use the recurrence to help us get the final numerator.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ULL unsigned long long

ULL* gena(int N) {
    ULL* arr = (ULL*)malloc(N * sizeof(ULL));
    for (int i = 1; i < N; i++) arr[i] = 1;
    arr[0] = 2;

    for (ULL i = 2; i < N; i += 3) {
        arr[i] = 2 * (i + 1) / 3;
    }

    return arr;
}

int sumdigits(ULL n) {
    int sum = 0;
    while (n != 0) {
        sum += (n % 10);
        n /= 10;
    }

    return sum;
}

int main() {
    const int N = 100;
    ULL* a = gena(N);

    ULL pa = 1LL, pb = (long long)a[0], pc;

    for (int i = 1; i < N; i++) {
        pc = a[i] * pb + pa;
        pa = pb; pb = pc;
        printf("%llu ", pc);
    }
    printf("%d\n", sumdigits(pc));

    free(a);
    return 0;
}