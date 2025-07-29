/*
By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and making use of the four arithmetic operations (+, -, *, /) and brackets/parentheses, it is possible to form different positive integer targets.
For example,

8 = (4 * (1 + 3)) / 2
14 = 4 * (3 + 1 / 2)
19 = 4 * (2 + 3) - 1
36 = 3 * 4 * (2 + 1)

Note that concatenations of the digits, like 12 + 34, are not allowed.
Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different target numbers of which 36 is the maximum, and each of the numbers 1 to 28 can be obtained before encountering the first non-expressible number.
Find the set of four distinct digits, a < b < c < d, for which the longest set of consecutive positive integers, 1 to n, can be obtained, giving your answer as a string: abcd.
*/

/*
There are 10C4 = 210 possible set of digits.

We can do a depth based search to solve this problem.
We first choose a digit and then remove it from the list. Then choose an operator and do the operation first (since brackets can force the order of operations). After that we go down the search tree and continue the search until all digits are used.
We then add the final result to an array and continue trying other opeartors and digits.

However, such method will miss out on the expression of the form (a+-b)*(c+-d) or (a+-b)/(c+-d)
*/



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define CHAR_LENGTH 1024
#define NCR 210
#define N 10

#define max(a,b) ((a>b) ? a : b)

typedef enum o {
    ADD,
    SUB,
    MUL,
    DIV
} OPERATIONS;

int bitsset10[1<<N] = {0};
int bitsset2[1<<N] = {0};

double eval(double a, double b, OPERATIONS operator) {
    switch (operator)
    {
    case ADD:
        return a+b; 
    case SUB:
        return a-b;
    case MUL:
        return a*b;
    case DIV:
        return a/b;
    }
}

void search(int avaliable, double result, char arr[CHAR_LENGTH]) {
    double d, temp;
    int has2bits = (bitsset2[avaliable] == 1), sum = 0, diff = -1;
    if (avaliable == 0) {
        if (result <= 0.0 || modf(result, &temp) != 0 || isinf(result)) return;
        int bit = (int)result;
        arr[bit/8] |= (0x80 >> (bit%8));
        return;
    }

    for (int i = 0; i < 10; i++) {
        if ((1<<i) & avaliable) {
            if (has2bits) {
                sum += i;
                diff = (diff == -1) ? i : diff - i;
            }
            avaliable ^= (1<<i);
            d = (double)(i);
            search(avaliable, eval(result, d, ADD), arr);
            search(avaliable, eval(result, d, SUB), arr);
            search(avaliable, eval(result, d, MUL), arr);
            search(avaliable, eval(result, d, DIV), arr);
            avaliable ^= (1<<i);
        }
    }

    if (has2bits) {
        d = (double)(sum);
        search(0, eval(result, d, MUL), arr);
        search(0, eval(result, d, DIV), arr);
        d = (double)(diff);
        search(0, eval(result, d, MUL), arr);
        search(0, eval(result, d, DIV), arr);
    }
}

void initbitset() {
    bitsset10[0] = 0;
    for (int i = 0; i<(1<<N); i++) {
        bitsset10[i] = (i & 1) + bitsset10[i >> 1];
    }

    int bitstring;
    for (int i = 1; i < 10; i++) {
        bitstring = (1<<i) | 1;
        while ((bitstring & 0x800) == 0) {
            bitsset2[bitstring] = 1;
            bitstring <<= 1;
        }
    }
}

int *genArrangements(int r, int n) {
    //Generate all arranges of r numbers in a range of N numbers.
    int *arr = calloc(NCR, sizeof(int)), idx = 0;
    for (int i = 0; i < (1<<n); i++) {
        if (bitsset10[i] == r) {
            arr[idx] = i; idx++; 
        }
    }
    return arr;
}

int main() {
    initbitset();
    int *arrangements = genArrangements(4, N);

    char seen[CHAR_LENGTH] = {0};
    int avaliable, n = 0, maxarrangement;

    for (int idx = 0; idx < NCR; idx++) {
        avaliable = arrangements[idx];
        for (int i = 0; i < 10; i++) {
            if ((avaliable & (1<<i)) == 0) continue;
            avaliable ^= (1<<i);
            search(avaliable, (double)i, seen);
            avaliable ^= (1<<i);
        }

        for (int i = 1; i < CHAR_LENGTH*8; i++) {
            if ((seen[i/8] & (0x80 >> (i % 8))) == 0) {
                if (i-1 > n) {
                    n = i-1; maxarrangement = arrangements[idx];
                }
                printf("%d %d\n",avaliable, i-1);
                break;
            }
        }
        memset(seen, 0, sizeof(seen));
    }

    printf("%d, ", n);
    for (int i = 0; i < 10; i++) {
        if (((1<<i) & maxarrangement) != 0) printf("%d",i);
    }
    return 0;
}