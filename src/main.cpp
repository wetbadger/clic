// kmir: a simple programming language made with c++

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "number.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void parse_file(string filename) {
  string line;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

}

string print_token_list(Lexer* lex) {
  string type_array = "[";
  for (int i = 0; i < lex->get_tokens().size(); i++) {
    string token = lex->get_tokens()[i].to_string();
    if (token != "END") {
      if (i > 0) {
        type_array += ", ";
      }
      type_array += token;
    } else {
      break;
    }
  }
  type_array += ']';
  return type_array;
}

int main () {
  string line;
  Context context = Context();
  //global symbols
  context.symbols.set("null", Token(TT_NULL, "null"));
  
  cout << "CLIC VERSION 0.0" << endl;
  do {
    cout << "clic > ";
    getline(cin, line);
    Lexer *lex = new Lexer("shell", line);
    //generate tokens
    lex->make_tokens();

    //generate Abstract Syntax Tree
    Parser *parser = new Parser(lex->get_tokens(), context.symbols.get_symbols());
    Node* ast = parser->parse();

    //Run Program
    Interpreter *interpreter = new Interpreter();
    Token result = interpreter->visit(ast, context);

    cout << result.get_value() << endl;
    
    cout << print_token_list(lex) << endl; //outputs your string as a list of tokens and values
  } while (line != "end");
  return 0;
}