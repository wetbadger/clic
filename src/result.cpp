#include "result.h"

Result::Result() {

}

Result::~Result() {

}

string Result::record(Result result) {
    return result.value;
}

Result Result::success(string) {

}

Result Result::failure(string) {

}