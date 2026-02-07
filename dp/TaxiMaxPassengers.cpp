Problem Statement -: A taxi can take multiple passengers to the railway station at the same time.On the way back to the starting point,the taxi driver may pick up additional passengers for his next trip to the airport.A map of passenger location has been created,represented as a square matrix.
The Matrix is filled with cells,and each cell will have an initial value as follows:
* A value greater than or equal to zero represents a path.
* A value equal to 1 represents a passenger.
* A value equal to -1 represents an obstruction.
The rules of motion of taxi are as follows:
* The Taxi driver starts at (0,0) and the railway station is at (n-1,n-1).Movement towards the railway station is right or down,through valid path cells.
* After reaching (n-1,n-1) the taxi driver travels back to (0,0) by travelling left or up through valid path cells.
* When passing through a path cell containing a passenger,the passenger is picked up.once the rider is picked up the cell becomes an empty path cell. 
* If there is no valid path between (0,0) and (n-1,n-1),then no passenger can be picked.
* The goal is to collect as many passengers as possible so that the driver can maximize his earnings.
For example consider the following grid,
           0      1
          -1     0
Start at top left corner.Move right one collecting a passenger. Move down one to the destination.Cell (1,0) is blocked,So the return path is the reverse of the path to the airport.All Paths have been explored and one passenger is collected.
 
Returns:
Int : maximum number of passengers that can be collected.
 
Sample Input 0
4  -> size n = 4
4 -> size m = 4
0 0 0 1 -> mat
1 0 0 0
0 0 0 0
0 0 0 0
Output 0
2
Explanation 0
The driver can contain a maximum of 2 passengers by taking the following path (0,0) → (0,1) → (0,2) → (0,3) → (1,3) → (2,3) → (3,3) → (3,2) → (3,1) → (3,0) → (2,0) → (1,0)  → (0,0)

Sample Input 1
 STD IN                  Function 
————              ————-
   3     →  size  n=3
   3    →  size m=3
   0 1 -1 → mat 
   1 0 -1
   1 1 1
Sample Output 1
5
Explanation 1
The driver can contain a maximum of 5 passengers by taking the following path (0,0) → (0,1) → (1,1) → (2,1) → (2,2) → (2,1) → (2,0) → (1,0) → (0,0) c++ solution with explanation
=============================================================================


Cherry Pickup

Grid paths with obstacles

Game DP

Minimax

Graph longest path

DAG DP
================================================================================
// TOP-DOWN (Memoization)

// dp[r1][c1][r2] = maximum passengers that can be collected
// from CURRENT positions till the END,
// when:
//   Taxi1 is at (r1, c1)
//   Taxi2 is at (r2, c2)
//   and c2 = r1 + c1 - r2


1. Top-Down 3D DP (Memoization)
State meaning (most important)

dp[r1][c1][r2] = maximum passengers that can still be collected from now till the destination,
when:

Taxi1 is currently at (r1, c1)

Taxi2 is currently at (r2, c2)

both have taken the same number of steps

and c2 = r1 + c1 - r2

So this DP answers:

“From this state, what is the best future outcome?”

int dp[55][55][55];
int n;
vector<vector<int>> grid;

int solve(int r1, int c1, int r2) {
    int c2 = r1 + c1 - r2; // both taxis have taken same number of steps

    // Invalid state: out of grid
    if (r1 >= n || c1 >= n || r2 >= n || c2 >= n)
        return -1e9;

    // Invalid state: any taxi hits an obstacle
    if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
        return -1e9;

    // Base case:
    // both taxis reached destination
    // only one cell left to count
    if (r1 == n-1 && c1 == n-1)
        return grid[r1][c1];

    // If already computed, return stored result
    int &res = dp[r1][c1][r2];
    if (res != -1) return res;

    // Try all 4 possible future move combinations
    int bestFuture = max({
        solve(r1+1, c1,   r2+1), // both go down
        solve(r1,   c1+1, r2),   // both go right
        solve(r1+1, c1,   r2),   // taxi1 down, taxi2 right
        solve(r1,   c1+1, r2+1)  // taxi1 right, taxi2 down
    });

    // Passengers collected at current positions
    int current = 0;
    if (r1 == r2 && c1 == c2)
        current = grid[r1][c1];               // same cell, count once
    else
        current

int main() {
    vector<vector<int>> grid = {
        {0,0,0,1},
        {1,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    n = grid.size();
    memset(dp, -1, sizeof(dp));

    int ans = solve(0,0,0, grid);
    cout << max(0, ans) << endl;
}
==========================================


2. Bottom-Up 3D DP (Tabulation)
State meaning

dp[r1][c1][r2] = maximum passengers collected so far,
while reaching:

Taxi1 at (r1, c1)

Taxi2 at (r2, c2)
starting from (0,0)

So this DP answers:

“What is the best past path to reach this state?”

// BOTTOM-UP (3D Tabulation)

// dp[r1][c1][r2] = maximum passengers collected SO FAR
// while reaching:
//   Taxi1 at (r1, c1)
//   Taxi2 at (r2, c2)
// from the start (0,0)

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    const int NEG = -1e9;
    static int dp[55][55][55];

    // Initialize all states as impossible
    for (int i=0;i<n;i++)
      for (int j=0;j<n;j++)
        for (int k=0;k<n;k++)
            dp[i][j][k] = NEG;

    // Starting state
    dp[0][0][0] = grid[0][0];

    for (int r1=0;r1<n;r1++) {
        for (int c1=0;c1<n;c1++) {
            for (int r2=0;r2<n;r2++) {

                int c2 = r1 + c1 - r2;
                if (c2 < 0 || c2 >= n) continue;

                // Invalid if any taxi hits obstacle
                if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
                    continue;

                // Best way to reach this state from past
                int bestPast = dp[r1][c1][r2];
                if (r1 > 0) bestPast = max(bestPast, dp[r1-1][c1][r2]);
                if (c1 > 0) bestPast = max(bestPast, dp[r1][c1-1][r2]);
                if (r2 > 0) bestPast = max(bestPast, dp[r1][c1][r2-1]);
                if (r1>0 && r2>0) bestPast = max(bestPast, dp[r1-1][c1][r2-1]);

                if (bestPast < 0) continue;

                // Add current passengers
                int current = 0;
                if (r1 == r2 && c1 == c2)
                    current = grid[r1][c1];
                else
                    current = grid[r1][c1] + grid[r2][c2];

                dp[r1][c1][r2] = bestPast + current;
            }
        }
    }

    return max(0, dp[n-1][n-1][n-1]);
}
=============================================
3. 3D DP with Steps (k-dimension)
State meaning

dp[k][r1][r2] = maximum passengers collected so far,
after exactly k steps, when:

Taxi1 is at (r1, k-r1)

Taxi2 is at (r2, k-r2)

So this DP answers:

“At time k, what is the best we can do with both taxis?”

// 3D DP WITH STEPS (k)

// dp[k][r1][r2] = maximum passengers collected SO FAR
// after exactly k steps,
// when:
//   Taxi1 is at (r1, k-r1)
//   Taxi2 is at (r2, k-r2)

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    const int NEG = -1e9;
    static int dp[105][55][55];

    // Initialize all states as impossible
    for (int k=0;k<105;k++)
        for (int i=0;i<55;i++)
            for (int j=0;j<55;j++)
                dp[k][i][j] = NEG;

    dp[0][0][0] = grid[0][0];

    for (int k = 1; k <= 2*n-2; k++) {
        for (int r1 = max(0, k-(n-1)); r1 <= min(n-1, k); r1++) {
            for (int r2 = max(0, k-(n-1)); r2 <= min(n-1, k); r2++) {

                int c1 = k - r1;
                int c2 = k - r2;

                if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
                    continue;

                // Best way to reach this state at time k
                int bestPast = dp[k-1][r1][r2];
                if (r1 > 0) bestPast = max(bestPast, dp[k-1][r1-1][r2]);
                if (r2 > 0) bestPast = max(bestPast, dp[k-1][r1][r2-1]);
                if (r1>0 && r2>0) bestPast = max(bestPast, dp[k-1][r1-1][r2-1]);

                if (bestPast < 0) continue;

                if (r1 == r2)
                    dp[k][r1][r2] = bestPast + grid[r1][c1];
                else
                    dp[k][r1][r2] = bestPast + grid[r1][c1] + grid[r2][c2];
            }
        }
    }

    return max(0, dp[2*n-2][n-1][n-1]);
}
==================================================

4. Optimized 2D DP (Rolling Array)
State meaning

dp[r1][r2] = maximum passengers collected so far at current step k,
when:

Taxi1 is at (r1, k-r1)

Taxi2 is at (r2, k-r2)

We don’t store k, it’s implicit.

So this DP answers:

“On this diagonal (time k), what is the best state?”


// 2D OPTIMIZED DP (Rolling)

// dp[r1][r2] = maximum passengers collected SO FAR
// at current step k,
// when:
//   Taxi1 is at (r1, k-r1)
//   Taxi2 is at (r2, k-r2)

int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    const int NEG = -1e9;

    vector<vector<int>> dp(n, vector<int>(n, NEG));
    dp[0][0] = grid[0][0];

    for (int k = 1; k <= 2*n-2; k++) {
        vector<vector<int>> newdp(n, vector<int>(n, NEG));

        for (int r1 = max(0, k-(n-1)); r1 <= min(n-1, k); r1++) {
            for (int r2 = max(0, k-(n-1)); r2 <= min(n-1, k); r2++) {

                int c1 = k - r1;
                int c2 = k - r2;

                if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
                    continue;

                // Best way to reach this state from previous step
                int bestPast = dp[r1][r2]; // both from left
                if (r1 > 0) bestPast = max(bestPast, dp[r1-1][r2]);
                if (r2 > 0) bestPast = max(bestPast, dp[r1][r2-1]);
                if (r1>0 && r2>0) bestPast = max(bestPast, dp[r1-1][r2-1]);

                if (bestPast < 0) continue;

                if (r1 == r2)
                    newdp[r1][r2] = bestPast + grid[r1][c1];
                else
                    newdp[r1][r2] = bestPast + grid[r1][c1] + grid[r2][c2];
            }
        }

        dp = newdp; // roll to next diagonal
    }

    return max(0, dp[n-1][n-1]);
}

