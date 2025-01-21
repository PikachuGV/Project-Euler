/*
Q25: The Fibonacci sequence is defined by the recurrence relation:
Fn = F{n - 1} + F{n - 2}, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:

F1 = 1
F2 = 1
F3 = 2
F4 = 3
F5 = 5
F6 = 8
F7 = 13
F8 = 21
F9 = 34
F{10} = 55
F{11} = 89
F{12} = 144

The 12th term, F{12}, is the first term to contain three digits.
What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int* add(int* a, int* b, int lena, int lenb, int* lenc) {
    if (lena < lenb) {
        a = realloc(a, sizeof(int) * lenb);
        for (int i = lena; i < lenb; i++) a[i] = 0;
        lena++;
    } else if (lena > lenb) {
        b = realloc(b, sizeof(int) * lena);
        for (int i = lenb; i < lena; i++) b[i] = 0;
        lenb++;
    }

    *lenc = lena;

    int* c = calloc(*lenc, sizeof(int));
    int carry = 0, sum;
    for (int i = 0; i < *lenc; i++) {
        sum = a[i] + b[i] + carry;
        c[i] = sum % 10; carry = sum / 10;
    }

    if (carry > 0) {
        (*lenc)++;
        c = realloc(c, sizeof(int) * *lenc);
        c[*lenc - 1] = carry;
    }
    return c;
}

int main() {
    int *a = malloc(sizeof(int)), *b = malloc(sizeof(int)), *c = malloc(sizeof(int));
    a[0] = 1; b[0] = 1; c[0] = 0;
    int lena = 1, lenb = 1, lenc = 1;

    for (int i = 3; i < INT_MAX; i++) {
        c = add(a, b, lena, lenb, &lenc);
        if (lenc == 1000) {
            printf("%d\n", i);
            break;
        }
        a = b; b = c;
        lena = lenb; lenb = lenc;
        
    }

    return 0;
}