#include "interpreter.h"

Interpreter::Interpreter() {

}
Token Interpreter::visit(Node* node, Context& context) {
    vector<TT> operations = {TT_PLUS, TT_MINUS, TT_MUL, TT_DIV, TT_POW};
    vector<TT> numbers = {TT_INT, TT_FLOAT};
    Number n;
    Token t;
    Token token = node->token;
    if (count(operations.begin(), operations.end(), token.get_type())) {
        if (node->right->get_token().get_type() != TT_UNARY) {
            n = visit_BinaryOperationNode(node, context);
            if (!n.get_errors().empty()) {
                string err_message = "\n";
                for (string e : n.get_errors())
                    err_message += e + "\n";
                return Token(TT_ERR, err_message);
            }
            Token new_number = Token();
            if (node->right->get_token().get_type() == TT_FLOAT)
                new_number.set(TT_FLOAT);
            else
                new_number.set(TT_INT);
            new_number.set_value(n.get_value());
            node->set_token(new_number);
        } else {
            n = visit_UnaryNode(node, context);
        }
        t = Token(n);
        return t;
    }
    if (count(numbers.begin(), numbers.end(), token.get_type())) {
        n = visit_NumberNode(node, context);
        t = Token(n);
        return t;
    }
    if (token.get_type() == TT_ASSIGN) {
        t = visit_VariableAssignmentNode(node, context);
        return t;
    }
    if (token.get_type() == TT_WORD) {
        t = visit_VariableAccessNode(node, context);
        return t;
    }
    return t;
}
void Interpreter::no_visit_method(Node* node, Context context) {
    //raise exception
}
Number Interpreter::visit_NumberNode(Node* node, Context context) {
    //cout << "Found NumberNode " << node->get_token().get_value() << endl;
    int dtcnt = 0;
    if (node->token.get_type() == TT_FLOAT) {
       dtcnt = 1;
    }
    return Number(node->token.get_value(), dtcnt);
}
Number Interpreter::visit_BinaryOperationNode(Node* node, Context context) {
    //cout << "Found BinaryOperationNode " << endl;
    int d1 = 0; //dot_count
    int d2 = 0;

    Token l = visit(node->left, context);
    Token r = visit(node->right, context);

    vector<string> errors;

    if (l.get_type() == TT_ERR) {
        errors.push_back(l.get_value());
    }
    if (r.get_type() == TT_ERR) {
        errors.push_back(r.get_value());
    }
    if (!errors.empty()) {
        return Number("NaN", errors);
    }

    //force token to be a number
    if (node->left->get_token().get_type() == TT_WORD) {
        string var_name = node->left->get_token().get_value();
        auto it = context.symbols.get_symbols().find(var_name);
        node->left->set_token(it->second);
    }
    if (node->right->get_token().get_type() == TT_WORD) {
        string var_name = node->right->get_token().get_value();
        auto it = context.symbols.get_symbols().find(var_name);
        node->right->set_token(it->second);
    }

    if (node->left->get_token().get_type() == TT_FLOAT) {
        d1 = 1;
        d2 = 1;
        node->right->get_token().set_type(TT_FLOAT);
    }
    if (node->right->get_token().get_type() == TT_FLOAT) {
        d2 = 1;
        d1 = 1;
        node->left->get_token().set_type(TT_FLOAT);
    }

    Number num1, num2;
    num1 = Number(node->left->get_token().get_value(), d1);
    num2 = Number(node->right->get_token().get_value(), d2);
    
    switch (node->token.get_type()) {
        case TT_PLUS:
            return num1.added_to(num2);
        case TT_MINUS:
            return num1.subtracted_from(num2);
        case TT_MUL:
            return num1.multiplied_by(num2);
        case TT_DIV:
            return num1.divided_by(num2);
        case TT_POW:
            return num1.power_of(num2);
        default:
            operator_missing_function(node->token.get_value());
            return Number("0",0);
    }
}

Number Interpreter::visit_UnaryNode(Node* node, Context context) {
    //cout << "Found UnaryNode" << endl;

    Token t = visit(node->left, context);
    Number n;
    if (t.get_type() == TT_FLOAT)
        n = Number(t.get_value(), 1);
    else
        n = Number(t.get_value(), 0);

    if (node->get_token().get_type() == TT_MINUS) {
        n.set_value("-"+n.get_value()); //.multiplied_by(Number("-1", n.get_dot_count()));
        Token new_number = Token();
        if (n.get_dot_count() == 1)
            new_number.set(TT_FLOAT);
        else
            new_number.set(TT_INT);
        new_number.set_value(n.get_value());
        node->set_token(new_number);
    }

    return n;
}

Token Interpreter::visit_VariableAccessNode(Node* node, Context context) {
    string var_name = node->get_token().get_value();
    Token value = context.symbols.get(var_name);

    return value;
}

Token Interpreter::visit_VariableAssignmentNode(Node* node, Context& context) {
    string var_name = node->left->get_token().get_value();
    Token value = node->right->get_token();
    context.symbols.set(var_name, value);
    return value;
}

SymbolTable::SymbolTable() {

}

map<string, Token> SymbolTable::get_symbols() {
    return symbols;
}

Token SymbolTable::get (string name) {
    if (has_parent) {
        return parent->get(name);
    }
    auto it = symbols.find(name);
    if (it->first == "") {
        
        NameError* err = new NameError(
            "NameError", 
            "Variable not defined.");
        Token name_error = err->tokenize();
        return name_error;
        
    }
    return it->second;
}

void SymbolTable::set(string name,  Token value) {
    symbols.insert(pair<string, Token>(name, value));
}

void SymbolTable::remove(string name) {
    symbols.erase(name);
}
