// kmir: a simple programming language made with c++

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "number.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

//global
bool verbose = false;
Context context = Context();

void parse_file(string, Context&);
void parse_line(string, Context&);
string print_token_list(Lexer*);

int main (int argc, char** argv) {

  if (argc > 3) {
    cout << "Too many arguments." << endl;
    return 1;
  }
  
  for (int i = 1; i < argc; ++i) {
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
        verbose = true;
      } else if (argv[i][0] != '-') {
        parse_file(argv[i], context);
      } else {
        cout << argv[i] << " not a valid argument." << endl;
      }
  }

  string line;
  //global symbols
  context.symbols.set("null", Token(TT_NULL, "null"));
  context.symbols.set("end", Token(TT_RES, "end"));
  context.symbols.set("end", Token(TT_RES, "ans"));
  
  cout << "CLIC VERSION 0.1" << endl;
  do {
    cout << "clic > ";
    getline(cin, line);

    parse_line(line, context);
    
  } while (line != "end");
  return 0;
}

void parse_file(string filename, Context& context) {
  string line;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      if (verbose)
        cout << line << '\n';
      parse_line(line, context);
    }
    myfile.close();
    exit(0);
  }

  else {
    cout << "Unable to open file\n";
    exit(0);
  }

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

void parse_line(string line, Context& context) {
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
  
  if (verbose)
    cout << print_token_list(lex) << endl; //outputs your string as a list of tokens and values
}