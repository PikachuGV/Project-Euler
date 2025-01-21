/*
Q24: A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

/*
Seems hard, but should be quite simple.

We first list the numbers in ascending order.
Aka 0123456789. This will be the first term.
Now keep all the digits fixed other than the last two. The possible permutations is just 89 and 98.
So the next term will be 0123456798
Now we revert to the original of 0123456789. Now keep all digits fixed other than the last 3.
Other than 789 and 798, the next permutation is to put 8 at the front (swap with 7). So now we have to consider the number of permutations of 79 which is 79 and 97.
So the next 2 terms will be 0123456879 and 0123456897.
Again, revert to the original of 0123456789 and keep all digits fixed other than the last 3.
The final permutation is to put 9 at the front of the 3 digits. Thus our next 3 terms are
0123456978, 0123456987.

Now if we look at the last 4 digits, we have to put 7 at the front and permutate the remaining 3 digits. This happens in 3 cycles (7 in front, 8 in front, 9 in front). Each of the 3 digits at the back have 3! = 6 permutations. So we have 6 * 3 = 18 permutations.

So in psuedocode:
perms = 1
digits = 1
cycle = 0
for 2 <= digits <= 10 {
    for 0<= j <digits - 1 {
        cycle++
        perm += (digits - 1)!
        if (perm >= 1000000), break
    }
}

digit = 10 - digits
swap(digit, digit + cycle)
get list with the last (digits - 1) digits
repeat with list and permslimit = (digits - 1)! - (perms - 1000000)
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void swap(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int partition(char* nums, int low, int high) {
    char pivot = nums[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (nums[j] < pivot) {
            i++; swap(&nums[i], &nums[j]);
        }

    }
    swap(&nums[i + 1], &nums[high]);
    return i + 1;
}

void sort(char* nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);

        sort(nums, low, pi - 1);
        sort(nums, pi + 1, high);
    } 
     
}

void lexicographic(char* nums, int len, int limit) {
    sort(nums, 0, len - 1);
    if (len == 1 || limit == 1) {
        return;
    }
    int perms = 1, digits = 2, cycle = 0, out = 0;
    for (digits = 2; digits <= len; digits++) {
        cycle = 0;
        for (int j = 0; j < digits - 1; j++) {
            cycle++;
            perms += factorial(digits - 1);
            if (perms >= limit) {
                out = 1; break;
            }
        }
        if (out == 1) break;
    }

    swap(&nums[len - digits], &nums[len - digits + cycle]);

    lexicographic(&nums[len - (digits - 1)], digits - 1, factorial(digits - 1) - (perms - limit));
}

int main() {
    char num[] = "0123456789";
    lexicographic(num, strlen(num), 1000000);
    printf("%s\n", num);
    return 0;
}