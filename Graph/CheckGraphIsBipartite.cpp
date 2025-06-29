Given a Graph with V vertices (Numbered from 0 to V-1) and E edges. Check whether the graph is bipartite or not.

A bipartite graph can be colored with two colors such that no two adjacent vertices share the same color. This means we can divide the graph’s vertices into two distinct sets where:

All edges connect vertices from one set to vertices in the other set.
No edges exist between vertices within the same set.
Examples:

Input: V = 3, edges[][] = [[0, 1], [1,2]]
Bipartite-Graph
Output: true
Explanation: The given graph can be colored in two colors so, it is a bipartite graph.
Input: V = 4, edges[][] = [[0, 3], [1, 2], [3, 2], [0, 2]]

Output: false 
Explanation: The given graph cannot be colored in two colors such that color of adjacent vertices differs. 


  BFS

  class Solution {
    bool bfsCheck(int node, vector<vector<int>>& adjList, vector<int>& visited ){
        
        queue<int> q;
        
        q.push(node);
        
        while(!q.empty()){
            
            auto current=q.front();
            q.pop();
            
            for( int neighbor: adjList[current]){
                
                if(visited[neighbor]==visited[current])
                    return false;
                else if(visited[neighbor]==-1){
                    q.push(neighbor);
                    visited[neighbor]=!visited[current];
                }
            }
        }
        
        return true;
    }
  public:
    bool isBipartite(int V, vector<vector<int>> &edges) {
        // Code here
        
        vector<vector<int>> adjList(V);
        
        for(auto edge: edges){
            
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        
        vector<int> visited(V,-1);
        
        for( int i=0 ;i<V;i++){
            if(visited[i]==-1){
                visited[i]=0;
                if(!bfsCheck(i,adjList,visited))
                    return false;
            }
        }
        
        return true;
    }
};

==============================================================
  DFS
  bool dfsCheck(int node, vector<vector<int>>& adjList, vector<int>& visited ){
        

            for( int neighbor: adjList[node]){
                
                if(visited[neighbor]==visited[node])
                    return false;
                else if(visited[neighbor]==-1){
      
                    visited[neighbor]=!visited[node];
                    if(!dfsCheck(neighbor,adjList,visited))
                        return false;
                }
            }

        
        return true;
    }
