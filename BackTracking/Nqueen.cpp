class Solution {
public:
    vector<vector<int>> solveNQueens(int n) {
        vector<vector<int>> results;
        vector<int> board(n * n, 0);  // Flattened 2D board represented as 1D array
        
        solveBacktrack(results, board, 0, n);
        
        return results;
    }
    
private:
    void solveBacktrack(vector<vector<int>>& results, 
                         vector<int>& board, 
                         int row, 
                         int n) {
        // Base case: If all queens are placed successfully
        if (row == n) {
            results.push_back(board);
            return;
        }
        
        // Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                // Place queen
                int index = row * n + col;
                board[index] = 1;  // Mark queen position with 1
                
                // Recursively place queens in next rows
                solveBacktrack(results, board, row + 1, n);
                
                // Backtrack
                board[index] = 0;  // Reset to 0
            }
        }
    }
    
    bool isValid(const vector<int>& board, int row, int col, int n) {
        // Check column (no need to check the current row as we're filling row by row)
        for (int i = 0; i < row; i++) {
            if (board[i * n + col] == 1) {
                return false;
            }
        }
        
        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i * n + j] == 1) {
                return false;
            }
        }
        
        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i * n + j] == 1) {
                return false;
            }
        }
        
        return true;
    }
};

===========================================


  class Solution {
public:

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        vector<string> board(n, string(n, '.'));
        
        solveBacktrack(results, board, 0, n);
        
        return results;
    }
    

    void solveBacktrack(vector<vector<string>>& results, 
                         vector<string>& board, 
                         int row, 
                         int n) {
        // Base case: If all queens are placed successfully
        if (row == n) {
            results.push_back(board);
            return;
        }
        
        // Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                // Place queen
                board[row][col] = 'Q';
                
                // Recursively place queens in next rows
                solveBacktrack(results, board, row + 1, n);
                
                // Backtrack
                board[row][col] = '.';
            }
        }
    }
    
    bool isValid(const vector<string>& board, int row, int col, int n) {
        // Check column (no need to check the current row as we're filling row by row)
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }
        
        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        
        return true;
    }
};
