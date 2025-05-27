/*
Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.

    4
     3
    1 2 6
   5

Working clockwise, and starting from the group of three with the numerically lowest external node (4,3,2 in this example), each solution can be described uniquely. For example, the above solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.

It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight solutions in total.

9   4,2,3; 5,3,1; 6,1,2
9   4,3,2; 6,2,1; 5,1,3
10  2,3,5; 4,5,1; 6,1,3
10  2,5,3; 6,3,1; 4,1,5
11  1,4,6; 3,6,2; 5,2,4
11  1,6,4; 5,4,2; 3,2,6
12  1,5,6; 2,6,4; 3,4,5
12  1,6,5; 3,5,4; 2,4,6

By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon ring is 432621513.
Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit strings. What is the maximum 16-digit string for a "magic" 5-gon ring?
*/

/*
Some observations made while analysing the question:

The middle numbers (in the polygon) must sum up to d*s - n(n+1)/2 where n is the number of integers used and s is the magic sum.
For a d-sided polygon, the min sum will be d(d+1)/2 and the max will be d(2n-d+1)/2
Thus it seems that for our case:
    Middle numbers sum to 5*s - 55
    Min sum of middle numbers is 15
    Max sum of middle numbers is 40.

However, things get interesting when we consider the restriction of only finding a 16-digit string.

There are 15 integers used in the string. The integer 10 provides 2 digits.
As such, to get only 16 digits in the string, 10 must be only used once in the string.
This implies that 10 must lie in the outer edges and not in the polygon.

As such we can see that the max sum for our requirements is actually 9+8+7+6+5=35.
Hence 15<=5s-55<=35 ==> 14<=s<=18

Possible method to solve this question:
    1. Set one branch to always be the starting branch. Doesnt matter which branch is chosen; this magic 5-gon ring is rotationally symmetrical.
    
    2. We first try to start this branch with the largest digit avaliable: 9. Note that 10 is considered to be smaller as 1 in our scenario, since the first digit of 10 is a 1. Appending a 10 anywhere also forces the digit after it to be 0, smaller than any other possible digit that can be placed after 1.

    3. This branch has only 2 spots remaining. The branch sum now is 9, and we know that the range of possible magic sums is 14<=s<=18. Hence our remaining 2 numbers must sum up to a min of 5 and a max of 9. We will then start by choosing the next 2 numbers to be 8 and 1 (since 8 is the biggest). This brings our magic sum to 18.

    4. Now we move on to the next branch in clockwise order. This branch will contain a 1 from the starting branch, and hence the remaining 2 spots must add up to 17. However, we have already used 9 and 8 and hence we cannot possibly add up to 17.

    5. We hence backtrack and look at 7 to be the 2nd digit instead. This opens the possiblity of the 3rd digit to be either 2 or 1. If it were 2, then the magic sum is still 18 and the same problem will arise. If it were 1, then the magic sum is 17, and the remaining 2 spots on the next branch must add up to 16. Again, impossible.
    
    6. This guess and check method can continue until we have found a valid string. The first string found will be guranteed to be the maximum.

To implement it efficently, we can do it recursively for each of the 5 branches. An array representing the digit string and a bitarray representing the usage of each of the 10 numbers, and an integer represent the branch number can be passed as arguments.

In each recursion, loop through all bits in the bitarry. The first bit represents 10, second represents 9, so on so forth. If a bit is set to 1, it means that it has already been used. If not, we use it at the HEAD of the branch, or the first possible spot. This continues until we only have one avaliable spot left. Since we know the magic sum, we deduce the last spot via magic sum. If the number calculated is not avaliable, then we know that this combination in the branch does not work. So we restart from the most recently set node. When all options have been tested and none work, we return a false value.

Notice for every branch after the head branch, the middle node is a known value. This middle node is actually the last node of the previous branch. The final branch has its last node as a known value too
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a, b) ((a < b) ? a : b)

const int order[10] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};

bool search(int* string, int* branch, int branchNum, int used, int magicSum) {
    int m, u, b[3];
    for (int i = 9; i >= 0; i--) { //Start with 9 because 9 is considered to be biggest.
        memset(b, 0, sizeof(b));
        u = used;
        m = order[i];
        if ((branchNum > 0) && (string[0] > m)) continue;
        if ((u & (1<<(m-1))) != 0) continue; //Continue if we have used digit.

        branch[0] = m; u |= (1 << (m-1)); //First node of branch is always empty.

        if (u == ((1<<10) - 1)) {
            //All numbers have been used.
            if (branch[0] + branch[1] + branch[2] == magicSum) {
                string[branchNum * 3] = branch[0];
                string[branchNum * 3 + 1] = branch[1];
                string[branchNum * 3 + 2] = branch[2];
                return true;
            }
            return false;
        }

        if (branchNum == 0) {
            //Middle node is empty for starting branch.
            string[0] = m; 
            
            for (int n = 9; n > 0; n--) { //Notice we dont use the number 10 since 10 cannot be in the poylgon
                if ((u & (1<<(n-1))) != 0) continue;
                string[1] = n;
                branch[1] = n; u |= (1 << (n-1));
                for (int o = 9; o > 0; o--) {
                    magicSum = branch[0] + branch[1] + o;
                    if ((u & (1<<(o-1))) != 0) continue;
                    if ((magicSum < 14) || (magicSum > 18)) continue;
                    branch[2] = o;
                    u |= (1<<(o-1));
                    b[1] = branch[2];
                    if (search(string, b, branchNum + 1, u, magicSum)) {
                        string[branchNum * 3] = branch[0];
                        string[branchNum * 3 + 1] = branch[1];
                        string[branchNum * 3 + 2] = branch[2];
                        return true;
                    }
                    u &= ~(1<<(o-1));
                }
                u &= ~(1<<(n-1));
            }
        } else {
            branch[2] = magicSum - branch[0] - branch[1];
            if (branch[2] <= 0 || branch[2] > 9 || ((u&(1<<(branch[2]-1)))!=0)) continue;
            u |= (1<<(branch[2]-1));
            b[1] = branch[2];
            if (branchNum == 3) b[2] = string[1];
            if (search(string, b, branchNum + 1, u, magicSum)) {
                string[branchNum * 3] = branch[0];
                string[branchNum * 3 + 1] = branch[1];
                string[branchNum * 3 + 2] = branch[2];
                return true;
            };
            u &= ~(1<<(branch[2]-1));
        }
        u &= ~(1 << (m-1));
    }

    return false;
}

int main() {
    int string[15], branch[3];
    memset(string, 0, sizeof(string));
    search(string, branch, 0, 0, 0);
    for (int i = 0; i < 15; i++) printf("%d", string[i]);
    return 0;
}