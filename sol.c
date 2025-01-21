/*
Q15: Starting in the top left corner of a 2 * 2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
How many such routes are there through a 20 * 20 grid?
*/

//I know the answer is just 40C20 but lets do it the programming way.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define LL long long int

LL moves(int m, int n, int x, int y, LL* table) {
    //m is the no of rows, n is the no of cols
    //x is the current coordinates. 0, 0 is starting. All coords are positive.

    if (x > m || y > n) return 0LL;
    if (x == m && y == n) return 1LL;

    if (!(x == 0 || y == 0) && table[(x - 1) * m + (y - 1)] != -1) {
        return table[(x - 1) * m + (y - 1)];
    }
    LL nmoves = moves(m, n, x + 1, y, table) + moves(m, n, x, y + 1, table);
    if (x != 0 && y != 0) table[(x - 1) * m + (y - 1)] = nmoves;
    return nmoves;
}

int main() {
    clock_t start = clock();
    int m = 20, n = 20;
    LL* table = malloc(m * n * sizeof(LL));
    memset(table, -1LL, sizeof(LL) * m * n);
    printf("%lld\n", moves(m, n, 0, 0, table));
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %lf\n", time);
    return 0;
}