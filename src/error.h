#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <iostream>
#include "position.h"

using namespace std;

//copy-pasted from:
//https://riptutorial.com/cplusplus/example/23640/custom-exception

class Except: virtual public exception {
    
protected:

    int error_number;               ///< Error number
    int error_offset;               ///< Error offset
    int line_number;
    string error_message;      ///< Error message
    string file_name;
    string file_text;
    
public:

    explicit 
    Except(const string& msg = "Error", int err_num = 0, int err_off = 0, string f_name = "Unknown Error", string text = "An Error Occured", int ln_num = 0):
        error_number(err_num),
        error_offset(err_off),
        error_message(msg),
        line_number(ln_num),
        file_name(f_name),
        file_text(text)
        {}

    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~Except() throw () {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char* what() const throw () {
       return error_message.c_str();
    }
    
    /** Returns error number.
     *  @return #error_number
     */
    virtual int getErrorNumber() const throw() {
        return error_number;
    }
    
    /**Returns error offset.
     * @return #error_offset
     */
    virtual int getErrorOffset() const throw() {
        return error_offset;
    }

    virtual string getFilename() const throw() {
        return file_name;
    }

    virtual int getLine() const throw() {
        return line_number;
    }

    virtual string printLine() const throw() {
        return file_text;
    }

};
//Exceptions
static void too_many_dots_error(string num_string, Position position) {
    string spaces = "";
        for (int i = 0; i < num_string.length(); i++) {
            spaces += " ";
        }
    try {
        throw(Except("\nParseError: I was trying to parse a number, then I saw this \""+num_string+".\" and got confused.\n" + 
                        "                                                             " + spaces +  "^", 1, position.get_column()+1, 
                        position.get_file_name(), position.get_file_text()));
    } catch (const Except& e) {
        std::cout<<e.what()
            <<"\n  Err "<<e.getErrorNumber()
            <<" - Column: "<<e.getErrorOffset()
            <<"\n  File name: "<<e.getFilename()
            <<"\n  Line "<<e.getLine()
            <<": \""<<e.printLine()<<"\"\n"
            <<endl;
    }
}

static void right_parenthesis_error(Position position) {

    try {
        throw(Except("\nParseError: Expected a right parenthesis somewhere.\n", 
                        2, position.get_column()+1, 
                        position.get_file_name(), position.get_file_text()));
    } catch (const Except& e) {
        std::cout<<e.what()
            <<"\n  Err "<<e.getErrorNumber()
            <<" - Column: "<<e.getErrorOffset()
            <<"\n  File name: "<<e.getFilename()
            <<"\n  Line "<<e.getLine()
            <<": \""<<e.printLine()<<"\"\n"
            <<endl;
    }
}

static void left_parenthesis_error(Position position) {

    try {
        throw(Except("\nParseError: Expected a left parenthesis somewhere.\n", 
                        3, position.get_column()+1, 
                        position.get_file_name(), position.get_file_text()));
    } catch (const Except& e) {
        std::cout<<e.what()
            <<"\n  Err "<<e.getErrorNumber()
            <<" - Column: "<<e.getErrorOffset()
            <<"\n  File name: "<<e.getFilename()
            <<"\n  Line "<<e.getLine()
            <<": \""<<e.printLine()<<"\"\n"
            <<endl;
    }
}

static void operator_missing_function(string op) {
    Position position = Position(0, 0, 0, "", "");
     try {
        throw(Except("\nProgrammerError: Operator not given a function.\n", 
                        3, position.get_column()+1, 
                        position.get_file_name(), position.get_file_text()));
    } catch (const Except& e) {
        std::cout<<e.what()
            <<"\n  Err "<<e.getErrorNumber()
            <<" - Column: "<<e.getErrorOffset()
            <<"\n  File name: "<<e.getFilename()
            <<"\n  Line "<<e.getLine()
            <<": \""<<e.printLine()<<"\"\n"
            <<endl;
    }
}


#endif