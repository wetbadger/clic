#include "lexer.h"

Lexer::Lexer(string file_name, string file_text) {
    position = Position(-1, 0, -1, file_name, file_text);
    text = file_text;
}

void Lexer::advance() {
    position.advance(current_char);
    if (position.get_index() < text.size()) {
        current_char = text.at(position.get_index());
    } else {
        end_of_line = true;
    }
}

void Lexer::set_text(string text) {
    this->text = text;
}

void Lexer::make_tokens() {

    while (!end_of_line) {
        if (isspace(current_char)) {
            advance();
            continue;
        }
        if (isdigit(current_char)) {
            token_position++;
            Number number = make_number();
            Token t = Token();
            if (number.get_dot_count() == 0) {
                t.set(TT_INT);
                int integer = number.make_int();
                t.set_value(integer);
                t.set_value(number.isInt());

            } else {
                t.set(TT_FLOAT);
                t.set_value(false); //!isInt
            }
            t.set_value(number.get_value());
            tokens.push_back(t);
            continue;
        }
        Token t = Token();
        switch (current_char)  {
            case '+':
            {
                t.set(TT_PLUS);
                break;
            }
            case '-':
            {
                t.set(TT_MINUS);
                break;
            }
            case '*':
            {
                t.set(TT_MUL);
                break;
            }
            case '/':
            {
                t.set(TT_DIV);
                break;
            }
            case '^':
            {
                t.set(TT_POW);
                break;
            }
            case '(':
            {
                t.set(TT_LPAREN);
                break;
            }
            case ')':
            {
                t.set(TT_RPAREN);
                break;
            }
            case '[':
            {
                t.set(TT_LBRAK);
                break;
            }
            case ']':
            {
                t.set(TT_RBRAK);
                break;
            }
            default:
            {
                t.set(TT_NULL);
            }
        }
        tokens.push_back(t);
        token_position++;
        advance();
    }
}

Number Lexer::make_number() {
    //Token number;
    string num_string = "";
    int dot_count = 0;

    while (current_char != ' ' 
    && isdigit(current_char) 
    || current_char == '.') {
        if (end_of_line) {
            break;
        }

        if (current_char == '.') {
            if (dot_count > 0) {
                //error here. (number has 2 dots)
                Position p_copy = position.copy();
                too_many_dots_error(num_string, p_copy);
                num_string = "";
                break; 
            }
            dot_count += 1;
            num_string.push_back(current_char);
        } else {
            num_string.push_back(current_char);
        }
        
        advance();
    }
    Number number = Number(num_string, dot_count);
    return number;
}

vector<Token> Lexer::get_tokens() {
    return tokens;
}