/*
Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.

OOOOO
OOOO   O
OOO   OO
OOO   O   O
OO   OO   O
OO   O   O   O
O   O   O   O   O

Find the least value of n for which p(n) is divisible by one million.
*/

/* 
There is no closed form for p(n).

However there is a recurrence relation, which is given as

p(n) = p(n-P0) + p(n-P1) - p(n-P2) - p(n-P3) + p(n-P4) +...
where Pi is the ith pentagonal number, with P0 = 1.
It is taken that p(0) = 1 and p(k) = 0 for negative k.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 100000
typedef unsigned long long ULL;


void genPen(ULL** arr, int n) {
    *arr = malloc(n * sizeof(ULL));
    int c = 0;
    for (int i = 1; i <= n/2; i++) {
        (*arr)[c] = (3*i*i - i)/2; c++;
        (*arr)[c] = (3*i*i + i)/2; c++;
    }
}


int main() {
    int *p = calloc(N, sizeof(int));
    ULL *pen; genPen(&pen, N);

    p[0] = 1;

    int P; int index;

    for (int i = 1; i < N; i++) {
        P = 0; index = 0;
        for (int j = 0; j < N; j++) {
            if (i < pen[j]) break;
            index = i - pen[j];
            if ((j % 4) < 2) {
                P += p[index];
            } else {
                P -= p[index];
            }
        }

        P %= 1000000;
        if (P < 0) P += 1000000;
        p[i] = P;

        if (P == 0) {
            printf("%d ",i); break;
        }
    }
}

