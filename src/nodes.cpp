#include "nodes.h"
#include <iostream>
using namespace std;

NumberNode::NumberNode(Token token) {
    this->token = token;
}

BinaryOperationNode::BinaryOperationNode(Token token, Node* left, Node* right) {
    this->token = token;
    this->left = left;
    this->right = right;
}

Token Node::get_token() {
    return this->token;
}

void Node::set_token(Token token) {
    this->token = token;
}