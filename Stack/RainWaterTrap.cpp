Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.


class Solution {
public:
    int trap(vector<int>& height) {
        
       int n = height.size();
    if (n == 0) return 0;

    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax)
                leftMax = height[left];
            else
                water += leftMax - height[left];
            ++left;
        } else {
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                water += rightMax - height[right];
            --right;
        }
    }

    return water;

    }
};




monotonic stack. The key idea is to maintain a stack of indices with non-increasing bar heights, and for every bar, check if it can serve as a right boundary to trap water between bars.

💡 Monotonic Stack Strategy:
Traverse the array.

For each bar:

While the stack is not empty and current bar is higher than the top of the stack:

Pop the top (this represents the bottom of a water container).

If the stack is not empty after the pop:

Calculate the distance between current bar and the new top.

Calculate the bounded height using the min of left and right bar.

Add the trapped water.

✅ C++ Code:
int trap(const std::vector<int>& height) {
    std::stack<int> st;
    int water = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        // While current height is greater than height at stack top
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();

            if (st.empty()) break;

            int distance = i - st.top() - 1;
            int boundedHeight = std::min(height[i], height[st.top()]) - height[top];
            water += distance * boundedHeight;
        }

        st.push(i);
    }

    return water;
}

int main() {
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "Trapped water: " << trap(height) << " units" << std::endl;
    return 0;
}
