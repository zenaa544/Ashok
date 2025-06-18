Given a binary grid of n*m. Find the distance of the nearest 1 in the grid for each cell.
The distance is calculated as |i1  - i2| + |j1 - j2|, where i1, j1 are the row number and column number of the current cell, and i2, j2 are the row number and column number of the nearest cell having value 1.
There should be atleast one 1 in the grid.

  
 Solution:
  Push all cells having value 1 to a queue; visit neighbouring cells using BFS 
  calculate neighbouring cells distnace from cells having 1 as +1.
  
Instead of doing a BFS from each 0, do a single BFS from all 1s at the same time.
This works because:
The shortest distance from a 0 to the nearest 1 will be found when the 0 is first reached during BFS.
BFS explores in increasing order of distance (layer by layer), so the first time a cell is visited, it's via the shortest path.
  

  class Solution {
  public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int r = grid.size();
        int c = grid[0].size();

        vector<vector<int>> ans(r, vector<int>(c, -1));
        vector<vector<bool>> visited(r, vector<bool>(c, false));
        queue<pair<int, int>> q;

        // Step 1: Push all 1s into the queue and set their distance = 0
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    ans[i][j] = 0;
                    visited[i][j] = true;
                }
            }
        }

        // Step 2: Directions - up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 3: BFS from all 1s
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dr[d];
                int ny = y + dc[d];

                if (nx >= 0 && nx < r && ny >= 0 && ny < c && !visited[nx][ny]) {
                    ans[nx][ny] = ans[x][y] + 1;
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        return ans;
    }
};
