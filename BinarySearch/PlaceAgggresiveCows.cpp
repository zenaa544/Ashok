Problem statement
You are given an array 'arr' consisting of 'n' integers which denote the position of a stall.
You are also given an integer 'k' which denotes the number of aggressive cows.
You are given the task of assigning stalls to 'k' cows such that the minimum distance between any two of them is the maximum possible.
Print the maximum possible minimum distance.

Example:
Input: 'n' = 3, 'k' = 2 and 'arr' = {1, 2, 3}
Output: 2
Explanation: The maximum possible minimum distance will be 2 when 2 cows are placed at positions {1, 3}. Here distance between cows is 2.

bool canPlaceCows(vector<int>& stalls, int K, int distance){

    int lastPos=stalls[0];
    int cowsPlaced=1;

    for(int i=1; i<stalls.size();i++){
         
         if(stalls[i]-lastPos>=distance){
             cowsPlaced++;
             lastPos=stalls[i];

             if(cowsPlaced==K){
                 return true;
             }
         }

    }
    return false;

}

int aggressiveCows(vector<int> &stalls, int k)
{
    //    Write your code here.

    sort(stalls.begin(),stalls.end());

    int low = 1, high = stalls.back() - stalls.front();
    int ans = 0;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (canPlaceCows(stalls, k, mid)) {
            ans = mid;    // Possible, try for bigger distance
            low = mid + 1;
        } else {
            high = mid - 1; // Not possible, reduce distance
        }
    }
    
    return ans;


}
