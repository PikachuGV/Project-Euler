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

char *add(char *a, char *b) {
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

char** gena(int N) {
    char** arr = (char**)malloc(N * sizeof(char*));
    for (int i = 1; i < N; i++) arr[i] = "1";
    arr[0] = "2";

    char *multiple = "0";

    for (int i = 2; i < N; i += 3) {
        multiple = add(multiple, "2");
        arr[i] = multiple;
    }

    return arr;
}

int sumdigits(char n) {
    int sum = 0;
    while (n != 0) {
        sum += (n % 10);
        n /= 10;
    }

    return sum;
}

int main() {
    const int N = 100;
    char** a = gena(N);

    char *pa = "1", *pb = a[0], *pc;

    for (int i = 1; i < N; i++) {
        pc = add(a[i] * pb + pa;
        pa = pb; pb = pc;
        printf("%llu ", pc);
    }
    printf("%d\n", sumdigits(pc));

    free(a);
    return 0;
}