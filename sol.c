/*
It is possible to show that the square root of two can be expressed as an infinite continued fraction.
sqrt2 = 1 + 1/(2 + 1/(2 + 1/(2 + ...)))
By expanding this for the first four iterations, we get:
1 + 1/2 = 3/2 = 1.5
1 + 1/(2 + 1/2) = 7/5 = 1.4
1 + 1/(2 + 1/(2 + 1/2)) = 17/{12 = 1.41666...
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
The next three expansions are 99/70, 239/169/, and 577/408/, but the eighth expansion, 1393/985, is the first example where the number of digits in the numerator exceeds the number of digits in the denominator.
In the first one-thousand expansions, how many fractions contain a numerator with more digits than the denominator?
*/

/*
Notice if we let An be the nth expansion, then
A(n+1) = 1 + 1/(1 + An) = (2 + An) / (1 + An)

Letting An = an/bn, we have
A(n+1) = (2bn + an) / (bn + an)

Notice gcd(2bn + an, bn + an) = gcd(an + bn, bn) = gcd(an, bn). So if an and bn are coprime, then so are 2bn+an and bn+an. Hence we know that we do not need to simplify the fraction if we have coprime an and bn.

This is actually really helpful. If we think about this carefully, we realise that a1 and b1 are obviously coprime. This implies that 2b1+a1 and b1+a1 are also coprime, so (2b1+a1)/b1+a1 is the simplified fraction. So we can say a2 = 2b1+a1 and b2 = b1+a1. This logic follows per induction, so we can say that we dont actually need to do any simplification.

Hence we just need to look at the following system of recurrence relations:
a(n+1) = 2bn + an
b(n+1) = bn + an
with initial conditions a1 = 3, b1 = 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

char *add(char *a, char *b) {
    if (strlen(a) > strlen(b)) {
        char *temp = malloc((strlen(b) + 1) * sizeof(char)); strcpy(temp, b);
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
        if (carry > 9 || carry < 0) {
            ("%s, %s, %d", (a), (b), carry);
            exit(100);
        } 
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

int main() {
    clock_t start = clock();
    char *a = calloc(2, sizeof(char)), *b = calloc(2, sizeof(char)), *A, *B;
    a[0] = '3'; b[0] = '2';
    int c = 0;
    for (int i = 1; i < 999; i++) {
        B = add(a, b); A = add(B, b);
        free(b); b = calloc(strlen(B) + 1, sizeof(char));
        strcpy(b, B); free(B);
        free(a); a = calloc(strlen(A) + 1, sizeof(char));
        strcpy(a, A); free(A);

        if (strlen(a) > strlen(b)) c++;
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%d\nTime Taken: %lf\n", c, time);
    return 0;
}