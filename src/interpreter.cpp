#include "interpreter.h"
#include "number.h"

Interpreter::Interpreter() {

}
string Interpreter::visit(Node* node) {
    method_name = "TODO: set method name.";
    vector<TT> operations = {TT_PLUS, TT_MINUS, TT_MUL, TT_DIV};
    vector<TT> numbers = {TT_INT, TT_FLOAT};
    if (count(operations.begin(), operations.end(), node->token.get_type())) {
        visit_BinaryOperationNode(node);
    }
    if (count(numbers.begin(), numbers.end(), node->token.get_type())) {
        visit_NumberNode(node);
    }
    return method_name;
}
void Interpreter::no_visit_method(Node* node) {
    //raise exception
}
Number Interpreter::visit_NumberNode(Node* node) {
    cout << "Found NumberNode" << endl;
    return Number(node->token.get_value(), 0);
}
Number Interpreter::visit_BinaryOperationNode(Node* node) {
    cout << "Found BinaryOperationNode" << endl;
    Number num1, num2;
    visit(node->left);
    visit(node->right);
    switch (node->token.get_type()) {
        case TT_PLUS:
            num1 = Number(node->left->token.get_value(), 0);
            num2 = Number(node->right->token.get_value(), 0);
            return num1.added_to(num2);
        case TT_MINUS:
        case TT_MUL:
        case TT_DIV:
        default:
            cout << "Operator not given functionality yet. TODO: add error here." << endl;
    }
}
void Interpreter::visit_UnaryNode(Node* node) {
    cout << "Found UnaryNode" << endl;
}