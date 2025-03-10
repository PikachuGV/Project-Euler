/*
The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
*/

/*
If we know all possible n-primes set for a certain n, then we can deduce all possible (n+1)-prime set by testing each prime concatenated with every prime in the set.

We can solve this qn using a bottom up approach. We start with only a 2-prime set, and when we find the first possible set, we use this set to generate the 3-prime set. We continue this until we reach the 5-prime set. When we find a possible 5-prime set, we save the sum. Now for every next set that we check, if the sum already exceeds the saved sum, we just break and go on to the next 2-prime set.



Note that if a number is divisible by 3 the sum of its digits is also divisble by 3. In fact every number is congruent to its sum of digits mod 3
This gives us a very big insight: for every pair in the set, sum of both primes must not be 0 mod 3.
There are only 3 options for mod 3: 0 1 2.
So there are 3*3 = 9 possible combinations:
0+0=0
0+1=1
0+2=2
1+0=0
1+1=2
1+2=3=0
2+0=2
2+1=3
2+2=4=1

Since order doesnt matter, then we have only have 6 possibilities
0+0=0
0+1=1
0+2=2
1+1=2
1+2=0
2+2=1

Since we are dealing with primes, there can only be a maximimum of 1 prime being congrurent to 0 mod 3 (aka 3).
This leaves with the rest of the primes being either 1 mod3 or 2mod3.
But if we have both 1mod3 and 2mod3 in the set, then there will be a pair consiting of one prime being 1mod3 and the other being 2mod3. This will lead to the the concat of the primes being 0 mod 3.
Thus we can deduce that for a n-primes set, all primes in the set (with the exception of 3) are either all 1 mod 3 or all 2 mod 3.


*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

bool isPrime(int n) {
    if ((n & 1) == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if ((n % i) == 0) return false;
    }
    return true;
}

bool isConcatPrimePair(int a, int b) {
    char A[10], B[10];
    sprintf(A, "%d", a); sprintf(B, "%d", b);
    char *concat = calloc(strlen(A) + strlen(B) + 1, sizeof(char));
    strcat(concat, A); strcat(concat, B);
    if (!isPrime(atoi(concat))) return false;
    memset(concat, '\0', (strlen(A) + strlen(B) + 1) * sizeof(char));
    strcat(concat, B); strcat(concat, A);
    if (!isPrime(atoi(concat))) return false;

    return true;
}

int sieve(int start, int end, int **allprimes) {
    bool primes[end - start + 1];
    int c = end - start + 1, s;
    memset(primes, true, sizeof(primes));

    //i represents the multiple that we are sieving out now. We only need to sieve until i = sqrt(end) since any number above sqrt(end) is either a prime or a multiple of some number below sqrt(end).
    for (int i = 2; i * i <= end; i++) {
        if (i > start && !primes[i - start]) continue;
        if (i * i < start) {
            //We set the start multiple to be start if start is already a multiple of i. Else we find the next multiple of i greater than start.
            s = (start % i == 0) ? start : (start / i + 1) * i;
        } else {
            //If i * i >= start then we have to start from i * i directly. 
            s = i * i;
        }
        //This loops through all multiples of i from start bound to end bound
        for (int j = s; j <= end; j += i) {
            if (primes[j - start]) c--;
            primes[j - start] = false;
        }
    }

    *allprimes = malloc(c * sizeof(int));

    int index = 0;
    for (int i = start; i < end; i++) {
        if (primes[i - start]) {
            (*allprimes)[index] = i; index++;
        }
    }

    return c;
}

int totalsum(int *list, int len) {
    int s = 0;
    for (int i = 0; i < len; i++) s += list[i];
    return s; 
}

int search(int target, int *primes, int c, int **list, int len, int minsum) {
    /*
    When this function is first called, list contains only 2 primes. (aka len is 2)
    Target is the target length of set that we want. So if we are trying to find a 5-prime set, then target=5.
    Primes and c are the list of primes and number of primes in said list respectively. Gotten from the sieve.
    Minsum is passed to each recursive call so that we know when to abandon the search.
    */


    int sum = totalsum(*list, len); //Finds the total sum of our current prime set.
    
    //If we have reached the target length, then we return the sum of the set as that is the value we want. Could also return minsum (if sum is greater) but Im too lazy.
    if (target == len) return sum; 

    //Looping through all the primes in my sieve.
    for (int i = 0; i < c; i++) {
        //Result of my analysis. We know that the second prime in the list is 100% not 3, so all the primes that we find from now onwards must be congruent to this prime in mod 3.
        if ((primes[i] % 3) != ((*list)[1] % 3)) continue;

        //This is where the abandoning of searches comes in. If our new sum is greater then the minsum, there is no need to continue checking this branch of primes since we want to minimise the sum, and all primes afterwards will be increasing.
        if (sum + primes[i] > minsum) break;

        //Loop through the set of primes.
        for (int j = 0; j < len; j++) {
            //Should there be a pair that when concatenated becomes composite, we abandon this search.
            if (!isConcatPrimePair((*list)[j], primes[i])) break;

            //Simple check to know that we reached the end of the loop, therefore this prime can be concatenated with all primes in the set.
            if (j == len - 1) {
                //Appends prime into list.
                len++; (*list)[len - 1] = primes[i];

                //Now we search with the current set to get the min possible sum. Note the change in the prime list and c, this is to ensure that we have no repeated primes (since we are only looking at increasing primes here.)
                sum = search(target, primes + i + 1, c - i - 1, list, len, minsum);
                if (sum < minsum) {
                    minsum = sum;
                    for (int i = 0; i < len; i++) printf("%d ", (*list)[i]);
                    printf("%d\n", minsum);
                }
                //Reset the list to its original.
                len--; (*list)[len - 1] = 0;
            }
        }
    }
    return minsum;
}

int main() {
    double start = get_time();
    int *primes, c, minsum, s, *list, N = 5;
    c = sieve(2, 10000, &primes);
    list = calloc(N, sizeof(int));
    minsum = INT_MAX;

    bool done = false;
    for (int i = 0; i < c; i++) {
        for (int j = i + 1; j < c; j++) {
            if (primes[i] + primes[j] > minsum) {
                done = true; break;
            };

            if ((primes[i] != 3) && ((primes[i] % 3) != (primes[j] % 3))) continue;

            if (isConcatPrimePair(primes[i], primes[j])) {
                list[0] = primes[i]; list[1] = primes[j];
                s = search(N, primes + j + 1, c - j - 1, &list, 2, minsum);
                if (s < minsum) minsum = s;
            }
        }
        if (done) break;
    }

    double end = get_time();

    printf("%d\n", minsum);

    printf("Time taken: %lf\n", end - start);
    
    return 0;
}