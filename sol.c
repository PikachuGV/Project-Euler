/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
    3
   7 4
  2 4 6
 8 5 9 3
That is, 3 + 7 + 4 + 9 = 23.
Find the maximum total from top to bottom in triangle.txt, a 15K text file containing a triangle with one-hundred rows.
NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this problem, as there are 2^99 altogether! If you could check one trillion (10^12) routes every second it would take over twenty billion years to check them all. There is an efficient algorithm to solve it. ;o)
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
    for (int i = 0; i < triangularnum(rows); i++) {
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
    int triangle[5050];
    
    FILE *f = fopen("triangle.txt", "r");
    char buffer[1000], *token;
    for (int i = 1; i <= 100; i++) {
        fgets(buffer, 1000, f);
        token = strtok(buffer, " ");
        for (int j = 1; j <= i; j++) {
            triangle[(i*(i - 1))/2 + j - 1] = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    
    fclose(f);

    struct node** nodes = malloc(5050 * sizeof(struct node*));
    initnodes(triangle, nodes, 100);

    struct node* n = nodes[0];

    printf("%d\n", search(n));

    return 0;
}