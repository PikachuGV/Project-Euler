/*
Q18: By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
3
7 4
2 4 6
8 5 9 3
That is, 3 + 7 + 4 + 9 = 23.
Find the maximum total from top to bottom of the triangle below:
75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define max(a, b) ((a > b) ? a : b)

struct node {
    struct node* left;
    struct node* right;
    int val;
    int maxresult;
    int index;
};

bool istriangular(int n) {
    return (bool)(sqrt(8 * n + 1) == (int)sqrt(8 * n + 1));
}

int triangularindex(int n) {
    return (sqrt(8 * n + 1) - 1) / 2;
}

int triangularnum(int n) {
    return n * (n + 1) / 2;
}

void initnodes(int* triangle, struct node** nodes, int rows) {
    int currrow, currrowindex;
    for (int i = 0; i < 120; i++) {
        if (istriangular(i)) {
            currrow = triangularindex(i);
            currrowindex = 0;
        }
        struct node* n = (struct node*)malloc(sizeof(struct node));
        n->maxresult = 0;
        n->val = triangle[i];
        n->index = i;

        if (currrowindex > 0) nodes[triangularnum(currrow - 1) + currrowindex - 1]->right = n;
        if (currrowindex < currrow) nodes[triangularnum(currrow - 1) + currrowindex]->left = n;
        
        if (currrow == rows - 1) {
            n->left = NULL; n->right = NULL;
        }

        nodes[i] = n;
        currrowindex++;
    }
}

int search(struct node* n) {
    if (n->left == NULL) return n->val;
    if (n->maxresult != 0) return n->maxresult;
    int total = n->val + max(search(n->left), search(n->right));
    n->maxresult = total;
    return total;
}

int main() {
    clock_t start = clock();
    int triangle[120] = {
        75, 95, 64, 17, 47, 82, 18, 35, 87, 10, 20, 04, 82, 47, 65, 19, 01, 23, 75, 03, 34, 88, 02, 77, 73, 07, 63, 67, 99, 65, 04, 28, 06, 16, 70, 92, 41, 41, 26, 56, 83, 40, 80, 70, 33, 41, 48, 72, 33, 47, 32, 37, 16, 94, 29, 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14, 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57, 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48, 63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31, 04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23
    };
    struct node** nodes = (struct node**)malloc(120 * sizeof(struct node*));

    initnodes(triangle, nodes, 15);

    struct node* n = nodes[0];
    printf("%d\n", search(n));
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n", time);
    return 0;
}