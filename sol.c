/*
Consider quadratic Diophantine equations of the form:
x^2 - Dy^2 = 1
For example, when D=13, the minimal solution in x is 649^2 - 13 * 180^2 = 1.
It can be assumed that there are no solutions in positive integers when D is square.
By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:

3^2 - 2 * 2^2 = 1
2^2 - 3 * 1^2 = 1
9^2 - 5 * 4^2 = 1
5^2 - 6 * 2^2 = 1
8^2 - 7 * 3^2 = 1

Hence, by considering minimal solutions in x for D < 7, the largest x is obtained when D=5.
Find the value of D < 1000 in minimal solutions of x for which the largest value of x is obtained.
*/

/*
This is known as Pell's equation. Finding the minimial solutions is the same thing as finding the fundemental solutions to Pell's equation.

Interestingly, this equation is solvable using continued fractions.

We know that sqrt(D) = [a1; a2, a3, a4 ... an, 2a1, a2, a3 ...]. n is the period of the continuous fraction.
Letting a(n+1) = [2a1, a2, a3 ...] = sqrt(N) + a1, we have sqrt(D) = [a1, a2, a3 ... an, a(n+1)]

We also know sqrt(N) = (a(n+1)pn + p(n-1)) / (a(n+1)qn + q(n-1)) where ith convergent = pi/qi = [a1, a2 ... ai]

This means that 
    sqrt(N) = ((sqrt(N) + a1)pn + p(n-1)) / ((sqrt(N) + a1)qn + q(n-1))
which gives us
    (sqrt(N) + a1)qn*sqrt(N) + q(n-1)sqrt(N) = (sqrt(N) + a1)pn + p(n-1) 
or upon simplifying
    Nqn + (a1qn + q(n-1))sqrt(N) = (a1pn + p(n-1)) + pn sqrt(N)

We can hence deduce by comparing integers and surds that
    Nqn = (a1pn + p(n-1)), (a1qn + q(n-1)) = pn

Solving gives 
    p(n-1) = Nqn - a1pn, q(n-1) = pn - a1qn

We know that pn q(n-1) - qn p(n-1) = (-1)^n. Thus by subbing p(n-1) and q(n-1), we get
    pn (pn - a1qn) - qn (Nqn - a1pn) = (-1)^n
or simply
    (pn)^2 - N(qn)^2 = (-1)^n

If n is even, then pn, qn is the fundemental solution.
If n is odd, then p2n, q2n is the fundemental solution.


We know that 
    pi = aip(i-1) + p(i-2)
    qi = aiq(i-1) + q(i-2)
where 
    p0 = 1, p1 = a1
    q0 = 0, q1 = 1

At the same time, we can calculate ai using the process done in Q64.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int squares[] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961};

const int nSquares = 31;

int closestElementIndex(int N) {
    for (int i = 0; i < nSquares; i++) {
        if (squares[i] > N) return i;
    }
    return nSquares;
}

int partialQuotient(int floorsqrt, int n, int *fraction) {
    int a, numerator, denominator,temp; //a = floor((floorsqrt(N) + numerator) / denominator) 

    numerator = fraction[0]; denominator = fraction[1];

    
    //Swap numerator and denominator
    numerator ^= denominator; denominator ^= numerator; numerator ^= denominator;
    
    //Saves the denominator for later use
    temp = denominator;
    //Rationalise denominator
    denominator = n - abs(denominator * denominator);

    //Ensures that there is a common multiple, else this method will not work.
    if ((denominator % numerator) != 0 && (numerator % denominator) != 0) {
        printf("Error: no common factors."); exit(1);
    }

    if (denominator > numerator) {
        denominator /= numerator; numerator = 1;
    } else {
        numerator /= denominator; denominator = 1;
    }

    //Changes sign of the old denominator value, since rationalising involves the flipping of sign.
    numerator = -temp;
    a = (floorsqrt + numerator) / denominator;

    numerator -= (denominator * a); //Removes the a from the fraction

    fraction[0] = numerator; fraction[1] = denominator;
    return a;
}

//Assume a is biggest
char *add(char *a, char *b) {
    if (strlen(a) > strlen(b)) {
        char *temp = malloc((strlen(b) + 1) * sizeof(char)); strcpy(temp, b);
        char *zeros = calloc(strlen(a) - strlen(b) + 1, sizeof(char));
        memset(zeros, '0', (strlen(a) - strlen(b)) * sizeof(char));
        b = calloc(strlen(a) + 1, sizeof(char));
        strcat(b, zeros); strcat(b, temp);
        free(temp);
        free(zeros); 
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

bool isGreater(char *a, char *b) {
    if (strlen(a) > strlen(b)) return true;
    if (strlen(b) > strlen(a)) return false;

    return (strcmp(a, b) > 0);
}

int main() {
    const int N = 1000;

    int floorsqrt, fraction[2], a, target, targetIndex, maxn = 0;

    char *x, *y, *px, *py, *t, *tx, *ty, *A, *maxx = calloc(40, 1);

    for (int n = 1; n <= N; n++) {
        floorsqrt = closestElementIndex(n);
        if (floorsqrt * floorsqrt == n) continue;
        fraction[0] = -floorsqrt; fraction[1] = 1; target = 2 * floorsqrt, targetIndex = UINT_MAX;
        //Our fraction is (sqrtN + n)/d) = 1/(ar + (sqrtN +n')/d'). So to make sure we start with ar = a2, we use n=-floorsqrt and d=1. Our fraction then becomes sqrtN-floorsqrt. 
        //Remember that to find a1 we do floorsqrt + sqrtN - floorsqrt. So the sqrtN-floorsqrt will give us a2.
        
        px = calloc(2, sizeof(char)); x = calloc(3, sizeof(char));
        py = calloc(2, sizeof(char)); y = calloc(2, sizeof(char));
        tx = calloc(2, sizeof(char)); ty = calloc(2, sizeof(char));
        A = calloc(3, sizeof(char));

        px[0] = '1'; sprintf(x, "%d", floorsqrt); py[0] = '0'; y[0] = '1';
        
        for (int i = 1; i < 100; i++) {
            a = partialQuotient(floorsqrt, n, fraction);
            sprintf(A, "%d", a);

            t = mul(x, A); tx = add(t, px); free(t);
            t = mul(y, A); ty = add(t, py); free(t);

            free(px); free(py);
            px = x; x = tx; py = y; y = ty;

            //strcpy(px, x); strcpy(py, y); strcpy(x, tx); strcpy(y, ty);

            if (a == target) {
                if (i % 2 == 0) {
                    printf("%d: %s, %s\n", n, px, py); fflush(stdout);
                    if (isGreater(px, maxx) ) {
                        strcpy(maxx, px); maxn = n;
                    }
                    break;
                } else {
                    targetIndex = 2 * i;
                }
            }
            
            if (i == targetIndex) {
                printf("%llu: %s, %s\n", n, px, py);fflush(stdout);
                if (isGreater(px, maxx)) {
                    strcpy(maxx, px); maxn = n;
                }
                break;
            }
        }
        
        free(px); free(py); free(x); free(y);
    }

    printf("Max x: %s. Found at: %llu\n", maxx, maxn);

    

    return 0;
}
