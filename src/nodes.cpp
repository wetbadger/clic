#include "nodes.h"
#include <iostream>
using namespace std;

NumberNode::NumberNode(Token token) {
    this->token = token;
    cout << token.get_value() << endl;
}

BinaryOperationNode::BinaryOperationNode(Token token, Node* left, Node* right) {
    this->token = token;
    this->left = left;
    this->right = right;
    cout << token.get_type() << endl;
    
}