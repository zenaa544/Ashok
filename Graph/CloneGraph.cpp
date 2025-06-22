Given a connected undirected graph represented by adjacency list, adjList[][] with n nodes, having a distinct label from 0 to n-1, 
  where each adj[i] represents the list of vertices connected to vertex i.

Create a clone of the graph, where each node in the graph contains an integer val and an array (neighbors) of nodes, 
containing nodes that are adjacent to the current node.

class Node {
    val: integer
    neighbors: List[Node]
}
Your task is to complete the function cloneGraph( ) which takes a starting node of the graph as input and 
returns the copy of the given node as a reference to the cloned graph.

BFS
graphNode *cloneGraph(graphNode *node)
{
    // Write your code here.
    if(!node)return node;
	
	queue<graphNode*> q;
	q.push(node);

	unordered_map<graphNode*,graphNode*> visited;

    graphNode* start = new graphNode(node->data);
    visited[node]=start;
	
	while(!q.empty()){
        
       graphNode* current = q.front();

	   q.pop();
       
	   for(auto neighbour:current->neighbours){

		   if(visited.find(neighbour)==visited.end()){

			   graphNode* temp = new graphNode(neighbour->data);

			   visited[neighbour]=temp;
			   q.push(neighbour);
		   }
	   }

	   for( auto neighbour: current->neighbours){
		   visited[current]->neighbours.push_back(visited[neighbour]);
	   }

	}

   return start;
}
==================

  DFS

   Node* cloneGraphDFS(Node* node, unordered_map<Node*,Node*>& visited){

        if(node==NULL)return NULL;
        
        if(visited.find(node)!=visited.end())
             return visited[node];

        Node* clone= new Node();
        clone->val=node->val;
        visited[node] = clone;
        for(auto neighbor:node->neighbors){
           clone->neighbors.push_back(cloneGraphDFS(neighbor,visited));  
        }  

        return clone;   

    }
    Node* cloneGraph(Node* node) {
       unordered_map<Node*, Node*> visited;
       return cloneGraphDFS(node,visited);
    }
