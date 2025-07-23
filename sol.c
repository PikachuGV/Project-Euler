/*
A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers, {a1, a2, ..., ak} is called a product-sum number: N = a1 + a2 + ... + ak = a1 * a2 * ... * ak.
For example, 6 = 1 + 2 + 3 = 1 * 2 * 3.
For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number. The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 * 2 = 2 + 2
k=3: 6 = 1 * 2 * 3 = 1 + 2 + 3
k=4: 8 = 1 * 1 * 2 * 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 * 1 * 2 * 2 * 2 = 1 + 1 + 2 + 2 + 2k=6: 12 = 1 * 1 * 1 * 1 * 2 * 6 = 1 + 1 + 1 + 1 + 2 + 6
Hence for 2 <= k <= 6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted once in the sum.
In fact, as the complete set of minimal product-sum numbers for 2 <= k <= 12 is {4, 6, 8, 12, 15, 16}, the sum is 61.
What is the sum of all the minimal product-sum numbers for 2 <= k <= 12000?
*/


/*
It helps to look at the list of the first few product sum numbers

n           n-tuple sol         product/sum
2               2,2                 4
3              1,2,3                6
4             1,1,2,4               8
5            1,1,1,2,5              10
5            1,1,1,3,3              9
5            1,1,2,2,2              8
6           1,1,1,1,2,6             12
7          1,1,1,1,1,2,7            14
7          1,1,1,1,1,3,4            12
8         1,1,1,1,1,1,2,8           16
8         1,1,1,1,1,2,2,3           12
9        1,1,1,1,1,1,1,2,9          18
9        1,1,1,1,1,1,1,3,5          15
10      1,1,1,1,1,1,1,1,2,10        20
10      1,1,1,1,1,1,1,1,4,4         16
11     1,1,1,1,1,1,1,1,1,2,11       22
11     1,1,1,1,1,1,1,1,1,3,6        18
11     1,1,1,1,1,1,1,1,2,2,4        16
12    1,1,1,1,1,1,1,1,1,1,2,12      24
12    1,1,1,1,1,1,1,1,2,2,2,2       16

We can make a few observations here:

1. For every n, there is a tuple with n-2 1s, a 2, and n in the solution.
2. There exists a first n that contains m amount of N and n-m amount of 1s. One of the Ns then gets incremented in another solution set (with diff amounts of 1s) at a fixed interval for n
    For example, refer to n=5 sol set 1,1,2,2,2. At n=8, the last 2 gets incremented to form the sol set 1,1,1,1,2,2,3. As predicted with period of 3, at n=11, there is a sol set with 2,2,4 as the non 1s elements.
    Another example is n=5 sol set 1,1,1,3,3. At n=7, last 3 gets incremented to form sol set 1,1,1,1,1,3,4. As predicted with period of 2, last 3 gets incremented to form sol set 1,1,1,1,1,1,1,3,5.

We can denote this observation by the following conjecture:
    For any sol set {a1,a2,a3...an}, set m to be the number of 1s in the sol set. Assume sol set is arranged in sequential order such that a1=a2=...=am=1 and a(m+1)<=a(m+2)...<=an.
    We can trace this sol set to its "fundemental sol" by setting an=a(n-1) and m-=(an-a(n-1))(a(m+1)a(m+2)...a(n-1)-1)
    Every sol set has a fundemental sol, and this fundemental sol generates sol at a period of n=a(m+1)a(m+2)...a(n-1) - 1.

We can obviously see that every sol set has a fundemental sol, since we know two facts:
    1. All a are positive integers.
    2. m <= n-2. If m=n then it means that mn=1 which is only possible if m=n=1. If m=n-1 then m+an = an which means m=0 which means n=1.

This means that we can always reduce a sol set into its fundemental counterpart by decrementing an and m.

Now suppose we have a fundemental sol set with length n. There are m 1s in this fundemental sol set. If we were to increment an, since we know that m<=n-2, we know that there a(n-1) != 1.
So by incrementing an by 1, we are essentially incrementing the product by a(m+1)a(m+2)...a(n-1) (since a1=a2=...=am=1) and the sum by 1.
This means that the difference between the product and sum is now a(m+1)a(m+2)...a(n-1) - 1 (since a(m+1)>=a(m+2)>=...>=a(n-1)>1). Notice that appending 1s to the sol set ONLY affects the sum since anything multiplied by 1 is still the same number. 
Thus we only need to append a(m+1)a(m+2)...a(n-1)-1 1s to get the next sol set. The same logic applies when we continue to increment an. This in essence means that for this fundemental sol set, we will generate different set at intervals of a(m+1)a(m+2)...a(n-1)-1.


Back to the question. We need to find the set of minimial product-sum numbers from 2<=k<=12000.
We need to know what is the maximum length of non-1 elements possible in this range.
For n non-1 elements, the smallest product will be 2^n while the smallest sum will be 2n.
Difference between the product and sum is thus 2^n - 2n. Since this is an increasing function, increasing any element will increase the difference.
We want n+(2^n - 2n) <= 12000. This can be simplified to 2^n - n <= 12000.
We know that 2^13 < 12000 < 2^14. A quick check shows that 2^13 - 13 < 12000 < 2^14 -14
Thus n<=13.

The logic for this approach will be as such (1st draft, there are errors here):

MPS = array denoting the minimial product sums.
S = array denoting sol set (less the 1s)
For i=2 i<13 i++:
    fill S with i 2s. S[-2] = 1
    pointer = i-2
    while true
        S[i-2]++
        S[i-1]=S[i-2]
        while prod(S)-sum(S)+i>12000
            S[pointer]++, S[pointer+1...i-1]=S[pointer]
            pointer--
            if pointer < 0 break

        if pointer < 0 break

        period = prod(S)/S[-1]
        mps = prod(S)-sum(S)+i
        s = sum(S)
        while (mps <= 12000)
            MPS[mps] = min(s, MPS[mps])
            mps += period
            s++ 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define min(a,b) ((a>b) ? b : a)

int sum(int *arr, int l) {
    int s=0;
    for (int i = 0; i < l; i++) s += arr[i];
    return s;
}


int prod(int *arr, int l) {
    int p=1;
    for (int i = 0; i < l; i++) p *= arr[i];
    return p;
}

int max(int *arr, int l) {
    int maxx = 0;
    for (int i = 0; i < l; i++) {
        if (arr[i] > maxx) maxx=arr[i];
    }

    return maxx;
}


int main() {
    int *arr, p, period, P, S, mps;
    int MPS[12000 + 1]; for (int i = 0; i <= 12000; i++) MPS[i]=INT_MAX;

    for (int i = 2; i <= 13; i++) {
        arr = calloc(i, sizeof(int));
        for (int ii = 0; ii < i; ii++) arr[ii] = 2;
        arr[i-2] = 1; //This is in anticipation of incrementation in the while loop
        p = i-1; //Also in anticipation
        while (true) {
            arr[i-2]++;
            arr[i-1]=arr[i-2];

            //When this current fundemental sol set exceeds, we have to find a new one
            //This is done by going forwards in the list, incrementing each element once.
            //Each time we increment, every element after this element will be set equal to this element. If it still exceeds, we move forward once more
            //Repeats unitl either we dont exceed or we have moved past the head of list
            while (prod(arr,i)-sum(arr,i)+i>12000) {
                if (p<0)break;
                p--;
                arr[p]++;
                for (int ii=p+1; ii<i; ii++) arr[ii]=arr[p];
            }
            //If we moved past head of list it means that we have found all fundemental sols with i non-1 elements.
            if (p<0) break;

            //Now we reset p so that we can redo the same trick. For example:
            //2,3,10->2,4,4->3,3,3->continue->exceed at 3,3,100->3,4,4
            p=i-1;

            //Fundemental sol set has been generated.
            P = prod(arr, i); S = sum(arr, i);
            period = P / arr[i-1];
            mps = P-S+i;
            while (mps <= 12000) {
                MPS[mps] = min(P, MPS[mps]);
                mps += period-1; P += period;
            }
        }    
    }

    bool *seen = calloc(max(MPS+2, 12001-2)+1, sizeof(bool));
    int s = 0;
    for (int i = 2; i <= 12000; i++) {
        if (seen[MPS[i]] == false) s+=MPS[i];
        seen[MPS[i]] = true;
    }

    printf("%d\n", s);



    return 0;
}