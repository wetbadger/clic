#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <iostream>
#include "position.h"

using namespace std;

//copy-pasted from:
//https://riptutorial.com/cplusplus/example/23640/custom-exception

class Except: virtual public std::exception {
    
protected:

    int error_number;               ///< Error number
    int error_offset;               ///< Error offset
    int line_number;
    std::string error_message;      ///< Error message
    std::string file_name;
    std::string file_text;
    
public:

    /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     *  @param err_num Error number
     *  @param err_off Error offset
     *  @param file_name Filename or shell
     *  @param text Full text of line
     */
    explicit 
    Except(const std::string& msg = "Error", int err_num = 0, int err_off = 0, std::string f_name = "Unknown Error", std::string text = "An Error Occured", int ln_num = 0):
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
            <<"\n  Line: "<<e.getLine()
            <<": \""<<e.printLine()<<"\"\n"
            <<endl;
    }
}

#endif