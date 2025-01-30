/*
An irrational decimal fraction is created by concatenating the positive integers:
0.123456789101112131415161718192021...
It can be seen that the 12th digit of the fractional part is 1.
If dn represents the nth digit of the fractional part, find the value of the following expression.
d1 * d10 * d100 * d1000 * d10000 * d100000 * d1000000
*/

/*
We have to note something here.
The quotient and the remainder can represent patterns.
Numbers with equal remainder are repeated every n terms.
Numbers with equal quotient have their quotient incremented every n terms.

Notice that dn for n<10 is just n.

Now from n=10 onwards the integers that are concatenated have multiple digits. So we need to be careful.
Notice that there are 100-10 = 90 2 digit numbers. This means that the length of the 2digit sequence is 180. Hence we will start the 2 digit sequence from n=10 to n=189.

Notice if we do a shift such that the range is now n=0 to n=170, then N = n/2 actually gives us the (N+1)th 2-digit number, which is 10+N. From there, we just need to check what n%2 is. If n%2==0, then we are talking about the tens place and thus the digit is (10+n)/10. Else, the digit is (10+n)%10

This is the same for d digits. Doing N = n/d gives us the (N+1)th d-digit number, which is 10^(d-1) + N. The digit is just given by ((10^(d-1) + N) / 10^(d-n%d-1)) % 10.

Now for the index shift to get the sequence of d digits, we have to shift n by 
1*(10-1)+2*(100-10+1)+3*(1000-100+1)+...+(d-1)*(10^(d-1) - 10^(d-2))
= 9 + sum(i*(10^i - 10^(i-1))) from i=2 to i=d-1
= 9 + sum(9i*10^(i-1)) from i=2 to i=d-1
= 9 + 9sum(i*10^(i-1)) from i=2 to i=d-1

We can calculate sum(i*10^(i-1)) using calculus.
Notice sum(x^i) from i=0 to i=n is 1+x+x^2+...+x^n = (x^(n+1) - 1) / (x - 1)
Differentiating we have sum(i*x^(i-1)) = ((x - 1)((n+1)*x^n) - (x^(n+1) - 1)) / (x - 1)^2
                                       = (n*x^(n+1) - (n+1)*x^n + 1) / (x - 1)^2
                                       = (x^n * (nx-n-1) + 1) / (x-1)^2

Substitute x=10 we have sum(i*10^(i-1)) from i=1 to i=n = (10^n * (9n-1) + 1) / 81

Thus the index shift will be
9 + 9((10^(d-1) * (9d-10) + 1) / 81 - 1)
= (10^(d-1) * (9d-10) + 1) / 9

For the nth digit, it falls in the sequence containing d digit integers, where d is the largest integer such that:
10^(d-1) * (9d-10) + 1) / 9 <= n

Thus we have this generalised method to find dn for any n:

1. Find the corresponding d-digit sequence for n. Let the starting index be D
2. Get N = n / d and R = n % d. D = 10^(d-1) + N
3. Digit is just (D / 10^(d-R-1)) % 10.
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

int getIndex(int d) {
    return (power(10,d-1) * (9*d-10) + 1) / 9;
}

int maxd(int n) {
    if (n < 10) return 1;
    for (int d = 2; d < 1000; d++) {
        if (n < getIndex(d)) {
            return d-1;
        }
    }
}


int main() {
    int d, D, N, nn, R, p = 1, t;
    for (int n = 1; n <= 1000000; n*=10) {
        if (n < 10) {
            p *= n;
            continue;
        }
        d = maxd(n); nn = n - getIndex(d) - 1;
        N = nn / d; R = nn % d; D = power(10,(d-1)) + N;
        p *= (D / power(10,d-R-1)) % 10;
    }

    printf("%d\n", p);
    return 0;
}