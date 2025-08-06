/*
If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, and two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21) * (14/20) = 1/2.
The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, is a box containing eighty-five blue discs and thirty-five red discs.
By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total, determine the number of blue discs that the box would contain.
*/

/*
This is a very special question. We will be solving this entirely by hand and using calculators.

B/T * (B-1)/(T-1) = 1/2
2B(B-1) = T(T-1)
2B^2 - 2B = T(T-1)
B = (2+sqrt(4+8(T)(T-1)))/4
  = 0.5(1 + sqrt(1 + 2T(T-1)))

We need 1 + 2T(T-1) to be perfect square. Let m = sqrt(1 + 2T(T-1))
2T^2 - 2T + 1 = m^2
4T^2 - 4T + 2 = 2m^2
(2T-1)^2 - 2m^2 = -1

Let x=2T-1, y=m. This is a Negative Pell Equation.
Solutions are x(n+1) = 3xn + 4yn, y(n+1) = 2xn + 3yn, x1=y1=1   

We can calculate that xn ~ 1/2 (1+sqrt2)(3+2sqrt2)^(n-1) and y ~ 1/4 (2+sqrt2)(3+2sqrt2)^(n-1) for large n by expressing the system of reccurence relation as a matrix equation and solving for closed form. (The reason for the approximation is due to a (3-2sqrt2)^(n-1) in both terms. Since 3-2sqrt2 ~ 0.17, for large n it tends to 0.)

So 2T-1 = 1/2 (1+sqrt2)(3+2sqrt2)^(n-1) and T > 10^12 
Thus we have n > ((ln(10^12 - 2) - ln(1+sqrt2)) / ln(3+2sqrt2)) + 1 ~ 16.17

Hence try n=17. We get x=2140758220993 and y=1513744654945
Thus we havae B = 0.5(1+1513744654945) = 756872327473
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main() {
    return 0;
}