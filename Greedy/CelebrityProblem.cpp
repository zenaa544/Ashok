Problem statement
There are ‘N’ people at a party. Each person has been assigned a unique id between 0 to 'N' - 1(both inclusive). A celebrity is a person who is known to everyone but does not know anyone at the party.

Given a helper function ‘knows(A, B)’, It will returns "true" if the person having id ‘A’ know the person having id ‘B’ in the party, "false" otherwise. Your task is to find out the celebrity at the party. Print the id of the celebrity, if there is no celebrity at the party then print -1.

Note:
1. The helper function ‘knows’ is already implemented for you.
2. ‘knows(A, B)’ returns "false", if A doesn't know B.
3. You should not implement helper function ‘knows’, or speculate about its implementation.
4. You should minimize the number of calls to function ‘knows(A, B)’.
5. There are at least 2 people at the party.
6. At most one celebrity will exist.


#include <bits/stdc++.h> 
/*
	This is signature of helper function 'knows'.
	You should not implement it, or speculate about its implementation.

	bool knows(int A, int B); 
	Function 'knows(A, B)' will returns "true" if the person having
	id 'A' know the person having id 'B' in the party, "false" otherwise.
*/

int findCelebrity(int n) {
 	// Write your code here.

	 int first=0;
	 int last=n-1;

	 while(first<last){

		 if(knows(first,last)==true)first++;
		 else if(knows(last,first)==true)last--;
		 else{
			 first++;
			 last--;
		 }
	 }

	 if(first>last)return -1;
	 else{
		 for(int i=0;i<n;i++){
			 if(i!=first && (knows(first,i) || !knows(i,first)))
			 	return -1;
		 }
	 }

	 return first;
}

=================================


  ✅ Key Properties of a Celebrity
Celebrity is known by everyone, and

Celebrity knows no one.

So, for a person C to be a celebrity:

For every i != C:
knows(C, i) == false and knows(i, C) == true

🧠 Optimal Approach: Two-Pointer Elimination
We can solve this in O(N) time and O(1) space by:

Finding a candidate celebrity using pairwise elimination.

Verifying the candidate.

int findCelebrity(int n) {
    // Step 1: Find the potential celebrity
    int candidate = 0;
    for (int i = 1; i < n; ++i) {
        if (knows(candidate, i)) {
            // candidate knows i, so candidate can't be celebrity
            candidate = i;
        }
        // else i can't be a celebrity, candidate stays
    }

    // Step 2: Verify candidate
    for (int i = 0; i < n; ++i) {
        if (i == candidate) continue;

        // Celebrity knows no one, and everyone knows celebrity
        if (knows(candidate, i) || !knows(i, candidate)) {
            return -1;
        }
    }

    return candidate;
}
