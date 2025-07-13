/*
The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column and finishing in any cell in the right column, and only moving up, down, and right, is indicated in red and bold; the sum is equal to 994.

131 673 234 103 18
201 96  342 965 150
630 803 746 422 111
537 699 497 121 956
805 732 524 37  331

Find the minimal path sum from the top left to the bottom right by only moving right and down in matrix.txt, a 31K text file containing an 80 by 80 matrix.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a,b) ((a < b) ? a : b)

typedef enum {
    UP,
    DOWN,
    NONE
} VDIR;

typedef struct node {    
    int val;
    int minvalup, minvaldown, minvalright;
} NODE;


#define N 80
NODE *matrix[N][N];


int search(int i, int j, VDIR vdir) {
    NODE *n = matrix[i][j];
    int eval = INT_MAX;

    if (j == N-1) {
        return n->val;
    }

    if (vdir != DOWN && n->minvalup != INT_MAX && n->minvalright != INT_MAX) {
        //n->minvalup = min(search(i-1,j,UP) + n->val, n->minvalup);
        eval = min(n->minvalup,eval);
        eval = min(eval,n->minvalright);
        if (vdir == NONE && n->minvaldown != INT_MAX && i < N-1) {
            eval = min(eval,n->minvaldown);
            return eval;
        } else if (vdir != NONE) return eval;
    }

    if (vdir != UP && n->minvaldown != INT_MAX && n->minvalright != INT_MAX) {
        //n->minvaldown = min(search(i+1,j,DOWN) + n->val, n->minvaldown);
        eval = min(n->minvaldown,eval);
        eval = min(eval,n->minvalright);
        if (vdir == NONE && n->minvalup != INT_MAX && i > 0) {
            eval = min(eval,n->minvalup);
            return eval;
        } else if (vdir != NONE) return eval;
    }

    if (n->minvalright == INT_MAX && j < N-1) n->minvalright = search(i,j+1,NONE) + n->val;
    if (n->minvaldown == INT_MAX && i < N-1 && vdir != UP) n->minvaldown = search(i+1,j,DOWN) + n->val;
    if (n->minvalup == INT_MAX && i > 0 && vdir != DOWN) n->minvalup = search(i-1,j,UP) + n->val;

    if (vdir == UP) {
        eval = min(n->minvalright, n->minvalup);
    } else if (vdir == DOWN) {
        eval = min(n->minvaldown, n->minvalright);
    } else {
        eval = min(n->minvaldown, min(n->minvalright, n->minvalup));
    }

    return eval;
}


int main() {
    FILE *f = fopen("matrix.txt", "r");
    char buffer[1023], *token;
    NODE *n;

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) matrix[i][j] = malloc(sizeof(NODE));
    for (int i = 0; i < N; i++) {
        fgets(buffer, 1023, f);
        token = strtok(buffer, ",");
        for (int j = 0; j < N; j++) {
            n = matrix[i][j];
            n->val = atoi(token);
            n->minvalup = INT_MAX;
            n->minvaldown = INT_MAX;
            n->minvalright = INT_MAX;
            token = strtok(NULL, ",");
        }
    }

    int eval = INT_MAX;
    search(0,0,NONE);
    
    for (int i = 0; i < N; i++) {
        eval = min(eval, matrix[i][0]->minvalright);
    }

    printf("%d", eval);

    return 0;
}