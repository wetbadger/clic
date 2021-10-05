#include <exception>
#include <iostream>

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
    Except(const std::string& msg, int err_num, int err_off, std::string f_name, std::string text, int ln_num = 0):
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