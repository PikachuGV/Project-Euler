/*
Q30: Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4

As 1 = 1^4 is not a sum it is not included.
The sum of these numbers is 1634 + 8208 + 9474 = 19316.
Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int* powers(int N, int b) {
    int *arr = malloc((N + 1) * sizeof(int));
    int n;
    for (int i = 0; i < N + 1; i++) {
        n = 1;
        for (int j = 0; j < b; j++) n *= i;
        arr[i] = n;
    }

    return arr;
}

int main() {
    clock_t start = clock();
    int* fifths = powers(10, 5);
    int n, sum, total = 0;
    for (int i = 10; i < 354294; i++) {
        n = i; sum = 0;
        while (n != 0) {
            sum += fifths[n % 10];
            n /= 10;
        }
        if (sum == i) {
            total += i;
        }
    }
    printf("%d\n", total);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n", time);
    return 0;
}
