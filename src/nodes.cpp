#include "nodes.h"
#include <iostream>
using namespace std;

Token Node::get_token() {
    return this->token;
}

void Node::set_token(Token token) {
    this->token = token;
}

NumberNode::NumberNode(Token token) {
    this->token = token;
}

BinaryOperationNode::BinaryOperationNode(Token token, Node* left, Node* right) {
    this->token = token;
    this->left = left;
    this->right = right;
}

UnaryNode::UnaryNode(Token token, Node* node) {
    this->token = token;
    this->left = node;
}