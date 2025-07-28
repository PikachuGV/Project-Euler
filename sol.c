/*
Each of the six faces on a cube has a different digit (0 to 9) written on it; the same is done to a second cube. By placing the two cubes side-by-side in different positions we can form a variety of 2-digit numbers.

For example, the square number 64 could be formed:

6 4

In fact, by carefully choosing the digits on both cubes it is possible to display all of the square numbers below one-hundred: 01, 04, 09, 16, 25, 36, 49, 64, and 81.

For example, one way this can be achieved is by placing {0, 5, 6, 7, 8, 9} on one cube and {1, 2, 3, 4, 8, 9} on the other cube.

However, for this problem we shall allow the 6 or 9 to be turned upside-down so that an arrangement like {0, 5, 6, 7, 8, 9} and {1, 2, 3, 4, 6, 7} allows for all nine square numbers to be displayed; otherwise it would be impossible to obtain 09.

In determining a distinct arrangement we are interested in the digits on each cube, not the order.

{1, 2, 3, 4, 5, 6} is equivalent to {3, 6, 4, 1, 2, 5}
{1, 2, 3, 4, 5, 6} is distinct from {1, 2, 3, 4, 5, 9}

But because we are allowing 6 and 9 to be reversed, the two distinct sets in the last example both represent the extended set {1, 2, 3, 4, 5, 6, 9} for the purpose of forming 2-digit numbers.

How many distinct arrangements of the two cubes allow for all of the square numbers to be displayed?
*/

/*
Each cube has a total of 10C6 = 210 distinct arrangements. So there are 210*210/2 = 22050 ways.
This is doable by brute force.
Notice 49 and 64 are the exact same combination since 6 can be flipped into a 9.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 10
#define R 6
#define NCR 210

int bitsset[1<<N] = {0};

void initbitset() {
    bitsset[0] = 0;
    for (int i = 0; i<(1<<N); i++) {
        bitsset[i] = (i & 1) + bitsset[i >> 1];
    }
}

int *genArrangements(int r, int n) {
    //Generate all arranges of r numbers in a range of N numbers.
    int *arr = calloc(NCR, sizeof(int)), idx = 0;
    for (int i = 0; i < (1<<n); i++) {
        if (bitsset[i] == r) {
            arr[idx] = i; idx++; 
        }
    }
    return arr;
}

int main() {
    initbitset();
    int *arrangements = genArrangements(R, N);
    
    int cube1, cube2, c=0;
    bool has01, has04, has09, has16, has25, has36, has49, has81;
    for (int i = 0; i < NCR; i++) {
        for (int j = i+1; j < NCR; j++) {
            cube1 = arrangements[i]; cube2 = arrangements[j];
            
            has01 = ((cube1 & 0x2) && (cube2 & 0x1)) || ((cube2 & 0x2) && (cube1 & 0x1));
            has04 = ((cube1 & 0x10) && (cube2 & 0x1)) || ((cube2 & 0x10) && (cube1 & 0x1));
            has09 = ((cube1 & 0x240) && (cube2 & 0x1)) || ((cube2 & 0x240) && (cube1 & 0x1));
            has16 = ((cube1 & 0x2) && (cube2 & 0x240)) || ((cube2 & 0x2) && (cube1 & 0x240));
            has25 = ((cube1 & 0x4) && (cube2 & 0x20)) || ((cube2 & 0x4) && (cube1 & 0x20));
            has36 = ((cube1 & 0x8) && (cube2 & 0x240)) || ((cube2 & 0x8) && (cube1 & 0x240));
            has49 = ((cube1 & 0x10) && (cube2 & 0x240)) || ((cube2 & 0x10) && (cube1 & 0x240));
            has81 = ((cube1 & 0x100) && (cube2 & 0x2)) || ((cube2 & 0x100) && (cube1 & 0x2));


            if (has01 && has04 && has09 && has16 && has25 && has36 && has49 && has81) {
                printf("%d, %d\n", cube1, cube2); c++;
            }
        }
    }

    printf("%d\n", c);
    return 0;
}