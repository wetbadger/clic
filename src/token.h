#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

enum TT {
    TT_END,
    TT_BOOL,
    //math stuff
    TT_PLUS, 
    TT_MINUS,
    TT_MUL,
    TT_DIV,
    TT_POW,
    TT_INT,
    TT_FLOAT,
    TT_LPAREN,
    TT_RPAREN,
    //array stuff
    TT_LBRAK,
    TT_RBRAK,
    TT_NULL
    };

class Token {
    private:
        string name = "Token";
    
    protected:
        TT type;
        //int_value and bool_value can represent the state of the Token
        int int_value;
        bool bool_value;
        string value; //store actual value as a string whether int, char or whatever
        //T value; //Using generics like this turned out to be a nightmare
    public:
        Token();
        void set(TT);
        void set_value(int);
        void set_value(bool);
        void set_value(string);
        //void set_value(void*);
        int get_int_value(); 
        bool get_bool_value();
        string get_value();
        //T get_value();
        void set_type(TT);
        TT get_type();
        virtual string get_name();
        virtual string to_string();
};

//token2 allows programmer to tokenize generic values
template <typename T> class Token2 : public Token {     
    private:
        T value; 
        string name = "Token2";
    public:
        void set_value(T value) {
            this->value = value;
            cout << value << endl;
        } 
        void get_value() const {
            return value;
        }
        virtual string get_name() {
            return "Token2";
        }

};

#endif