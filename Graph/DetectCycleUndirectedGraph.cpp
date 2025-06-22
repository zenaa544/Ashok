Given an undirected graph with V vertices and E edges, represented as a 2D vector edges[][], where each entry edges[i] = [u, v]
denotes an edge between vertices u and v, determine whether the graph contains a cycle or not.

Examples:
Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: true
Explanation: 
 
1 -> 2 -> 0 -> 1 is a cycle.
Input: V = 4, E = 3, edges[][] = [[0, 1], [1, 2], [2, 3]]
Output: false
Explanation: 
 
No cycle in the graph.
=======================================================================
Solution use edges to create an adjacent list first ,then use BFS or DFS.

=======================================================================
DFS
=================
class Solution {
  public:
    bool dfs(vector<vector<int>>&adj, int current,int parent,vector<int>& visited){
        
        if(visited[current]==1)return true;
        
        visited[current]=1;
        for(auto neighbor: adj[current]){
            
            if(neighbor!=parent){
                if(dfs(adj,neighbor,current,visited))
                    return true;
            }
            
        }
        return false;
    }
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Code here
        
        vector<int>visited(V,0);
        
        vector<vector<int>>adj(V);
        
        for(auto edge:edges){
            
            int u= edge[0];
            int v= edge[1];
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        for(int i=0; i<V;i++){
                if(visited[i]==0){
                   if(dfs(adj,i,-1,visited))
                       return true;
                }
        }
        return false;
    }
    
};

==========================================================================
BFS
========  
bool bfs(int start, vector<vector<int>>& adjList,unordered_map<int,bool>& visited ){

     queue<pair<int,int>> q;
     q.push({start,-1});

    while(!q.empty()){
     
        pair<int,int> entry= q.front();
        int node=entry.first;
        int prev=entry.second;
        q.pop();
        if(visited[node]==true){
            return true;

        }

        visited[node]=true;

        for(auto entry: adjList[node]){

            if(entry!=prev){
                q.push({entry,node});
            }

        }
    }
    return false;
}
string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // Write your code here.
    unordered_map<int,bool> visited;

    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
    }
    vector<vector<int>> adjList(n+1);
	
    
    for(auto edge:edges){

        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
        
    }
   
    for(int i=1;i<=n;i++){

        if (!visited[i]) {
            if (bfs(i, adjList, visited))
                return "Yes";
        }
    }

    return "No";

}
