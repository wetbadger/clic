#include "token.h"
#include "nodes.h"
#include "number.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

class Parser {
    private:
        Token current_token;
        vector<Token> tokens;
        int token_index = -1;
    public:
        Parser(vector<Token> tokens);
        void advance();
        Node* parse();
        Node* atom();
        Node* power();
        Node* factor();
        Node* term();
        Node* expression();
        Node* binary_operation(std::function<Node* ()> func, vector<TT> operations);
};