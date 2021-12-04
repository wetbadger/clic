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

class SymbolTable {
    private:
        map<string, Token> symbols;
        SymbolTable* parent;
        bool has_parent = false;
    public:
        SymbolTable();
        map<string, Token> get_symbols();
        Token get(string name);
        void set(string name, Token value);
        void remove(string name);
};

struct Context {
    SymbolTable symbols;
};

class Interpreter {
    public:
        Interpreter();
        Token visit(Node*, Context&);
        void no_visit_method(Node*, Context);
        Number visit_NumberNode(Node*, Context);
        Number visit_BinaryOperationNode(Node*, Context);
        Number visit_UnaryNode(Node*, Context);
        Token visit_VariableAccessNode(Node*, Context);
        Token visit_VariableAssignmentNode(Node*, Context&);
};

#endif