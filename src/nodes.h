#include "token.h"
 
struct Node {
    Token token;
    struct Node* left;
    struct Node* right;
};

class NumberNode : public Node {
    public:
        NumberNode(Token token);
};

class BinaryOperationNode : public Node {
    public:
        BinaryOperationNode(Token key, Node* left, Node* right);
        void insert(Token key); //insert a node
        Node *search(Token key); //search a value
        void print(); //print the tree
        Node *root; //pointer to a root element

};