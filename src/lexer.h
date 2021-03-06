#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "number.h"
#include "error.h"
#include "position.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <stack>

using namespace std;

class Lexer {
    private:
        string text;
        Position position;
        int token_position =-1;
        char current_char = 0;
        bool end_of_line = false;
        vector<Token> tokens;

        double string_to_float(string);
        bool isBig(string);
        Number make_number();
        string make_a_word();
        int make_int(string);
        int get_dot_count(string);

        stack<char> p_stack;

    public:
        Lexer(string file_name, string file_text);
        void advance();
        void set_text(string text);
        void make_tokens();
        
        vector<Token> get_tokens();
};

#endif