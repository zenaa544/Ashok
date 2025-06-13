Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

 

#include <stack>
using namespace std;

class MinStack {
    stack<long long> st;
    long long minVal;

public:
    MinStack() {}

    void push(int val) {
        if (st.empty()) {
            st.push(val);
            minVal = val;
        } else if (val < minVal) {
            // Encode and update minVal
            st.push(2LL * val - minVal);
            minVal = val;
        } else {
            st.push(val);
        }
    }

    void pop() {
        if (st.empty()) return;
        long long top = st.top();
        st.pop();
        if (top < minVal) {
            // Decode previous minVal
            minVal = 2 * minVal - top;
        }
    }

    int top() {
        long long top = st.top();
        if (top >= minVal) {
            return top;
        } else {
            // Encoded value → actual top is current minVal
            return minVal;
        }
    }

    int getMin() {
        return minVal;
    }
};
