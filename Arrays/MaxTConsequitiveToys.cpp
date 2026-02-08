Problem Statement – In a toy shop there are a number of toys presented with several various – priced toys in a specific order. 
You have a limited budget and would like to select the greatest number of consecutive toys that fit within the budget. 
Given prices of the toys and your budget, what is the maximum number of toys that can be purchased for your child?

Example :

prices=[1,4,5,3,2,1,6]
money=6
All subarrays that sum to less than or equal to 6 .

length 1: [1] [4] [5] [3] [2] [1] [6]
length 2: [1,4] [3,2] [2,1]
length 3: [3,2,1]
The longest of these or the maximum number of toys that can be purchased is 3.

Function description
Complete the function

getMaxToys in the editor below
getMaxToys has the following parameters:
int prices[n] : the prices of the various toys.
int money: the amount of money you can spend on toys
Returns :
Int the maximum number of toys you can purchase

Constraints :

1<=n<=10^5
1<=price[i]<=100
1<=money<=10^6
Sample case

Sample input :
7
1
4
5
3
2
1
6
6 
================================================
  “This is the classic Longest Subarray with Sum ≤ K problem. Since prices are positive and toys must be consecutive, 
the optimal solution is a sliding window with two pointers in O(n).”
=================================================
  int getMaxToys(int money, vector<int>& prices) {
    int left = 0;
    int sum = 0;
    int maxT = 0;

    for (int right = 0; right < prices.size(); right++) {
        sum += prices[right];

        while (sum > money) {
            sum -= prices[left];
            left++;
        }

        maxT = max(maxT, right - left + 1);
    }

    return maxT;
}

  
