#ifndef NODES_H
#define NODES_H

#include "token.h"
 
struct Node {
    Token token;
    struct Node* left;
    struct Node* right;
    Token get_token();
    void set_token(Token token);
};

class NumberNode : public Node {
    public:
        NumberNode(Token token);
};

class BinaryOperationNode : public Node {
    public:
        BinaryOperationNode(Token key, Node* left, Node* right);
};

class UnaryNode : public Node {
    public:
        UnaryNode(Token unary, Node* node);
};

#endif