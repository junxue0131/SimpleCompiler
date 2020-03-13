#include <string>
#include <iostream>


using namespace std;


void print_line() {
    extern int line;
    cout << "(ERROR)In line " + to_string(line) + ":"  << endl;
}


void type_error(string value, string c_type, string w_type) {
    print_line();
    cout << "type error: \"" + value  + "\" is not " + c_type + ", it's " + w_type << endl;
}


void use_key_word_error(string keyword) {
    print_line();
    cout << "use key word error: \"" + keyword + "\" is a key word, you can't use it." << endl;
}

void define_error(string var) {
    print_line();
    cout << "Syntax error: maybe define error: The defination of \"" + var + "\" is wrong." << endl;
}

void syntax_error() {
    print_line();
    cout << "Syntax error." << endl;
}

void undefined_error(string name) {
    print_line();
    cout << "undefined error: \"" + name + "\" is undefined." << endl;
}

void lack_semicolon() {
    print_line();
    cout << "Syntax error: maybe lack_semicolon error." << endl;
}

void not_assigned_error(string name) {
    print_line();
    cout << "not assigned error: \"" + name + "\" is not assigned." << endl;
}

// int main() {
//     // type_error("23", "INT", "FLOAT");
//     // use_key_word_error("int");
//     define_error("abc");
//     return 0;
// }