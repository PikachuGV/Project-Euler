/*
A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly, F, sits in the opposite corner. By travelling on the surfaces of the room the shortest "straight line" distance from S to F is 10 and the path is shown on the diagram.
However, there are up to three "shortest" path candidates for any given cuboid and the shortest route doesn't always have integer length.
It can be shown that there are exactly 2060 distinct cuboids, ignoring rotations, with integer dimensions, up to a maximum size of M by M by M, for which the shortest route has integer length when M = 100. This is the least value of M for which the number of solutions first exceeds two thousand; the number of solutions when M = 99 is 1975.
Find the least value of M such that the number of solutions first exceeds one million.
*/

/*
Analysis:

Let a,b,c be the dimensions of the cuboid. WLOG, a>=b>=c>0. Every triplet of a,b,c will produce a distinct cuboid.
Now let the faces be named using the dimensions. For example, the face spanned by dimensions a and b will be called ab.
For simplicity, we will make the face ab be the base of the cuboid, with side a facing us.

Notice there there are mainly 3 shortest ways to get from one corner to another:
    - via ab->ac
    - via ab->bc
    - via ac->bc

Reverse in directions (like bc->ac) doesnt change the distance travelled.
These are the shortest because when the cuboid is unfolded into a 2d plane, these faces can be connected side by side, meaning that the straight diagonal between the two faces will result int the shortest distance.

The distances are therefore as such:
-(𝑎+𝑐)^2+𝑏^2=𝑎^2+𝑏^2+𝑐^2+2𝑎𝑐 
-(𝑏+𝑐)^2+𝑎^2=𝑎^2+𝑏^2+𝑐^2+2𝑏𝑐
-(𝑎+𝑏)^2+𝑐^2=𝑎^2+𝑏^2+𝑐^2+2𝑎𝑏

Notice that the only difference between the 3 expressions is the product term. Notice that since a>=b>=c>0, we can say that ab>=ac AND ac>=bc. As such, ab>=ac>=bc. Hence:
(𝑎+𝑏)^2+𝑐^2≥(𝑎+𝑐)^2+𝑏^2≥(𝑏+𝑐)^2+𝑎^2

The shortest distance is thus (b+c)^2 + a^2. All we need to do is check whether this is a perfect square.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPerfectSq(int n) {
    int x = n>>1, y;
    for (int i = 0; i < 100; i++) {
        y = (x+(n/x))>>1;
        if (y == x) break;
        x=y;
    }

    return (x * x == n); 
}

const int N = 1000000;

int main() {
    int sq, n = 0;
    for (int a = 1; a < N; a++) {
        for (int b = 1; b <= a; b++) {
            for (int c = 1; c <= b; c++) {
                sq = (b+c)*(b+c) + a*a;
                if (isPerfectSq(sq)) {
                    n++;
                    if (n == N) break;
                }
            }
            if (n == N) break;
        }
        if (n == N) {
            printf("%d\n", a); break;
        }
    }

    
    return 0;
}