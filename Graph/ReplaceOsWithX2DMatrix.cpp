Given a 2D array grid G of 'O's and 'X's. The task is to replace all 'O' with 'X' contained in each island. Where, an island is a set of 'O's connected horizontally 
or vertically and surrounded by 'X' from all of it's boundaries. (Boundary means top, bottom, left and right)

Example:
{{X, X, O, X, X, X},
 {X, X, O, X, O, X},
 {X, X, X, O, O, X},
 {X, O, X, X, X, X},
 {O, X, O, O, X, X},
 {X, X, X, X, O, X}}
In the above example, there are 3 islands. Considering Zero based indexing of rows and columns, in the following islands described here, (x,y) represents the element in xth row and yth column.

Island 1: Formed by three elements at (1, 4), (2, 3), (2, 4) positions.

Island 2: Formed by a single element at (3, 1) position.

Island 3: Formed by two elements at (4, 2), (4, 3) positions.

Note:

In the above example, elements at positions (0, 2) and (1,2) do not form an island as there is no 'X' surronding it from the top.


Solution : 

  Mark the Border Os and the connected Os to border Os , these don't represent connected island.
  Traverse through matrix mark the Os to X and flip the erlier marked Os(#) back to O.
  
DFS Solution
  
void markConnectedZerosToBorder(char** arr, int r, int c, int n, int m) {
    if (r < 0 || r >= n || c < 0 || c >= m)
        return;
    if (arr[r][c] != 'O')
        return;

    arr[r][c] = '#';  // Mark as protected (connected to border)

    markConnectedZerosToBorder(arr, r - 1, c, n, m);
    markConnectedZerosToBorder(arr, r + 1, c, n, m);
    markConnectedZerosToBorder(arr, r, c - 1, n, m);
    markConnectedZerosToBorder(arr, r, c + 1, n, m);
}

void replaceOWithX(char** arr, int n, int m) {
    // Step 1: Mark border-connected 'O's with '#'
    for (int i = 0; i < m; i++) {
        if (arr[0][i] == 'O')
            markConnectedZerosToBorder(arr, 0, i, n, m);
        if (arr[n - 1][i] == 'O')
            markConnectedZerosToBorder(arr, n - 1, i, n, m);
    }

    for (int i = 0; i < n; i++) {
        if (arr[i][0] == 'O')
            markConnectedZerosToBorder(arr, i, 0, n, m);
        if (arr[i][m - 1] == 'O')
            markConnectedZerosToBorder(arr, i, m - 1, n, m);
    }

    // Step 2: Flip all unmarked 'O' to 'X', and '#' back to 'O'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 'O')
                arr[i][j] = 'X';
            else if (arr[i][j] == '#')
                arr[i][j] = 'O';
        }
    }
}


BFS Solution 

#include <queue>
using namespace std;

void replaceOWithX(char** arr, int n, int m) {


    // BFS queue
    queue<pair<int, int>> q;

    // Step 1: Push all boundary 'O's to queue
    for (int i = 0; i < n; i++) {
        if (arr[i][0] == 'O') {
            q.push({i, 0});
            arr[i][0] = '#';
        }
        if (arr[i][m - 1] == 'O') {
            q.push({i, m - 1});
            arr[i][m - 1] = '#';
        }
    }

    for (int j = 0; j < m; j++) {
        if (arr[0][j] == 'O') {
            q.push({0, j});
            arr[0][j] = '#';
        }
        if (arr[n - 1][j] == 'O') {
            q.push({n - 1, j});
            arr[n - 1][j] = '#';
        }
    }

    // Step 2: BFS from all border 'O's to mark all connected 'O's
    // Directions: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && arr[nr][nc] == 'O') {
                arr[nr][nc] = '#';
                q.push({nr, nc});
            }
        }
    }

    // Step 3: Replace remaining 'O' with 'X', and '#' back to 'O'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 'O') {
                arr[i][j] = 'X';
            } else if (arr[i][j] == '#') {
                arr[i][j] = 'O';
            }
        }
    }
}


