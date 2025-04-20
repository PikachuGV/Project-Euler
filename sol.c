/*
All square roots are periodic when written as continued fractions and can be written in the form:

   sqrt(N)=a0 + 1/(a1 + 1/(a2 + 1/(a3 + ...)))

For example, let us consider sqrt(23):
  sqrt(23) = 4 + sqrt(23) - 4 = 4 + 1/(1/(sqrt(23) - 4)) = 4 + 1/(1 + (sqrt(23)-3)/7)

If we continue we would get the following expansion:

   sqrt(23) = 4 + 1/(1 + 1/(3 + 1/(1 + 1/(8 + ...))))

The process can be summarised as follows:

  a0=4, 1/(sqrt(23) - 4) = (sqrt(23) + 4)/7 = 1 + (sqrt(23) - 3)/7
  a1=1, 7/(sqrt(23) - 3) = (7(sqrt(23) + 3))/14 = 3 + (sqrt(23) - 3)/2
  a2=3, 2/(sqrt(23) - 3) = (2(sqrt(23) + 3))/14 = 1 + (sqrt(23) - 4)/7
  a3=1, 7/(sqrt(23) - 4) = (7(sqrt(23) + 4))/7 = 8 + sqrt(23) - 4
  a4=8, 1/(sqrt(23) - 4) = (sqrt(23) + 4)/7 = 1 + (sqrt(23) - 3)/7
  a5=1, 7/(sqrt(23) - 3) = (7(sqrt(23) + 3))/14 = 3 + (sqrt(23) - 3)/2
  a6=3, 2/(sqrt(23) - 3) = (2(sqrt(23) + 3))/14 = 1 + (sqrt(23) - 4)/7
  a7=1, 7/(sqrt(23) - 4) = (7(sqrt(23) + 4))/7 = 8 + sqrt(23) - 4


It can be seen that the sequence is repeating. For conciseness, we use the notation sqrt(23)=[4;(1,3,1,8)], to indicate that the block (1,3,1,8) repeats indefinitely.

The first ten continued fraction representations of (irrational) square roots are:

  sqrt(2)=[1;(2)], period=1
  sqrt(3)=[1;(1,2)], period=2
  sqrt(5)=[2;(4)], period=1
  sqrt(6)=[2;(2,4)], period=2
  sqrt(7)=[2;(1,1,1,4)], period=4
  sqrt(8)=[2;(1,4)], period=2
  sqrt(10)=[3;(6)], period=1
  sqrt(11)=[3;(3,6)], period=2
  sqrt(12)=[3;(2,6)], period=2
  sqrt(13)=[3;(1,1,1,1,6)], period=5

Exactly four continued fractions, for N < 13, have an odd period.
How many continued fractions for N < 10000 have an odd period?
*/


/*
We can ignore all square numbers from 1 to 10000 for this qn.

For every ai, it will be the floor of the current term.
For example, a0 = floor(sqrtN). When we do one iteration, we get sqrt(N) ~ a0 + 1/[(sqrtN + a0) / (N - a0^2)]
a1 will thus be equal to floor([(sqrtN + a0) / (N - a0^2)])

This is because we know that 1/x > 0 for all x > 0. So consider ar + 1/(a(r+1) + 1/x)
Since we know x is a sum of 2 positive terms, it follows that x>0 -> a(r+1) + 1/x > 1 since a(r+1) >= 1.
Hence 1/(a(r+1) + 1/x) < 1, which will be the fractional part of ar + 1/(a(r+1) + 1/x). ar will hence be the integer part.


Notice that every iteration r will consist of a(r-1) + (sqrtN + A)/C
The next iteration will proceed as follows:
    1. Get ar = floor[(sqrtN + A) / C].
    2. We will then write the fraction as 1/[ar + (sqrtN - A') / C] where A = -A' + ar * C
    3. Now write (sqrtN + A') / C as 1/[C / (sqrtN + A')].
    4. We can then rationalise the denominator to get 1/[C(sqrtN + A') / C'] where C' = N - A'^2
    5. Now make the assumption that either C is a scalar multiple of C' or vice versa (it holds).
    6. Thus we have a(r-1) + 1/[ar + 1/((sqrtN + A')/C'')]

We can thus save A and C as the numerator and denominator variables since we assume sqrtN to always appear in all iterations in the numerator of the fraction.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

int genSquares(int n, int* array) {
    int i;
    for (i = 1; i * i <= n; i++) {
        array[i - 1] = i * i;
    }
    return i - 1;
}

int closestElementIndex(int N, int* arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] > N) return i;
    }
    return len;
}

int main() {
    double start = get_time();
    const int N = 10000;

    int *squares = malloc(N * sizeof(int));
    int c = genSquares(N, squares); squares = realloc(squares, c * sizeof(int));
    int floorsqrt, a, numerator, denominator,temp; //a = floor((floorsqrt(N) + numerator) / denominator) 
    int seennumerator, seendenominator;

    int odd = 0;

    for (int n = 2; n <= N; n++) {
        floorsqrt = closestElementIndex(n, squares, c);
        if (floorsqrt * floorsqrt == n) continue;
        
        a = floorsqrt; numerator = -floorsqrt; denominator = 1; //Start with floorsqrt + sqrtN - floorsqrt

        for (int i = 0; i < INT_MAX; i++) {
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

            if (i == 0) {
                seendenominator = denominator;
                seennumerator = numerator;
            } else {
                if (seendenominator == denominator && seennumerator == numerator) {
                    if ((i % 2) == 1) {
                        odd++;
                    }
                    break;
                }
            }
        }
    }

    printf("%d\nTime taken: %lf\n", odd, get_time() - start);



    return 0;
}