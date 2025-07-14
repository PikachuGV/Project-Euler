/*
By counting carefully it can be seen that a rectangular grid measuring 2 by 3 contains eighteen rectangles:

Although there exists no rectangular grid that contains exactly two million rectangles, find the area of the grid with the nearest solution.
*/

/*
Consider m by n (row, col) grid.

There are clearly mn 1 by 1 rectangles contained in the grid.
For 2 by 1 rectangles, we can start from the top row to the m-1 row, so there are (m-1)n 2 by 1 rectangles.
Similiarly, there are (m-2)n 3 by 1 rectangles.
Thus, for k by 1 rectangles where 1<=k<=m, there are (m-k+1)n such rectangles.

Now if we consider a 1 by 2 rectangle, we can similiarly start from the first col to the n-1 col. Thus there are m(n-1) of such rectangles.
Consider a 2 by 2 rectangle now. As mentioned, we start from the first col to the n-1 col. But since the rectangle takes up 2 rows too, then we can also start from first row to m-1 row. Hence there are (m-1)(n-1) such rectangles.

Putting it all together, for x by y rectangles where 1<=x<=m and 1<=y<=n, there are (m-x+1)(n-y+1) such rectangles.

This means that in total, there are 
(sum x from 1 to m)(sum y from 1 to n) (m-x+1)(n-y+1)
= (sum x from 1 to m (m-x+1)) (sum y from 1 to n (n-y+1))
= (m(m+1)-(0.5m(m+1)))(n(n+1)-(0.5n(n+1)))
= 0.25m(m+1)n(n+1)

Lets fix n. Then if we want 0.25m(m+1)n(n+1) = k, m(m+1)=4k/(n(n+1));
Thus m^2 + m - 4k/(n(n+1)) = 0
m = (-1 + sqrt(1+(16k/n(n+1))))/2 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define N 2000000

int main() {
    int mindiff = INT_MAX, minm = INT_MAX;
    double n = 1.0, minn;
    int m, val;
    while (n < minm) {
        m = floor((-1.0 + sqrt(1.0+(16.0*N/(n*(n+1.0)))))/2.0);
        if (m <= 0) {n++; continue;}
        val = (m*(m+1)*(int)n*(int)(n+1))/4;
        if (abs(val - N) < mindiff) {
            mindiff = abs(val - N);
            minm = m;
            minn = n;
        }

        val = ((m+1)*(m+2)*(int)n*(int)(n+1))/4;
        if (abs(val - N) < mindiff) {
            mindiff = abs(val - N);
            minm = m+1;
            minn = n;
        }
        n++;
    }

    printf("%d, %lf, %lf\n", minm, minn, minm*minn);
    return 0;
}