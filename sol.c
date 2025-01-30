/*
An irrational decimal fraction is created by concatenating the positive integers:
0.123456789101112131415161718192021...
It can be seen that the 12th digit of the fractional part is 1.
If dn represents the nth digit of the fractional part, find the value of the following expression.
d1 * d10 * d100 * d1000 * d_10000 * d100000 * d1000000
*/

/*
Notice that dn for n<10 is just n.

Now from n=10 onwards the integers that are concatenated have multiple digits. So we need to be careful.
Notice that there are 100-10+1 = 91 2 digit numbers. This means that the length of the 2digit sequence is 182. Hence we will start the 2 digit sequence from n=10 to n=191.

Every even n from n=10 to n=191 (starting with n=10) is a digit in the tens place. From n=10 to n=28 the tens place is 1, from n=30 to n=48 the tens place is 2, so on so forth. If we do an index shift such that we eliminate the first 9 digits (aka n-=10) then we will start from n=0 to n=181, and the intervals for identical tens place digit will be n=20i to n=20i+18. Thus, for any 0<=n<=181, the digit in the nth place is n/20 + 1 if n is even, and (n-1)%20 if n is odd.

With the same logic, the length of the 3 digit sequence is 3(1000-10+1) = 2703, thus we will index shift (n-=192) such that the range is n=0 to n=2702. From n=0 to n=297 the hundreds place is 1, n=300 to n=597 the hundreds place is 2 and so on. Every 3rd digit is a hundreds place digit. If n % 3 == 1, that means we are in the tens place. Notice that for n=1 to n=28 the tens place is 0. This is the same for n=301 to n=328. Finally if n % 3 == 2 then we are looking at the ones place. For n=2, n=302, n=602... the digit is 0.
So we can conclude that for 0<=n<=2702:
-If n%3==0 then the digit is n/300 + 1.
-If n%3==1 then the digit is (n%300)/30
-If n%3==2 then the digit is (n-2)%300

Now we can predict that for 4 digits, the range is from n=0 to n=36004. We can also predict that:
-If n%4==0, digit is n/4000 + 1
-If n%4==1, digit is (n%4000)/400
-If n%4==3, digit is (n-3)%4000

What happens if n%4==2? Well then we know we are talking about the tens digit. From n=2 to n=38 we have the digit being 0, n=42 to n=78 we have the digit being 1. So we can say that 
-If n%4==2, digit is (n%4000)/40

Now for the index shift to get the sequence of d digits, we have to shift n by 
1*(10-1)+2*(100-10+1)+3*(1000-100+1)+...+d*(10^d - 10^(d-1) + 1)
= 9 + sum(i*(10^i - 10^(i-1) + 1)) from i=2 to i=d
= 9 + sum(9i*10^(i-1) + i) from i=2 to i=d
= 9 + 9sum(i*10^(i-1)) from i=2 to i=d + d*(d+1)/2 - 1

We can calculate sum(i*10^(i-1)) using calculus.
Notice sum(x^i) from i=0 to i=n is 1+x+x^2+...+x^n = (x^(n+1) - 1) / (x - 1)
Differentiating we have sum(i*x^(i-1)) = ((x - 1)((n+1)*x^n) - (x^(n+1) - 1)) / (x - 1)^2
                                       = (n*x^(n+1) - (n+1)*x^n + 1) / (x - 1)^2
                                       = (x^n * (nx-n-1) + 1) / (x-1)^2

Substitute x=10 we have sum(i*10^(i-1)) from i=1 to i=n = (10^n * (9n-1) + 1) / 81

Thus the index shift will be
9 + 9((10^d * (9d-1) + 1) / 81 - 1) + d*(d+1)/2 - 1
= (10^d * (9d-1) + 1) / 9 + d*(d+1)/2 - 1

For the nth digit, it falls in the sequence containing d digit integers, where d is the largest integer such that:
(10^d * (9d-1) + 1) / 9 + d*(d+1)/2 - 1 <= n

Thus we have this generalised method to find dn for any n:

1. Find the corresponding d-digit sequence for n. Let the starting index be D
2. Do n-=D. Get n % d.
3. If n%d==0 then the digit is n/(d*10^d) + 1
4. If n%d==d-1 then the digit is (n-d+1)%(d*10^d)
5. Else, let x=n%d, then the digit is (n%(d*10^d))/(d*10^(d-1))
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    return 0;
}