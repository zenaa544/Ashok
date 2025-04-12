You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * 109.

 https://leetcode.com/problems/unique-paths-ii/description/

class Solution {
public:
int solveTab(int row,int col,vector<vector<int>>& grid){

        if(grid[0][0]==1)return 0;
        vector<vector<int>>dp(row+1,vector<int>(col+1,-1));
        //dp[0][0]=1;
        for(int i=0;i<=row;i++){
            for(int j=0;j<=col;j++){
             
             if(i==0 && j==0)
                    dp[i][j]=1;
             else{
                    if(grid[i][j]==1)
                        dp[i][j]=0;
                    else{
                        int up = (i > 0) ? dp[i - 1][j] : 0;
                        int left = (j > 0) ? dp[i][j - 1] : 0;
                        dp[i][j] = up + left;
                    }
                }
            }
        }
        return dp[row][col];
      

    }
    int solve(int rowI, int colI, vector<vector<int>>& dp, vector<vector<int>>& grid){

       if(rowI==0 && colI==0)return 1;
        
        if(rowI<0 || colI<0) return 0;

        if(rowI>=0 && colI>=0 && grid[rowI][colI]==1)return 0;
         
         if(dp[rowI][colI]!=-1) return dp[rowI][colI];

        dp[rowI][colI]= solve(rowI,colI-1,dp,grid)+ solve(rowI-1,colI,dp,grid);

        return dp[rowI][colI];


    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row=obstacleGrid.size()-1;
        int col=obstacleGrid[0].size()-1;
        //vector<vector<int>>dp(row+1,vector<int>(col+1,-1));
        // if(obstacleGrid[0][0]!=1)dp[0][0]=1;
        // else return 0;
        //return solve(row,col,dp,obstacleGrid);
        return solveTab(row,col,obstacleGrid);
    }
};
