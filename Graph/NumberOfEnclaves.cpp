You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.

Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

 

Example 1:


Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
Example 2:


Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 500
grid[i][j] is either 0 or 1.


DFS  
class Solution {
public:
    void mark1sdfs(vector<vector<int>>& copy, int cr, int cc, int row, int col) {
        if (cr < 0 || cr >= row || cc < 0 || cc >= col || copy[cr][cc] != 1)
            return;

        copy[cr][cc] = 2;  // mark visited

        mark1sdfs(copy, cr + 1, cc, row, col); // down
        mark1sdfs(copy, cr - 1, cc, row, col); // up
        mark1sdfs(copy, cr, cc + 1, row, col); // right
        mark1sdfs(copy, cr, cc - 1, row, col); // left
    }

    int numEnclaves(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();

        vector<vector<int>> copy = grid;

        // Traverse border cells and mark reachable land as 2
        for (int i = 0; i < row; i++) {
            if (copy[i][0] == 1)
                mark1sdfs(copy, i, 0, row, col);
            if (copy[i][col - 1] == 1)
                mark1sdfs(copy, i, col - 1, row, col);
        }
        for (int j = 0; j < col; j++) {
            if (copy[0][j] == 1)
                mark1sdfs(copy, 0, j, row, col);
            if (copy[row - 1][j] == 1)
                mark1sdfs(copy, row - 1, j, row, col);
        }

        int count = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (copy[i][j] == 1)
                    count++;
            }
        }

        return count;
    }
};

===========================
  BFS

  class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        queue<pair<int, int>> q;

        // Step 1: Add all boundary land cells to the queue
        for (int i = 0; i < row; i++) {
            if (grid[i][0] == 1) {
                q.push({i, 0});
                grid[i][0] = 2;
            }
            if (grid[i][col - 1] == 1) {
                q.push({i, col - 1});
                grid[i][col - 1] = 2;
            }
        }
        for (int j = 0; j < col; j++) {
            if (grid[0][j] == 1) {
                q.push({0, j});
                grid[0][j] = 2;
            }
            if (grid[row - 1][j] == 1) {
                q.push({row - 1, j});
                grid[row - 1][j] = 2;
            }
        }

        // Step 2: BFS to mark all reachable land cells from boundaries
        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 1) {
                    q.push({nr, nc});
                    grid[nr][nc] = 2;
                }
            }
        }

        // Step 3: Count remaining 1s
        int count = 0;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (grid[i][j] == 1)
                    count++;

        return count;
    }
};
