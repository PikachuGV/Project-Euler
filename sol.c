/*
Q23: A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int power(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++) {
        c *= a;
    }
    return c;
}

int sumpdiv(int n) {
    int total, factor, c, m;

    total = 1, factor = 1, c = 0, m = n; 
    while (n % 2 == 0) {
        n /= 2;
        c++;
        factor += (1 << c);
    }
    total *= factor;
    for (int j = 3; j * j <= n; j += 2) {
        factor = 1;
        c = 0;
        while (n % j == 0) {
            n/=j,
            c++,
            factor += power(j, c);
        }    
        total*=factor;
    }
    if (n != 1) total *= (1 + n);

    total -= m;

    return total;
}

int search(int* arr, int n, int len) {
    if (len == 1 && arr[0] != n) return -1;
    int mid = len / 2;

    if (arr[mid] == n) return mid;
    
    if (arr[mid] > n) {
        return search(arr, n, mid);
    } else {
        return search(&arr[mid + 1], n, len - mid);
    }
}

int greatestindex(int* abundant, int len, int n) {
    int index;
    for (index = 0; index < len; index++) {
        if (abundant[index] > n) return index;
    }
    return index;
}

int main() {
    int N = 28123;

    int* abundant = malloc(0);
    int len = 0;

    for (int i = 1; i <= N; i++) {
        if (sumpdiv(i) > i) {
            len++;
            abundant = realloc(abundant, len * sizeof(int));
            abundant[len - 1] = i;
        }
    }

    int total = 0;

    for (int i = 1; i <= N; i++) {
        int diff, index = greatestindex(abundant, len, i);
        int out = 0;
        for (int j = 0; j < index; j++) {
            diff = i - abundant[j];
            if (search(abundant, diff, len) != -1) {
                out = 1;
                break;
            }
        }
        if (out == 0) {
            total += i;
        }
    }

    printf("%d\n", total);
    return 0;
}