You are given ‘n’ cities, some of which are connected by bidirectional roads.
You are also given an ‘n x n’ matrix i.e. ‘roads’, where if city ‘i’ and ‘j’ are connected by a road then ‘roads[i][j]'= 1, otherwise ‘roads[i][j]' = 0.
A province is a group of cities that are either directly or indirectly connected to each other through roads.

The goal is to count and return the total number of such provinces in the given matrix.

Example:
n = 4, roads = [ [1, 1, 1, 0],
                 [1, 1, 1, 0],
                 [1, 1, 1, 0],
                 [0, 0, 0, 1] ]

So, there are ‘2’ provinces.
Note:
1. A city is connected to itself. So, for every city ‘i’, ‘roads[i][i] = 1’.


Solution:

Do BFS or DFS on each city and traverse each connected city.(city is represent as nodes in graph)
mark them as visited.
When we encounter non-visited city then increamnet province count.

void bfs(vector<vector<int>>& roads, vector<bool>& visited, int city, int n) {
    queue<int> q;
    q.push(city);
    visited[city] = true;  // Mark as visited when pushed

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            if (roads[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int findNumOfProvinces(vector<vector<int>>& roads, int n) {
    vector<bool> visited(n, false);
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            ++count;
            bfs(roads, visited, i, n);
        }
    }

    return count;
}
================================================================================



void dfs(int city, vector<vector<int>>& roads, vector<bool>& visited, int n) {
    visited[city] = true;

    for (int i = 0; i < n; i++) {
        if (roads[city][i] == 1 && !visited[i]) {
            dfs(i, roads, visited, n);
        }
    }
}


int findNumOfProvinces(vector<vector<int>>& roads, int n) {
    vector<bool> visited(n, false);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i, roads, visited, n);
        }
    }

    return count;
}
