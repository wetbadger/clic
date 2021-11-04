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

using namespace std;

class Lexer {
    private:
        string text;
        Position position;
        int token_position =-1;
        char current_char;
        bool end_of_line = false;
        vector<Token> tokens;

        double string_to_float(string);
        bool isBig(string);
        Number make_number();
        int make_int(string);
        int get_dot_count(string);

    public:
        Lexer(string file_name, string file_text);
        void advance();
        void set_text(string text);
        void make_tokens();
        
        vector<Token> get_tokens();
};

#endif