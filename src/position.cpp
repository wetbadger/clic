#include "position.h"

Position::Position() {

}

Position::Position(int index, int line, int column, string file_name, string file_text) {
    this->index = index;
    this->line = line;
    this->column = column;
    this->file_name = file_name;
    this->file_text = file_text;
}

void Position::advance(char current_char) {
    index++;
    column++;

    if (current_char == '\n') {
        line++;
        column=0;
    }
}

Position Position::copy() {
    return Position(index, line, column, file_name, file_text);
}

int Position::get_index() {
    return index;
}

int Position::get_column() {
    return column;
}

string Position::get_file_name() {
    return file_name;
}

string Position::get_file_text() {
    return file_text;
}