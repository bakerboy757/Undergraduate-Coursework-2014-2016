#ifndef BET_H
#define BET_H
#include <string>
#include <iomanip>
#include <stack>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class BET {

private:
    struct BinaryNode {
        string element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const string& d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
            : element{ d }, left{ l }, right{ r } {}
        BinaryNode(string&& d, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
            : element{ std::move(d) }, left{ l }, right{ r } {}

    };
    BinaryNode* root;
public:
    //default
    BET();
    // one-parameter constructor, where parameter "postfix" is string containing a postfix expression. 
    //The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space.
    BET(const string postfix);
    //copy construct
    BET(const BET&);
    ~BET();
    /*parameter "postfix" is string containing a postfix expression. The tree should be built based on the
    postfix expression. Tokens in the postfix expression are separated by space. If the tree contains nodes
    before the function is called, you need to first delete the existing nodes. Return true if the new tree is built
    successfully. Return false if an error is encountered.*/
    bool buildFromPostfix(const string postfix);
    //assignment operator
    const BET & operator= (const BET &);
    //call the private version of the printInfixExpression function to print out the infix expression.
    void printInfixExpression();
    // call the private version of the printPostfixExpression function to print out the postfix expression
    void printPostfixExpression();
    //call the  private version of the size function to return the number of nodes in the tree.
    size_t size();
    //call the private version of the leaf_nodes function to return the number of leaf nodes in the tree.
    size_t leaf_nodes();
    //return true if the tree is empty. Return false otherwise
    bool empty();
	int precedence(string op);
    //all private must be implemented Recursively

private:
    //print to the standard output the corresponding infix expression. Note that you may need to add 
    //parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
    void printInfixExpression(BinaryNode *n);
    //delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
    void makeEmpty(BinaryNode* &t);
    //clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.
    BinaryNode * clone(BinaryNode *t) const;
    //print to the standard output the corresponding postfix expression.
    void printPostfixExpression(BinaryNode *n);
    //return the number of nodes in the subtree pointed to by t
    size_t size(BinaryNode *t);
    //return the number of leaf nodes in the subtree pointed to by t
    size_t leaf_nodes(BinaryNode *t);
    //variables
    size_t theSize;
    size_t leafs;
    
    
    
};

#endif
