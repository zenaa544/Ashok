/*#########
     Memoization
  ########*/


/*
1. Greedy approach will give worng solution if we choose the max point task from 0th day and try to build, because point for the same task on
next day might increae.

2. We need all possible combinations 

lets start on 0th day and pick any task and following days we pick only tasks that was not picked the previous day.

3- recurence will happen from 0th day to following days till n-1 th day.
*/


#include <iostream>
#include <vector>
#include <algorithm>
int solve(vector<vector<int>> &points, int task, int day, int n,vector<vector<int>> &dp) {
    if (day == n) {
        return 0;  // No points can be gained after the last day.
    }
    if(dp[day][task]!=-1)
        return dp[day][task];
    int maxToday = 0;

    for (int i = 0; i < 3; i++) {
        if (i != task) {  // Ensure no same activity on consecutive days
            maxToday = max(maxToday, points[day][i] + solve(points, i, day + 1, n,dp));
        }
    }
    dp[day][task]=maxToday;
    return dp[day][task];
}
int ninjaTraining(int n, vector<vector<int>> &points)
{
    // Write your code here.
     int maxPoints=0;
     int pointsGained =0;
     vector<vector<int>> dp(n,vector<int>(3,-1));
    for(int task=0; task<3;task++){
       
       pointsGained=solve(points,task,0,n,dp);
       maxPoints=max(pointsGained,maxPoints);

    }
    return maxPoints;
}


/**********
Tabulation
***********/

int ninjaTraining(int n, vector<vector<int>> &points) {
    vector<vector<int>> dp(n, vector<int>(3, 0)); // DP table to store max points

    // Base Case: First day's points
    dp[0][0] = points[0][0]; // Task 0 on day 0
    dp[0][1] = points[0][1]; // Task 1 on day 0
    dp[0][2] = points[0][2]; // Task 2 on day 0

    // Fill DP table for subsequent days
    for (int day = 1; day < n; day++) {
        for (int task = 0; task < 3; task++) {
            // Maximum points if task is chosen on 'day', ensuring different task on 'day-1'
            dp[day][task] = points[day][task] +
                            max(dp[day - 1][(task + 1) % 3], dp[day - 1][(task + 2) % 3]);
        }
    }

    // The maximum points on the last day
    return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}

int main() {
    vector<vector<int>> points = {
        {1, 2, 5},
        {3, 1, 1},
        {3, 3, 3}
    };

    cout << "Max Points: " << ninjaTraining(points.size(), points) << endl;
    return 0;
}
