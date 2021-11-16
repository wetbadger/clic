#include "interpreter.h"
#include "number.h"

Interpreter::Interpreter() {

}
Number Interpreter::visit(Node* node) {
    method_name = "TODO: set method name.";
    vector<TT> operations = {TT_PLUS, TT_MINUS, TT_MUL, TT_DIV, TT_POW};
    vector<TT> numbers = {TT_INT, TT_FLOAT};
    Number n;
    Token token = node->token;
    if (count(operations.begin(), operations.end(), token.get_type())) {
        if (node->right->get_token().get_type() != TT_UNARY) {
            n = visit_BinaryOperationNode(node);
            Token new_number = Token();
            new_number.set(TT_INT);
            new_number.set_value(n.get_value());
            node->set_token(new_number);
        } else {
            n = visit_UnaryNode(node);
        }
        return n;
    }
    if (count(numbers.begin(), numbers.end(), token.get_type())) {
        n = visit_NumberNode(node);
        return n;
    }
}
void Interpreter::no_visit_method(Node* node) {
    //raise exception
}
Number Interpreter::visit_NumberNode(Node* node) {
    //cout << "Found NumberNode " << node->get_token().get_value() << endl;
    return Number(node->token.get_value(), 0);
}
Number Interpreter::visit_BinaryOperationNode(Node* node) {
    //cout << "Found BinaryOperationNode " << endl;
    
    visit(node->left);
    visit(node->right);

    Number num1, num2;
    num1 = Number(node->left->get_token().get_value(), 0);
    num2 = Number(node->right->get_token().get_value(), 0);
    
    switch (node->token.get_type()) {
        case TT_PLUS:
            return num1.added_to(num2);
        case TT_MINUS:
            return num1.subtracted_from(num2);
        case TT_MUL:
            return num1.multiplied_by(num2);       
        case TT_POW:
            return num1.power_of(num2);
        default:
            cout << "Operator not given functionality yet. TODO: add error here." << endl;
    }
}
Number Interpreter::visit_UnaryNode(Node* node) {
    //cout << "Found UnaryNode" << endl;
    Number n = visit(node->left);

    if (node->get_token().get_type() == TT_MINUS) {
        n = n.multiplied_by(Number("-1", 0));
        Token new_number = Token();
        new_number.set(TT_INT);
        new_number.set_value(n.get_value());
        node->set_token(new_number);
    }

    return n;
}