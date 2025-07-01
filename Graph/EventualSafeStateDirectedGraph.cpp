There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

 

Example 1:

Illustration of graph
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
Example 2:

Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.

Detect Cycle in Directed graph
If a node is not part of cytcle or does not lead to a cycle it is a safe node.
When ever we dont find a cycle mark the node as safe node.  

class Solution {
    bool dfs(vector<vector<int>>& adjList,int node, vector<bool>& visited,vector<bool>& pathVisited,vector<int>& isSafe){

        visited[node] = true;
        pathVisited[node] = true;
        isSafe[node]=0;    
        for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    if (dfs( adjList, neighbor,visited, pathVisited,isSafe))
                        return true;
                } else if (pathVisited[neighbor]) {
                        return true;  // back edge
                }
        }
    
        pathVisited[node] = false;  // backtrack
        isSafe[node]=1;
        return false;
}
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
         
  
        int V= graph.size();
        vector<bool> visited(V, false);
        vector<bool> pathVisited(V, false);
        vector<int> isSafe(V, 0);
        vector<int> ans;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfs(graph,i,visited, pathVisited,isSafe);
                    
            }
        }

  
    //sort(ans.begin(),ans.end());
    for( int i =0 ;i<V;i++){
        if(isSafe[i])
            ans.push_back(i);
    }
    return ans;
    }
    
};
