#include "bet.h"
//default
/*
	TODO:
		need to fix error checking(to strict)


*/
BET::BET() :root{nullptr} {
    theSize = 0;
    leafs = 0;
    root = new BinaryNode;
    root->left = nullptr;
    root->right = nullptr;
    
    
}
// one-parameter constructor, where parameter "postfix" is string containing a postfix expression. 
//The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space.
BET::BET(const string postfix) {
    bool isValid = true;
    if (postfix == "") isValid = false;
    stack<BinaryNode*> s;
    vector<string> v;
    istringstream iss(postfix);
    string token;
    //v now holds postfix notation in token form
    while (getline(iss, token, ' '))
        v.push_back(token);
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v[i] != "+" && v[i] != "-" && v[i] != "*" && v[i] != "/") {
            BinaryNode *temp = new BinaryNode;
            temp->element = v[i];
            s.push(temp);
        }
        else {
           if (s.size() < 2) {
                isValid = false;
                break;
            }
            BinaryNode *temp = new BinaryNode;
            temp->element = v[i];
            temp->right = s.top();
            s.pop();
            temp->left = s.top();
            s.pop();
            s.push(temp);
        }
    
    }
	if (s.size() > 1) isValid = false;
    if (isValid) this->root = s.top();
	else { 
		this->root = nullptr; 
		cout << "Wrong postfix expression" << endl;
	
	}

}
//copy construct
BET::BET(const BET& rhs) {
    root = clone(rhs.root);
    
}
BET::~BET() {
    makeEmpty(root);
    
}
/*parameter "postfix" is string containing a postfix expression. The tree should be built based on the
postfix expression. Tokens in the postfix expression are separated by space. If the tree contains nodes
before the function is called, you need to first delete the existing nodes. Return true if the new tree is built
successfully. Return false if an error is encountered.*/
bool BET::buildFromPostfix(const string postfix) {
    makeEmpty(root);
    BET temp(postfix);
    swap(root, temp.root);
    if (root == nullptr) return false;
    return true;
    
}
//assignment operator
const BET & BET::operator= (const BET & rhs) {
    BET copy = rhs;
    root = clone(copy.root);
    return *this;
        
}
//call the private version of the printInfixExpression function to print out the infix expression.
void BET::printInfixExpression() {
    if (empty()) cout << "Empty tree" << endl;
    else printInfixExpression(root);
    cout << endl;
    
}
    
// call the private version of the printPostfixExpression function to print out the postfix expression
void BET::printPostfixExpression() {
    if (empty()) cout << "Empty Tree" << endl;
    else printPostfixExpression(root);
    cout << endl;
    
}
//call the  private version of the size function to return the number of nodes in the tree.
size_t BET::size() {
    if (empty()) return 0;
    theSize = size(root);
    return theSize;


    
}
//call the private version of the leaf_nodes function to return the number of leaf nodes in the tree.
size_t BET::leaf_nodes() {
    if (empty()) return 0;
    leafs = leaf_nodes(root);
    return leafs;
    
}
//return true if the tree is empty. Return false otherwise
bool BET::empty() {
    if (root == nullptr) return true;
    return false;
    
}



//all private must be implemented Recursively
//print to the standard output the corresponding infix expression. Note that you may need to add 
//parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
void BET::printInfixExpression(BinaryNode *n) {
    bool flag = false;
    if (n != nullptr) {
        //if left subtree has 5 or more elements then it will require a parenthesis
        if (size(n->left) >= 5) cout << "( ";
        if (size(n->left) > 1 && size(n->right) >= 5) cout << "( ";
        printInfixExpression(n->left);

        //closes aforementioned parenthesis for 5 or more subtree
        if (size(n->left) >= 5) cout << ") ";
        if (size(n->left) > 1 && size(n->right) >= 5) cout << ") ";
        cout << n->element << " ";
        //if right sub tree has an operator with greater than or equal to precedence than print open parenthesis
        if (n->right != nullptr && (n->element == "+" || n->element == "-" || n->element == "*" || n->element == "/") && 
            (n->right->element == "+" || n->right->element == "-" || n->right->element == "*" || n->right->element == "/") &&
            precedence(n->element) >= precedence(n->right->element)) {
            cout << "( ";
            flag = true;
        }

        printInfixExpression(n->right);
        //close parenthesis opened by right subtree with same or higher precedence
        if (flag) cout << ") ";

    }
    
}
//delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
void BET::makeEmpty(BinaryNode* &t) {
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
    
}


//clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.
BET::BinaryNode * BET::clone(BET::BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
}
//print to the standard output the corresponding postfix expression.
void BET::printPostfixExpression(BinaryNode *n) {
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    
    }
    
    
}
//return the number of nodes in the subtree pointed to by t
size_t BET::size(BinaryNode *t) {

    if (t == nullptr) return 0;
    if (t->left == nullptr && t->right == nullptr) return 1;
    return 1 + size(t->left) + size(t->right);
    
}
//return the number of leaf nodes in the subtree pointed to by t
size_t BET::leaf_nodes(BinaryNode *t) {
    
    if (t == nullptr) return 0;
    if (t->left == nullptr && t->right == nullptr) return 1;
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}
int BET::precedence(string op)
{
    switch (op[0]) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        cout << op << " is not valid";
        return 0;
    }

}