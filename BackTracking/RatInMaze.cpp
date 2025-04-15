You are given a starting position for a rat which is stuck in a maze at an initial point (0, 0) (the maze can be thought of as a 2-dimensional plane). The maze would be given in the form of a square matrix of order 'N' * 'N' where the cells with value 0 represent the maze’s blocked locations while value 1 is the open/available path that the rat can take to reach its destination. The rat's destination is at ('N' - 1, 'N' - 1). Your task is to find all the possible paths that the rat can take to reach from source to destination in the maze. The possible directions that it can take to move in the maze are 'U'(up) i.e. (x, y - 1) , 'D'(down) i.e. (x, y + 1) , 'L' (left) i.e. (x - 1, y), 'R' (right) i.e. (x + 1, y).

Note:
Here, sorted paths mean that the expected output should be in alphabetical order.
For Example:
Given a square matrix of size 4*4 (i.e. here 'N' = 4):
1 0 0 0
1 1 0 0
1 1 0 0
0 1 1 1 
Expected Output:
DDRDRR DRDDRR 
i.e. Path-1: DDRDRR and Path-2: DRDDRR

The rat can reach the destination at (3, 3) from (0, 0) by two paths, i.e. DRDDRR and DDRDRR when printed in sorted order, we get DDRDRR DRDDRR.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
2 <= N <= 5
0 <= MATRIX[i][j] <= 1

Where N is the size of the square matrix.

  My Solution
  void solve(vector<vector<int>>& arr, vector<string>& ans, int n, string& path,int x, int y, vector<vector<int>>& visited){

   if(x<0||x>=n || y<0|| y>=n || arr[x][y]==0|| visited[x][y]==1) return;
   if(x==n-1 && y==n-1 && arr[x][y]==1){ 
    ans.push_back(path);
    return;
   }
   visited[x][y]=1;
   vector<pair<pair<int,int>,char>> directions= {{{-1,0},'U'},{{1,0},'D'},{{0,-1},'L'},{{0,1},'R'}};
    
   for(auto direction: directions){
     int dx = x+direction.first.first;
     int dy = y+direction.first.second;
     char d = direction.second;

     path.push_back(d);
     solve(arr,ans,n,path,dx,dy,visited);
     path.pop_back();
   }
   visited[x][y]=0;
}


vector < string > searchMaze(vector < vector < int >> & arr, int n) {
    // Write your code here.

    vector<string> ans;
    if(arr[0][0] == 0) 
        return ans;
    string path="";
    vector<vector<int>>visited(n,vector<int>(n,0));
    solve(arr,ans,n,path,0,0,visited);
    sort(ans.begin(), ans.end());
    return ans;

}
Striver Solution
// void solve(vector<vector<int>>& arr, vector<string>& ans, int n, string& path, int x, int y, vector<vector<int>>& visited) {
//     // Boundary and blocking check
//     if (x < 0 || x >= n || y < 0 || y >= n || arr[x][y] == 0 || visited[x][y] == 1)
//         return;

//     // Destination reached
//     if (x == n - 1 && y == n - 1) {
//         ans.push_back(path);
//         return;
//     }

//     // Mark current cell as visited
//     visited[x][y] = 1;

//     // Possible directions: Up, Down, Left, Right
//     vector<pair<pair<int, int>, char>> directions = {
//         {{-1, 0}, 'U'}, {{1, 0}, 'D'}, {{0, -1}, 'L'}, {{0, 1}, 'R'}
//     };

//     for (auto direction : directions) {
//         int dx = x + direction.first.first;
//         int dy = y + direction.first.second;
//         char dir = direction.second;

//         path.push_back(dir);
        
//         solve(arr, ans, n, path, dx, dy, visited);
//         path.pop_back();  // Backtrack
//     }

//     // Unmark current cell for other paths
//     visited[x][y] = 0;
// }
//  bool isSafe(vector<vector <int>> &m,vector<vector <int>> &visited, int x, int y, int n){
        
//         if(x<0 || x>=n || y <0 || y>=n || visited[x][y]==1 || m[x][y]==0)
//         return false;
        
//         else
//          return true;
//     }
//     void solve(vector<vector<int>> &m, int n,vector<vector<int>> &visited, string &path, int x, int y, vector <string> &ans){
        
//         if(m[x][y]==0)
//            return;
//         if(x==n-1 && y==n-1){
//             ans.push_back(path);
//             return;
//         }
        
//         visited[x][y]=1;
//         int newx=x+1;
//         int newy=y;
//         if(isSafe(m,visited,newx,newy,n)){
//             path.push_back('D');
//             solve(m,n,visited,path,newx,newy,ans);
//             path.pop_back( );
//         }
//         newx=x-1;
//         newy=y;
//         if(isSafe(m,visited,newx,newy,n)){
            
//             path.push_back('U');
//             solve(m,n,visited,path,newx,newy,ans);
//             path.pop_back();
//         }
        
//         newx=x;
//         newy=y-1;
//         if(isSafe(m,visited,newx,newy,n)) {
            
//             path.push_back('L');
//             solve(m,n,visited,path,newx,newy,ans);
//             path.pop_back();
//         }
        
//         newx=x;
//         newy=y+1;
//         if(isSafe(m,visited,newx,newy,n)) {
            
//             path.push_back('R');
//             solve(m,n,visited,path,newx,newy,ans);
//             path.pop_back();
//         }
//         visited[x][y]=0;
//     }
