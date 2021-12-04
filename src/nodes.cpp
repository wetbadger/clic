#include "nodes.h"
#include <iostream>
using namespace std;

Node::Node() {

}

Node::Node(Token token) {
    this->token = token;
}

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
    this->right = new Node(Token(TT_UNARY, "-1"));
}

VariableAccessNode::VariableAccessNode(Token word) {
    this->token = word;
}

AssignmentNode::AssignmentNode(string word, Node* value) {
    this->token = Token(TT_ASSIGN, "=");
    this->left = new Node(Token(TT_WORD, word));
    this->right = value;
}