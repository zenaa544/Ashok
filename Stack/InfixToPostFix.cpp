Solution Steps
Initialize:
An empty string postfix for output.
An empty stack opStack for operators.
Loop through each character ch in the infix expression:
a. If ch is an operand (e.g., letter or digit):
Append it to postfix.
b. If ch is (:
Push it to opStack.
c. If ch is ):
Pop from opStack and append to postfix until you find (.
Discard the (.
d. If ch is an operator (+, -, *, /, ^):
While opStack is not empty AND top of opStack is not ( AND:
either the priority  of top of opStack > ch, OR
priority is equal AND ch is left-associative:
Pop from opStack and append to postfix.
Push ch onto opStack.
After the loop, pop all remaining operators from opStack and append to postfix.
Return postfix string.


#include<bits/stdc++.h>
int priority(char op){

	if(op=='^') return 3;
	else if(op=='*'||op=='/') return 2;
	else if(op=='+'||op=='-') return 1;
	else return -1;
}
string infixToPostfix(string exp){
	// Write your code here

	string postFix="";
	stack<char> st;

	int i=0;
	int size=exp.size();
	while(i<size){
		
		if((exp[i]>='A' && exp[i]<='Z')||
		 	(exp[i]>='a' && exp[i]<='z')||
			(exp[i]>='0' && exp[i]<='9')){
				postFix=postFix+exp[i];
		}
		else if(exp[i]=='(')
			st.push(exp[i]);
		else if(exp[i]==')'){
			while(!st.empty() && st.top()!='('){
				postFix=postFix+st.top();
				st.pop();

			}
			st.pop();
		}	
        else {
			while(!st.empty() && (priority(exp[i])<=priority(st.top()))){
				postFix=postFix+st.top();
				st.pop();
			}
			st.push(exp[i]);
		}
		++i;
	}
    while(!st.empty()){
		postFix=postFix+st.top();
		st.pop();
	}
	return postFix;
}
