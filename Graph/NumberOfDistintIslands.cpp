You are given a two-dimensional array/list of integers consisting of 0s and 1s. In the list, 1 represents land and 0 represents water.

The task is to find the number of distinct islands where a group of connected 1s(horizontally or vertically) forms an island.

Note:
Two islands are considered to be the same if and only if one island is equal to another(not rotated or reflected) 
i.e if we can translate one island on another without rotating or reflecting then it would be considered as the same islands. 
For example:
1 1 0
0 0 1
0 0 1

In this example, we have two islands and they would be considered as distinct islands as we can not translate 
them on one another even if they have the same no of 1's.
For example :
1 1 0 0 0 
1 1 0 0 0
0 0 0 1 1
0 0 0 1 1

In this example, we have two islands and they are the same as we can translate one island onto another island, so our answer should be 1.


BFS or DFS  traversal to explore each island.

Track the relative coordinates of each cell in an island (with respect to the starting cell).

Store the shape (a vector of relative coordinates) in a set to ensure uniqueness.

  BFS
  void bfs(int** grid, int cr, int cc, int n, int m, vector<vector<bool>>& visited, set<vector<pair<int,int>>>& ans){

        queue<pair<int,int>> q;
        vector<pair<int,int>> dir ={{-1,0},{1,0},{0,-1},{0,1}};

        q.push({cr,cc});
        visited[cr][cc]=true;
        vector<pair<int,int>> island;
        int baseRow=cr;
        int baseCol=cc;
        island.push_back({cr-baseRow,cc-baseCol});
        while(!q.empty()){
            pair<int,int> current=q.front();
            q.pop();
            for(auto d: dir){

                int dr=current.first+d.first;
                int dc=current.second+d.second;

                if(dr>=0 && dr <n && dc>=0 && dc <m && grid[dr][dc]==1 && !visited[dr][dc]){
                    q.push({dr,dc});
                    visited[dr][dc]=true;
                    island.push_back({dr-baseRow,dc-baseCol});
                }
            }
        }

        ans.insert(island);
    }
int distinctIslands(int** arr, int n, int m)
{
    //Write your code here

    vector<vector<bool>> visited(n,vector<bool>(m,0));

    queue<pair<int,int>> q;

    set<vector<pair<int,int>>> ans;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(arr[i][j]==1 && !visited[i][j]){
                bfs(arr,i,j,n,m,visited,ans);
            }
        }
    }
    
    return ans.size();
 
}
=========================================================================================================
DFS
class Solution {
public:
    void dfs(int** grid, int r, int c, int baseR, int baseC, int n, int m,
             vector<vector<bool>>& visited, vector<pair<int, int>>& shape) {

        visited[r][c] = true;
        shape.push_back({r - baseR, c - baseC});

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;

            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                grid[nr][nc] == 1 && !visited[nr][nc]) {
                dfs(grid, nr, nc, baseR, baseC, n, m, visited, shape);
            }
        }
    }

    int distinctIslands(int** grid, int n, int m) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        set<vector<pair<int, int>>> uniqueShapes;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    vector<pair<int, int>> shape;
                    dfs(grid, i, j, i, j, n, m, visited, shape);
                    sort(shape.begin(), shape.end()); // normalize
                    uniqueShapes.insert(shape);
                }
            }
        }

        return uniqueShapes.size();
    }
};
