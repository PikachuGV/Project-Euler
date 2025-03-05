/*
A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.
Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/

/*
Lets say the digital sum of a number N is d.
Notice that for N with n digits, max d = 9n, min d = 1, with d=1 being when N=10^(n-1)
So if our current maximum d = D, we only need to check numbers that have more than floor(D/9) digits. 
Starting from a=99, b=99 and working our way down b will help alot. We just decrement b until we either hit the digit floor or reach b=1, at which we decrement a and reset b. If we cut at b=99 at a certain a=A, then since a^b < A^99 for all a<A, b<=99, we can stop the checking process.s
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//Assume a is biggest
char *add(char *a, char *b) {
    if (a[0] == 47) {
        printf("OH NO");
    }
    if (strlen(a) > strlen(b)) {
        char *temp = malloc(strlen(b) * sizeof(char)); strcpy(temp, b);
        char *zeros = calloc(strlen(a) - strlen(b) + 1, sizeof(char));
        memset(zeros, '0', (strlen(a) - strlen(b)) * sizeof(char));
        b = calloc(strlen(a) + 1, sizeof(char));
        strcat(b, zeros); strcat(b, temp);
        free(zeros); free(temp);
    }
    int len = strlen(a);
    int digit = 0, carry = 0;
    
    char *c = calloc((len + 2), sizeof(char));
    
    for (int i = len - 1; i >= 0; i--) {
        digit = ((a)[i] - '0') + ((b)[i] - '0') + carry;
        carry = digit / 10;
        /* if (carry > 9 || carry < 0) {
            ("%s, %s, %d", (a), (b), carry);
            exit(100);
        } */
        c[i + 1] = (digit % 10) + '0';
    }

    if (carry == 0) {
        char *C = calloc((len + 1), sizeof(char));
        memcpy(C, c + 1, len * sizeof(char));
        free(c);
        return C;
    }
    c[0] = carry + '0';
    return c;
}

//Assume a is biggest.
char *mul(char *a, char *b) {
    int lena = strlen(a), lenb = strlen(b);
    int digit = 0, carry = 0, product = 0;

    char *A = calloc(lena + lenb + 1, sizeof(char)), *B = calloc(lena + lenb + 1, sizeof(char)), *C;
    memset(A, '0', (lena + lenb) * sizeof(char)); memset(B, '0', (lena + lenb) * sizeof(char));

    for (int i = lenb - 1; i >= 0; i--) {
        digit = (int)(b[i] - '0'); carry = 0;
        for (int j = lena - 1; j >= 0; j--) {
            product = (int)(a[j] - '0') * digit + carry;
            B[i + j + 1] = (product % 10) + '0';
            carry = (product / 10);
        }
        B[i] = carry + '0';
        C = add(A, B);
        free(A); A = calloc(strlen(C) + 1, sizeof(char)); memcpy(A, C, strlen(C) * sizeof(char));
        free(B); B = calloc(lena + lenb + 1, sizeof(char)); memset(B, '0', (lena + lenb) * sizeof(char));
        free(C);
    }
    if (A[0] == '0') {
        char *new = calloc(lena + lenb, sizeof(char));
        memcpy(new, A + 1, (lena + lenb) * sizeof(char));
        free(A);
        return new;
    }
    return A;
}

void getpows(char *(*nums)[99], char *a) {
    char *temp;
    (*nums)[0] = calloc(strlen(a) + 1, sizeof(char));
    strcpy((*nums)[0], a);
    for (int i = 1; i < 99; i++) {
        temp = mul((*nums)[i - 1], a);
        (*nums)[i] = calloc(strlen(temp) + 1, sizeof(char));
        strcpy((*nums)[i], temp);
        free(temp);
    }
}

int digitsum(char *n) {
    int sum = 0;
    for (int i = 0; i < strlen(n); i++) {
        sum += (n[i] - '0');
    }
    return sum;
}

int main() {
    char *nums[99], *A, *num, *largestnum = malloc(0);
    int largest = 0, a, b, sum;
    A = calloc(3, sizeof(char));


    for (a = 99; a > 0; a--) {
        sprintf(A, "%d", a);
        getpows(&nums, A);
        for (b = 99; b > 0; b--) {
            num = nums[b - 1];
            if (strlen(num) <= largest / 9) break;
            sum = digitsum(num);
            if (sum > largest) {
                largest = sum;
                free(largestnum);
                largestnum = calloc(strlen(num) + 1, sizeof(char));
                strcpy(largestnum, num);
            }
        }
        for (int i = 0; i < 99; i++) free(nums[i]);
        if (b == 99) break;
    }
    printf("%d, %s\n", largest, largestnum);
    return 0;
}