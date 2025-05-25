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
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    return 0;
}