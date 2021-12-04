#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "nodes.h"
#include "number.h"
#include "result.h"

using namespace std;

class Interpreter {
    public:
        Interpreter();
        Number visit(Node*);
        void no_visit_method(Node*);
        Number visit_NumberNode(Node*);
        Number visit_BinaryOperationNode(Node*);
        Number visit_UnaryNode(Node*);
};

class SymbolTable {
    private:
        map<Token, Token> symbols;
        map<Token, Token> global_symbols;
    public:
        SymbolTable();
        map<Token, Token> get(Token name);
};

#endif