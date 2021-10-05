#include <iostream>
using namespace std;

class Position {
    private:
        int index, line, column;
        string file_name, file_text;
    public:
        Position();
        Position(int index, int line, int column, string file_name, string file_text);
        void advance(char current_char);
        Position copy();
        int get_index();
        int get_column();
        string get_file_name();
        string get_file_text();

};