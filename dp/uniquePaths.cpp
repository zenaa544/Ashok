/*
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 109.

https://leetcode.com/problems/unique-paths/description/
  */


class Solution {
public:
    int solve(int rowI, int colI, vector<vector<int>>& dp){

       if(rowI==0 && colI==0)return 1;
        
        if(rowI<0 || colI<0) return 0;
         
         if(dp[rowI][colI]!=-1) return dp[rowI][colI];

        dp[rowI][colI]= solve(rowI,colI-1,dp)+ solve(rowI-1,colI,dp);

        return dp[rowI][colI];


    }

    int solveTab(int row,int col){

      
        vector<vector<int>>dp(row+1,vector<int>(col+1,-1));
        //dp[0][0]=1;
        for(int i=0;i<=row;i++){
            for(int j=0;j<=col;j++){
             
             if(i==0 && j==0)
                    dp[i][j]=1;
             else{
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }
        return dp[row][col];
      

    }
//     int solveTab(int row, int col) {
//     vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
//     dp[0][0] = 1;  // Base case: start position

//     for (int i = 0; i <= row; i++) {
//         for (int j = 0; j <= col; j++) {
//             if (i == 0 && j == 0) continue; // already set
//             int up = (i > 0) ? dp[i - 1][j] : 0;
//             int left = (j > 0) ? dp[i][j - 1] : 0;
//             dp[i][j] = up + left;
//         }
//     }

//     return dp[row][col];
// }
    int uniquePaths(int m, int n) {
        
        int rowI=m-1;
        int colI=n-1;
        // vector<vector<int>> dp(m,vector<int>(n,-1));
        // dp[0][0]=1;
        // int uP= solve(rowI,colI,dp);

        // return uP;
        return solveTab(rowI,colI);
    }
};
