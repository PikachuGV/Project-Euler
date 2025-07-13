/*
In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by moving left, right, up, and down, is indicated in bold red and is equal to 2297.

131 673 234 103 18
201 96  342 965 150
630 803 746 422 111
537 699 497 121 956
805 732 524 37  331

Find the minimal path sum from the top left to the bottom right by moving left, right, up, and down in matrix.txt, a 31K text file containing an 80 by 80 matrix.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a,b) ((a < b) ? a : b)

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} VDIR;

typedef struct node {    
    int val;
    int row;
    int col;
    struct node *left;
    struct node *right;
    struct node *up;
    struct node *down;
    bool visited;
} NODE;


#define N 80
NODE *matrix[N][N];

NODE *mindistnode(int distances[N][N]) {
    NODE *min = NULL; int mindist = INT_MAX;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        if (distances[i][j] < mindist && matrix[i][j]->visited == false) {
            min = matrix[i][j]; mindist = distances[i][j];
        } 
    }

    return min;
}


int dijkstra() {
    int distances[N][N];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) distances[i][j] = INT_MAX;
    distances[0][0] = 0;
    int c = 0, d;
    NODE *u, *v;
    while (c < N*N) {
        u = mindistnode(distances); 
        //printf("%d\n", u->val);
        u->visited = true;
        c++;

        if (u->left != NULL) {
            d = distances[u->row][u->col] + u->left->val;
            if (d < distances[u->left->row][u->left->col]) {
                distances[u->left->row][u->left->col] = d;
            }
        }
        if (u->right != NULL) {
            d = distances[u->row][u->col] + u->right->val;
            if (d < distances[u->right->row][u->right->col]) {
                distances[u->right->row][u->right->col] = d;
            }
        }
        if (u->up != NULL) {
            d = distances[u->row][u->col] + u->up->val;
            if (d < distances[u->up->row][u->up->col]) {
                distances[u->up->row][u->up->col] = d;
            }
        }
        if (u->down != NULL) {
            d = distances[u->row][u->col] + u->down->val;
            if (d < distances[u->down->row][u->down->col]) {
                distances[u->down->row][u->down->col] = d;
            }
        }
        
    }

    return distances[N-1][N-1];
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
            n->row = i; n->col = j;
            n->val = atoi(token);
            n->up = (i > 0) ? matrix[i-1][j] : NULL;
            n->down = (i < N-1) ? matrix[i+1][j] : NULL;
            n->left = (j > 0) ? matrix[i][j-1] : NULL;
            n->right = (j < N-1) ? matrix[i][j+1] : NULL;
            n->visited = false;
            token = strtok(NULL, ",");
        }
    }
    printf("%d", dijkstra()+matrix[0][0]->val);

    return 0;
}