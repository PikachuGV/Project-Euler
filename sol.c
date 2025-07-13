/*
In the game, Monopoly, the standard board is set up in the following way:

GO A1 CC1 A2 T1 R1 B1 CH1 B2 B3 JAIL
H2                              C1
T2                              U1
H1                              C2
CH3                             C3
R4                              R2
G3                              D1
CC3                             CC2
G2                              D2
G1                              D3
G2J F3 U2 F2 F1 R3 E3 E2 CH2 E1 FP

A player starts on the GO square and adds the scores on two 6-sided dice to determine the number of squares they advance in a clockwise direction. Without any further rules we would expect to visit each square with equal probability: 2.5%. However, landing on G2J (Go To Jail), CC (community chest), and CH (chance) changes this distribution.
In addition to G2J, and one card from each of CC and CH, that orders the player to go directly to jail, if a player rolls three consecutive doubles, they do not advance the result of their 3rd roll. Instead they proceed directly to jail.
At the beginning of the game, the CC and CH cards are shuffled. When a player lands on CC or CH they take a card from the top of the respective pile and, after following the instructions, it is returned to the bottom of the pile. There are sixteen cards in each pile, but for the purpose of this problem we are only concerned with cards that order a movement; any instruction not concerned with movement will be ignored and the player will remain on the CC/CH square.
Community Chest (2/16 cards):
Advance to GO
Go to JAIL

Chance (10/16 cards):
Advance to GO
Go to JAIL
Go to C1
Go to E3
Go to H2
Go to R1
Go to next R (railway company)
Go to next R
Go to next U (utility company)
Go back 3 squares.

The heart of this problem concerns the likelihood of visiting a particular square. That is, the probability of finishing at that square after a roll. For this reason it should be clear that, with the exception of G2J for which the probability of finishing on it is zero, the CH squares will have the lowest probabilities, as 5/8 request a movement to another square, and it is the final square that the player finishes at on each roll that we are interested in. We shall make no distinction between "Just Visiting" and being sent to JAIL, and we shall also ignore the rule about requiring a double to "get out of jail", assuming that they pay to get out on their next turn.
By starting at GO and numbering the squares sequentially from 00 to 39 we can concatenate these two-digit numbers to produce strings that correspond with sets of squares.
Statistically it can be shown that the three most popular squares, in order, are JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and GO (3.09%) = Square 00. So these three most popular squares can be listed with the six-digit modal string: 102400.
If, instead of using two 6-sided dice, two 4-sided dice are used, find the six-digit modal string.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define ITERATIONS 100000000
#define DICESIDES 4

typedef enum sqtype {
    NORMAL,
    GO,
    JAIL,
    CC,
    CH,
    G2J
} SQUARETYPE;

typedef enum chtype {
    CH_GO,
    CH_JAIL,
    CH_C1,
    CH_E3,
    CH_H2,
    CH_R1,
    CH_R,
    CH_U,
    CH_B,
    CH_OTHERS
} CHTYPE;

typedef enum cctype {
    CC_GO,
    CC_JAIL,
    CC_OTHERS
} CCTYPE;

typedef struct sq {
    SQUARETYPE sqtype;
    int visitCount;
    const char *name;
} SQUARE;

const char *names[40] = {
    "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3", 
    "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
    "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
    "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
};

CHTYPE chance[] = {
    CH_GO, CH_JAIL, CH_C1, CH_E3, 
    CH_H2, CH_R1, CH_R, CH_R, CH_U, CH_B, 
    CH_OTHERS, CH_OTHERS, CH_OTHERS, 
    CH_OTHERS, CH_OTHERS, CH_OTHERS
};

CCTYPE commchest[] = {
    CC_GO, CC_JAIL, CC_OTHERS, CC_OTHERS,
    CC_OTHERS, CC_OTHERS, CC_OTHERS,
    CC_OTHERS, CC_OTHERS, CC_OTHERS,
    CC_OTHERS, CC_OTHERS, CC_OTHERS,
    CC_OTHERS, CC_OTHERS, CC_OTHERS
};

SQUARE *board[40];

void initboard() {
    SQUARE *sq;
    for (int i = 0; i < 40; i++) {
        sq = malloc(sizeof(SQUARE));
        sq->visitCount = 0;
        sq->name = names[i];
        if (strcmp(sq->name, "GO") == 0) {
            sq->sqtype = GO;
        } else if (strcmp(sq->name, "JAIL") == 0) {
            sq->sqtype = JAIL;
        } else if (strncmp(sq->name, "CC", 2) == 0) {
            sq->sqtype = CC;
        } else if (strncmp(sq->name, "CH", 2) == 0) {
            sq->sqtype = CH;
        } else if (strcmp(sq->name, "G2J") == 0) {
            sq->sqtype = G2J;
        } else {
            sq->sqtype = NORMAL;
        }

        board[i] = sq;
    }
}

void shuffle() {
    for (int i = 16-1; i > 0; i--) {
        int j = rand() % (i+1);
        CCTYPE temp = commchest[i];
        commchest[i] = commchest[j];
        commchest[j] = temp;
    }

    for (int i = 16-1; i > 0; i--) {
        int j = rand() % (i+1);
        CHTYPE temp = chance[i];
        chance[i] = chance[j];
        chance[j] = temp;
    }
}

int rolldice(int n) {
    return (rand() % n) + 1;
}

int nextRail(int idx) {
    if (idx > 35) return 5;

    if (idx < 5) return 5;
    if (idx < 15) return 15;
    if (idx < 25) return 25;
    if (idx < 35) return 35; 
}

int cc(int idx) {
    CCTYPE card = commchest[0];
    for (int i = 0; i < 15; i++) {
        commchest[i] = commchest[i+1];
    }
    commchest[15] = card;

    switch (card) {
        case CC_GO:
            return 0;
        case CC_JAIL:
            return 10;
        case CC_OTHERS:
            return idx;
    }
}

int ch(int idx) {
    CHTYPE card = chance[0];
    for (int i = 0; i < 15; i++) {
        chance[i] = chance[i+1];
    }
    chance[15] = card;

    switch (card) {
        case CH_GO:
            return 0;
        case CH_JAIL:
            return 10;
        case CH_C1:
            return 11;
        case CH_E3:
            return 24;
        case CH_H2:
            return 39;
        case CH_R1:
            return 5;
        case CH_R:
            return nextRail(idx);
        case CH_U:
            return (idx > 12 && idx < 28) ? 12 : 28;
        case CH_B:
            return idx - 3;
        case CH_OTHERS:
            return idx;
    }
}

int compare(const void *a, const void *b) {
    SQUARE **squarea = (SQUARE **) a;
    SQUARE **squareb = (SQUARE **) b;
    return (*squareb)->visitCount - (*squarea)->visitCount;
}

int main() {
    srand(time(NULL));
    initboard(); shuffle(); 

    int dice1, dice2, idx = 0, doublecount = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        dice1 = rolldice(DICESIDES);
        dice2 = rolldice(DICESIDES);
        idx += dice1 + dice2;
        idx %= 40;

        doublecount = (dice1 == dice2) ? doublecount+1 : 0;

        if (doublecount == 3) {
            idx = 10; doublecount = 0;
        }

        switch (board[idx]->sqtype) {
            case NORMAL:
                break;
            case GO:
                break;
            case JAIL:
                break;
            case CC:
                idx = cc(idx);
                break;
            case CH:
                idx = ch(idx);
                break;
            case G2J:
                idx = 10;
                break;
        }

        board[idx]->visitCount++;
    }

    qsort(board, 40, sizeof(SQUARE*), compare);

    for (int i = 0; i < 40; i++) {
        printf("%s: %d visits. Percentage: %lf%% \n", board[i]->name, board[i]->visitCount, (double)board[i]->visitCount/ITERATIONS*100);
    }

    return 0;
}