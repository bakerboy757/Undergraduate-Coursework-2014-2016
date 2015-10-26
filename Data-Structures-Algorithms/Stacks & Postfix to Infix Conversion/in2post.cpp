#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "stack.h"


using namespace std;
using namespace cop4530;
int infix2postfix(const vector<char>&, vector<char>& );
void evaluatePostfix(const vector<char>&);
float evaluate(float, float, char);
void print(const vector<char>&);
int precedence(char );
int main() {
    string input = "";
    vector<char> postfix;
    vector<char> infix;
    int error;

    ////check cout and cin are OK with the side effect of writing "Enter..." AND reading a line
    while(cout << "Enter infix expression (\"exit\" to quit): ", getline(cin, input)){
		if (input == "exit") return(EXIT_SUCCESS);

        //puts string contents into vector 
        for (auto c : input)
            infix.push_back(c);

        //converts notations
        error = infix2postfix(infix, postfix);
       
        //if no terminating errors occur then go on to next step of evaluating the postifix
        if (!error) evaluatePostfix(postfix);
        
        //clear contetns of vector
        infix.clear();
        postfix.clear();

    }
    cout << "\n";     
    return(EXIT_SUCCESS);
}
void defaultPrint(const vector<char>& vec) {
    //outputs conversion
    cout << "\n\nPostfix expression: ";
    print(vec);

    //outputs the equality
    cout << "\nPostfix evaluation: ";
    print(vec);
    cout << "= ";

}
void evaluatePostfix(const vector<char>& postfix) {
    //get out immediately if there are any characters
    for (unsigned int x = 0; x < postfix.size(); x++) {
        if (isalpha(postfix[x])) {
            defaultPrint(postfix);
            print(postfix);
            cout << "\n";
            return;
        }
    }
    stack<float> operandStk;
    float i, j, lhs; 
    
    for (unsigned int x = 0; x < postfix.size(); x++) {
        string tempStr = "";
        //if digit need to check rest of precedding characters 
        if (x != postfix.size() && isdigit(postfix[x])) {
            while (x < postfix.size() && (isdigit(postfix[x]) || postfix[x] == '.')) {
		tempStr += postfix[x];
                x++;
            }
            if(!isspace(postfix[x])){
	       defaultPrint(postfix);
               print(postfix);
               cout << "\n";
               return;
	    }
            //convert string to float value
            float value = stof(tempStr.c_str());
            operandStk.push(value);
        
        }
            
        else if (postfix[x] == '+' || postfix[x] == '-' || postfix[x] == '*' || postfix[x] == '/') {
            if (operandStk.size() < 2) {
                cout << "ERROR: Fewer than two elements in stack\n";
                return;
            }
            //preserve top of stack twice and pop off twice
            i = operandStk.top();
            operandStk.pop();
            j = operandStk.top();
            operandStk.pop();
            lhs = evaluate(i, j, postfix[x]);
            //push returned value to stack
            operandStk.push(lhs);
        }

    }
    if (operandStk.size() > 1) {
        cout << "ERROR: More than one element left in stack\n";
        return;
    }
    else if (operandStk.size() == 1) {
        defaultPrint(postfix);
        cout << operandStk;
        cout << "\n";
    
    }
    else {
        defaultPrint(postfix);
        cout << "0";
        cout << "\n";
    
    }
        
}
float evaluate(float i, float j, char c) {
    float lhs;
    switch (c) {
    case '+': lhs = i + j;
        break;
    case '-': lhs = j - i;
        break;
    case '*': lhs = j * i;
        break;
    case '/': lhs = j / i;
        break;
    }
    return lhs;
            


}
void print(const vector<char>& vec) {
    for (unsigned int i = 0; i < vec.size(); i++)
        cout << vec[i];
    
}
/*
* returns 1 when eror occurs
* returns 0 when exits function normally
*
*/
int infix2postfix(const vector<char> &infix, vector<char>& postfix) {
    stack<char> s;
    unsigned int i;
    if (infix.empty())
        return 0;

    for (i = 0; i < infix.size(); i++) {
        //takes care of operands
        if (isalpha(infix[i]) || isdigit(infix[i])) {
            postfix.push_back(infix[i]);
            unsigned int j = ++i;
            while (j < infix.size() && !isspace(infix[j])) {
                postfix.push_back(infix[j]);
                j++;
            }
            i = j;
            postfix.push_back(' ');
        }
        else if (infix[i] == '(') {
            s.push(infix[i]);
        }
        //takes care if operator
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            while (!s.empty() && s.top() != '(' && precedence(s.top()) >= precedence(infix[i])) {
                postfix.push_back(s.top());
                postfix.push_back(' ');
                s.pop();
            }
            s.push(infix[i]);
        }
        else if (infix[i] == ')') {
            if (!(isalpha(infix[i - 2]) || isdigit(infix[i - 2]) || infix[i-2] != '(' || infix[i-2] != ')')) {
                cout << "\nERROR: Missing operators in the expression.\n" << endl;
                return 1;
            }
            while (!s.empty() && s.top() != '(') {
                postfix.push_back(s.top());
                postfix.push_back(' ');
                s.pop();
            }
            if (s.empty()) {
                cout << "\nERROR: Infix expression: ";
                print(infix);
                cout << " has mismatched parens!\n";
                return 1;
            }

            else   s.pop();

        }
    }
    //checks again at end
    if (!(isalpha(infix[i - 2]) || isdigit(infix[i - 2]) ||  infix[i - 2] != ')' || infix[i-2] != '(')) {
        cout << "\nERROR: Missing operators in the expression.\n" << endl;
        return 1;
    }

    while (!s.empty()) {
        if (s.top() == '(') {
            cout << "\nERROR: Infix expression: ";
            print(infix);
            cout << " has mismatched parens!\n";
            return 1;
        }
        postfix.push_back(s.top());
        postfix.push_back(' ');
        s.pop();
    }
    return 0;

}
                        
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 3;
        default:
            cout << op << " is not valid";
            return 0;
    }

}
