Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, check whether it contains any cycle or not.
The graph is represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes an edge from verticex u to v.

Examples:

Input: V = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 0], [2, 3]]

Output: true
Explanation: The diagram clearly shows a cycle 0 → 2 → 0
Input: V = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]

Output: false
Explanation: no cycle in the graph


class Solution {
  public:
  bool dfs(vector<vector<int>>& adjList,int node, vector<bool>& visited,vector<bool>& pathVisited){

        visited[node] = true;
        pathVisited[node] = true;
    
        for (int neighbor : adjList[node]) {
            if (visited[neighbor] && pathVisited[neighbor]) {
                
                    return true;
            }
            else {
                
                if(dfs(adjList, neighbor, visited, pathVisited))
                    return true;
            }
        }
    
        pathVisited[node] = false;  // backtrack
        return false;
}
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // code here
        vector<vector<int>> adjList(V);
    
        for (auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1] );  // convert to 0-based index
        }
    
        vector<bool> visited(V, false);
        vector<bool> pathVisited(V, false);
    
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (dfs(adjList, i, visited, pathVisited))
                    return 1;
            }
        }

    return 0;
    }
};
