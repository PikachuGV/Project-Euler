/*
Su Doku (Japanese meaning number place) is the name given to a popular puzzle concept. Its origin is unclear, but credit must be attributed to Leonhard Euler who invented a similar, and much more difficult, puzzle idea called Latin Squares. The objective of Su Doku puzzles, however, is to replace the blanks (or zeros) in a 9 by 9 grid in such that each row, column, and 3 by 3 box contains each of the digits 1 to 9. Below is an example of a typical starting puzzle grid and its solution grid.


A well constructed Su Doku puzzle has a unique solution and can be solved by logic, although it may be necessary to employ "guess and test" methods in order to eliminate options (there is much contested opinion over this). The complexity of the search determines the difficulty of the puzzle; the example above is considered easy because it can be solved by straight forward direct deduction.
The 6K text file, sudoku.txt, contains fifty different Su Doku puzzles ranging in difficulty, but all with unique solutions (the first puzzle in the file is the example above).
By solving all fifty puzzles find the sum of the 3-digit numbers found in the top left corner of each solution grid; for example, 483 is the 3-digit number found in the top left corner of the solution grid above.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 50


bool solve(int rows[9], int cols[9], int squares[9], int grid[9][9], int x, int y) {
    if (y>=9) {
        x++; y=0;
    }
    if (x>=9) return true;

    if (grid[x][y]!=0) return solve(rows, cols, squares, grid, x, y+1);
    
    int r = rows[x], c = cols[y], s = squares[y/3 + 3*(x/3)];

    int avaliable = 0x1FF^(r|c|s), b;

    if (avaliable == 0) return false;

    for (int i = 1; i <= 9; i++) {
        b = (1 << (i-1));
        if ((avaliable & b) == 0) continue;

        rows[x] ^= b; cols[y] ^= b; squares[y/3 + 3*(x/3)] ^= b; grid[x][y] = i;
        if (solve(rows, cols, squares, grid, x, y+1)) return true;
        rows[x] ^= b; cols[y] ^= b; squares[y/3 + 3*(x/3)] ^= b;
    }

    grid[x][y] = 0; return false;
}




int main() {
    int squares[N][9] = {{0}};
    int row[N][9] = {{0}};
    int col[N][9] = {{0}};
    int grid[N][9][9] = {{{0}}};


    FILE *f = fopen("sudoku.txt","r");
    char buffer[255];
    int idx = -1, rowidx, d, b;
    while (fgets(buffer, 255, f)) {
        if (buffer[0] == 'G') {
            idx++; rowidx = 0; continue;
        }

        for (int i = 0; i < 9; i++) {
            d = buffer[i] - '0';
            if (d == 0) continue;
            b = 1<<(d-1);
            row[idx][rowidx] |= b;
            col[idx][i] |= b;
            squares[idx][i/3 + 3*(rowidx/3)] |= b;
            grid[idx][rowidx][i] = d;
        }
        rowidx++;
    }

    int sum = 0;

    for (int i = 0; i < N; i++) {
        if (solve(row[i], col[i], squares[i], grid[i], 0, 0) == false) exit(1010);

        sum += grid[i][0][0]*100 + grid[i][0][1]*10 + grid[i][0][2];
    }

    printf("%d", sum);

    return 0;
}