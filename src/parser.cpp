#include "parser.h"



Parser::Parser(vector<Token> tokens, map<string, Token> symbols) {
    this->tokens = tokens;
    token_index = 0;
    current_token = tokens[token_index];
    this->symbols = symbols;
    advance();
}

void Parser::advance() {
    token_index ++;
    if (token_index < tokens.size()) {
        current_token = tokens[token_index];
    } else {
        current_token.set_type(TT_END);
    }
}

Token Parser::peek() {
    Token t;
    if (token_index+1 < tokens.size())
        t = tokens[token_index+1];
    else
        t = Token(TT_NULL, "null");
    return t;
}

Node* Parser::parse() {
    while (current_token.get_type() == TT_NULL) {
        advance();
    }
    return expression();
}

Node* Parser::atom() {
    Token token = current_token;

    if (token.get_type() == TT_PLUS || token.get_type() == TT_MINUS) {
        advance();
        Node* fctr = atom();
        return new UnaryNode(token, fctr);
    } 

    if (token.get_type() == TT_INT || token.get_type() == TT_FLOAT) {
        advance();
    }
    if (token.get_type() == TT_WORD) {
        advance();
        return new VariableAccessNode(token);
    }
    if (token.get_type() == TT_LPAREN) {
        advance();
        Node* expr = expression();
        if (current_token.get_type() == TT_RPAREN) {
            advance();
            return expr;
        } //parenthesis error caught by lexer
    }
    
    return new NumberNode(token);
}

Node* Parser::power() {
    vector<TT> operations;
    operations.push_back(TT_POW);
    return binary_operation([this]() { return atom(); }, operations);
}

Node* Parser::factor() {
    Token token = current_token;
    if (token.get_type() == TT_PLUS || token.get_type() == TT_MINUS) {
        advance();
        Node* fctr = factor();
        return new UnaryNode(token, fctr);
    } 

    return power();
}

Node* Parser::term() {
    vector<TT> operations{TT_MUL, TT_DIV};
    return binary_operation([this]() { return factor(); }, operations);
}

Node* Parser::expression() {
    if (current_token.get_type() == TT_WORD) {
        var_name = current_token.get_value(); 
        if (peek().get_type() == TT_ASSIGN) {
            advance(); advance();
            Node* expr = expression();
            return new AssignmentNode(var_name, expr);
        }
    }
    vector<TT> operations{TT_PLUS, TT_MINUS};
    return binary_operation([this]() { return term(); }, operations);
}

Node* Parser::binary_operation(function<Node* ()> func, vector<TT> operations) {
    Node* left = func();
    Token root_token;

    while (count(operations.begin(), operations.end(), current_token.get_type())) {
        root_token = current_token;
        advance();
        
        Node* right = func();
        left = new BinaryOperationNode(root_token, left, right);
    }
    return left;
}