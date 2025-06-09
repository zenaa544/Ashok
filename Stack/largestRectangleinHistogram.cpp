***************************************************************************************************************
https://leetcode.com/problems/largest-rectangle-in-histogram/

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1,
  return the area of the largest rectangle in the histogram
***************************************************************************************************************
Brute Force--
  3 Passess.
  Find next smaller element nse and previous smaller  pse elements for each element
  Calculate Area for each index heights[i]*(nse-pse-1)
*******************************************************************************************************************
    int largestRectangleArea(vector<int>& heights) {

        int n=heights.size();
        vector<int> prevSmaller(n,-1);
        vector<int> nextSmaller(n,n);

        stack<int> st1;
        stack<int> st2;
        
        for(int i=0 ;i < n;i++){

            while(!st1.empty()&& heights[st1.top()]>=heights[i]){
                st1.pop();
            }
            if(st1.empty()){

                st1.push(i);
                continue;
            }
            prevSmaller[i]=st1.top();
            st1.push(i);
        }

        for(int i=n-1;i>=0;i--){
            while(!st2.empty() && heights[st2.top()]>=heights[i]){
                st2.pop();
            }

            if(st2.empty()){
                st2.push(i);
                continue;
            }
            nextSmaller[i]=st2.top();
            st2.push(i);
        }
        
        int maxArea=0;
        for(int i=0;i<n;i++){
            int width = nextSmaller[i]-prevSmaller[i]-1;
            int area= width*heights[i];
            maxArea=max(area,maxArea);
        }
        
        return maxArea;
    }

****************************************************************************************************************************************
In single Single pass, Actaully 2 if we consider emptying the stack .
   Use stack to keep elements in increasing order
  Get the next smaller element as you pass the array,
  when find the next smaller element , pop from the stack and claulate area for the elememt that was poped
   for popped element 
nse= i/traversing index,
 pse= stack top else -1 if stack empty.

then empty the the stack in another pass and claculate area once all the elements traversed once.
********************************************************************************************************************************************
int largestRectangleArea(vector<int>& heights) {

        stack<int> st;
        int currentArea=0;
        int maxArea=0;
        int prevSmaller=-1;
        for(int i=0;i<heights.size();i++){
            while(!st.empty() && heights[i]<heights[st.top()]){

                int current=st.top();
                st.pop();
                if(!st.empty())
                    prevSmaller=st.top();
                else
                    prevSmaller=-1;
                currentArea= heights[current]*(i-prevSmaller-1);
                maxArea=max(currentArea,maxArea);
            
 
            }
        
            st.push(i);
        }

        while(!st.empty()){
            int nse=heights.size();
            int current=st.top();
            st.pop();
            int pse=st.empty()?-1:st.top();
            currentArea=heights[current]*(nse-pse-1);
            maxArea=max(currentArea,maxArea);
        }
        return maxArea;
    }

***************************************************************************************************************************************
Above approach needs additional pass to empty the stack ,that can be made cleaner but not necessrily more effective by adding a 0 to heights 
That will allow to do evrything in single pass

*************************************************************************************************************************************
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    // Add a 0 at the end to make sure we empty the stack
    heights.push_back(0);

    for (int i = 0; i < heights.size(); ++i) {
        // While the current bar is less than the bar at stack top
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }

    return maxArea;
}

*************************************************************************************************************************************
