#include "interpreter.h"
#include "number.h"

Interpreter::Interpreter() {

}
Number Interpreter::visit(Node* node) {
    vector<TT> operations = {TT_PLUS, TT_MINUS, TT_MUL, TT_DIV, TT_POW};
    vector<TT> numbers = {TT_INT, TT_FLOAT};
    Number n;
    Token token = node->token;
    if (count(operations.begin(), operations.end(), token.get_type())) {
        if (node->right->get_token().get_type() != TT_UNARY) {
            n = visit_BinaryOperationNode(node);
            Token new_number = Token();
            if (node->right->get_token().get_type() == TT_FLOAT)
                new_number.set(TT_FLOAT);
            else
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
    int dtcnt = 0;
    if (node->token.get_type() == TT_FLOAT) {
       dtcnt = 1;
    }
    return Number(node->token.get_value(), dtcnt);
}
Number Interpreter::visit_BinaryOperationNode(Node* node) {
    //cout << "Found BinaryOperationNode " << endl;
    int d1 = 0; //dot_count
    int d2 = 0;

    visit(node->left);
    visit(node->right);

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
    }
}
Number Interpreter::visit_UnaryNode(Node* node) {
    //cout << "Found UnaryNode" << endl;

    Number n = visit(node->left);

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

