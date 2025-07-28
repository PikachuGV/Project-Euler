/*
The points P(x1, y1) and Q(x2, y2) are plotted at integer co-ordinates and are joined to the origin, O(0,0), to form triangle OPQ.

There are exactly fourteen triangles containing a right angle that can be formed when each co-ordinate lies between 0 and 2 inclusive; that is, 0 <= x1, y1, x2, y2 <= 2.

Given that 0 <= x1, y1, x2, y2 <= 50, how many right triangles can be formed?
*/

/*
One of the vertices MUST be on the origin.

Notice it is trival to consider the triangles that have a horizontal and vertical line, where the hypotenuse passes through the origin. We can actually calculate the number of such triangles easily.
For 0<=x,y<=N, there are N possible x (and y) coordinates on the axis. 
If we set the x coordinate first, then we can see that there are N choices for y. Similiar logic follows if we set y first. So there are 2N^2 triangles.

However, there are also triangles with the horizontal and vertical line where the origin is where the right angle is located. In this case, when we fix one of the coordinates, the other also has N choices to choose from. It does not matter whether we fix x or y first because they will lead to the same triangles formed. Hence there are N^2 triangles.

In total, there are 3N^2 triangles with horizontal and vertical edges.

Now the hard part is triangles that have a right angle via 2 diagonal lines. In that case the product of the gradient of the lines is -1.
We have to check all 1<=x,y<=N.
Let the coordinate be X,Y. Now the gradient of this edge from origin will be Y/X. As such the gradient of the other edge must be -X/Y.

Since it must also pass through coordinate X,Y, then we can see that the eqn of the line is y-Y = -X/Y * (x-X) -> y = -X/Y * (x-X) + Y
Expanding, we thus now have
Xx + Yy = Y^2 + X^2

Now this can be treated as a Diophantine Equation of the form ax+by=c, where a,b,c are all integers. There is a theorem relating to this type of equation, which we will use without proof.

This Diophantine equation has a solution (where x and y are integers) if and only if c is a multiple of the greatest common divisor of a and b. Moreover, if (x, y) is a solution, then the other solutions have the form (x + kv, y − ku), where k is an arbitrary integer, and u and v are the quotients of a and b (respectively) by the greatest common divisor of a and b.

We can clearly see that Y^2 + X^2 will always be a multiple of gcd(X,Y). So there must exist solutions.
We know that X,Y is obviously a solution. This means that all other solutions will be of the form (X+kv, Y-ku).
Now we know 0<=x,y<=N. Thus we can say that
-X <= kv <= N-X AND Y-N <= ku <= Y

==> -X/v <= k <= (N-X)/v AND (Y-N)/u <= k <= Y/u

Thus max(-X/v, (Y-N)/u) <= k <= min((N-X)/v, Y/u).
The number of such k is thus min((N-X)/v, Y/u) - max(-X/v, (Y-N)/u)
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 50

#define max(a,b) ((a>b) ? a : b)
#define min(a,b) ((a<b) ? a : b)

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    int total = 3*N*N, v, u, d;
    for (int X = 1; X <= N; X++) {
        for (int Y = 1; Y <= N; Y++) {
            d = gcd(X, Y);
            u = X/d; v = Y/d;
            total += min((N-X)/v, Y/u) - max(-X/v, (Y-N)/u);
        }
    }
    printf("%d", total);
    return 0;
}