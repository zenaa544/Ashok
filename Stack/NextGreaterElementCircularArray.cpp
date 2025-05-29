Problem statement
You are given a circular array 'a' of length 'n'.
A circular array is an array in which we consider the first element is next of the last element. That is, the next element of 'a[n - 1]' is 'a[0]'.
Find the Next Greater Element(NGE) for every element.
The Next Greater Element for an element 'x' is the first element on the right side of 'x' in the array, which is greater than 'x'.
If no greater elements exist to the right of 'x', consider the next greater element as -1.



Example:
Input: 'a' = [1, 5, 3, 4, 2]

Output: NGE = [5, -1, 4, 5, 5]

Explanation: For the given array,

- The next greater element for 1 is 5.

- There is no greater element for 5 on the right side. So we consider NGE as -1.

- The next greater element for 3 is 4.

- The next greater element for 4 is 5, when we consider the next elements as 4 -> 2 -> 1 -> 5.

- The next greater element for 2 is 5, when we consider the next elements as 2 -> 1 -> 5.

  
#include<bits/stdc++.h>
vector<int> nextGreaterElementII(vector<int>& nums) {
    // Write your code here.
        int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // stack stores indices

    for (int i = 2 * n - 1; i >= 0; --i) {
        int idx = i % n;

        while (!st.empty() && nums[st.top()] <= nums[idx]) {
            st.pop();
        }

        if (i < n) { // Only fill result during the first pass
            if (!st.empty()) {
                result[idx] = nums[st.top()];
            }
        }

        st.push(idx);
    }

    return result;
}
