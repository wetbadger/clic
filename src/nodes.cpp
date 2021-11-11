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
    /*if (token.get_type() == TT_MINUS) {
        Number num1 = Number(left->get_token().get_value(), 0);
        Number num2 = Number("-1", 0);
        Token negative = Token(TT_INT, num1.multiplied_by(num2).get_value());
        this->right = new NumberNode(negative);
    } else { */
    this->right = new Node(Token(TT_UNARY, "-1"));
    //}
}