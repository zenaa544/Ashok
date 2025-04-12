Problem statement
You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.

Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

For Example :
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.


  My Solution

bool subsetSumToK(int n, int k, vector<int> &arr) {
    // Write your code here.
 vector<vector<bool>>dp(n,vector<bool>(k+1,false));
    
    for(int i =0; i< n;i++)
         dp[i][0]=true; 
  
    if (arr[0] <= k)
        dp[0][arr[0]] = true;

    
    for(int i=1 ;i<n;i++){
        for(int j=1;j<=k;j++){
                          
             bool notTake= dp[i-1][j];
             bool take= false;
             if(j>=arr[i])
               take= dp[i-1][j-arr[i]];
             

             dp[i][j]= take||notTake;
        } 
    }   

    return dp[n-1][k]; 
   
}

GPT solution

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));

    // Base case: sum = 0 is always possible (empty subset)
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            bool notTake = dp[i - 1][j];
            bool take = false;

            if (j >= arr[i - 1])
                take = dp[i - 1][j - arr[i - 1]];

            dp[i][j] = take || notTake;
        }
    }

    return dp[n][k];
}










