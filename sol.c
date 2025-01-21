/*
Q28: Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?*/

/*
1 by 1:
1

3 by 3:
7 8 9
6 1 2
5 4 3

5 by 5:
21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

7 by 7:
43 44 45 46 47 48 49
42 21 22 23 24 25 26
41 20  7  8  9 10 27
40 19  6  1  2 11 28
39 18  5  4  3 12 29
38 17 16 15 14 13 30
37 36 35 34 33 32 31

For each ith ring, where 1st ring is 1 and 3rd ring is from 2 to 9, (i is odd)
The top right number is i^2, bottom left number is (i-1)^2 +1 = i^2 - 2i + 2
Top left number is i^2 - (i-1) = i^2 - i + 1
Top right number is (i-1)^2 + 1 - (i - 1) = i^2 - 3i + 3

Sum of the 4 corners will thus be 
i^2 + i^2 - 2i + 2 + i^2 - i + 1 + i^2 - 3i + 3 
= 4i^2 -6i + 6 = 2(2i^2 -3i + 3)

So total sum = 1 + summation of 2(2i^2 -3i + 3) for odd 3 <= i <= 1001
We can write i = 2k + 1 then the sum will be from 1<=k<=500

  2 * sum(2(2k + 1)^2 -3(2k + 1) + 3)
= 2 * sum(2(4k^2 + 4k + 1) -3(2k + 1) + 3)
= 2 * sum(8k^2 + 8k + 2 -6k - 3 + 3)
= 2 * sum(8k^2 + 2k + 2)
= 4 * sum(4k^2 + k + 1) from 1 to limit n
= 8(n)(n+1)(2n+1)/3 + 2n(n+1) + 4n
= 2n(4(n+1)(2n+1)/3 + (n+1) + 2)
= 2n((n+1)(8n+7)/3 + 2)
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int N = 1001, n = N / 2;
    int ans = 1 + 2 * n * (((n + 1) * (8 * n + 7) / 3) + 2);

    printf("%d\n", ans);
    return 0;
}