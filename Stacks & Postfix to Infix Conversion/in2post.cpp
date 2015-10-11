#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "stack.h"

using namespace std;
using namespace cop4530;
void analyzeStk(Stack<int>& , string);
enum class Sign { PLUS = '+', MINUS = '-', TIMES = '*', DIVIDE = '/'};
bool operator<= (const Sign& a, const Sign& b);
int main() {
	string input = "";
	Stack<int> postfix;
	vector<char> infix;
	do {
		cout << "Enter infix expression (\"exit\") to quit): ";
		getline(cin, input);
		for(auto c: input)
			infix.push_back(c);
		analyzeStk(postfix, input);
	} while (input != "exit");
		
	
	
	
	
	



	return(EXIT_SUCCESS);
}
void analyzeStk(const vector<char> &infix) {
	int place = 0;
	Stack<char> s;
	
	for (int i = 0; i < infix.size(); ++i) {
		if (infix[i] == ' ')
			break;
		//takes care of operands
		if (isalpha(infix[i]) || isdigit(infix[i])) {
			cout << infix[i];
			int j = ++i;
			while (isdigit(infix[j]) || isalpha(infix[i]))
				cout << infix[j];
		}
		//takes care if operator
		else if (infix[i] == '+'|| infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(')
			while(s.top() != '(' && s.top())
			
		
	
	
	
	}
	for (auto c : input) {
		while (c != ' ') {
			if (i == 0 && isdigit(c) != 0) {
				num = static_cast<int>(c);
				postfix.push(num);
			}
		
		
		
		}
	
	
	}


}
bool operator>= (const Sign& a, const Sign& b) {
	if(a == PLUS)


}