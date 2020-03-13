#include <iostream>
#include <string>
#include <vector>
#include "token.h"

using namespace std;

//token的类型有：INT  FLOAT
//VAR
//DELIMITER
//OPERATOR


//公用常量

//特殊符号
vector<char> OPERATOR = {'+', '-', '*', '/', '='};
vector<char> DELIMITER = {'(', ')', ',', ';', '.'};
// vector<char> END = {'\r', '\n', '\f'};

//特殊函数名
vector<string> FUNCTIONS = {"write"};






//公用函数

//处理匹配数字开头的序列的函数
Token read_number(int &i, string line) {
    //常规整数
    int intValue = line[i] - 48;
    int j = i + 1;
    for ( ;isdigit(line[j]); j++, i++) {
        intValue = intValue * 10 + (line[j] - 48);
    }

    if (line[j] != '.') {
        return Token("INT", to_string(intValue));
    }

    j++;
    i++;
    // 扫描到小数点，尝试匹配小数
    double floatValue = intValue;
    float rate = 10;
    for (; isdigit(line[j]); j++, i++) {
        floatValue = floatValue + (line[j] - 48) / rate;
        rate *= 10;
    }
    return Token("FLOAT", to_string(floatValue));
}

//处理匹配变量名和函数名的函数
Token read_letter(int& i, string line) {
    int start = i;
    int j = i + 1;

    //识别特殊函数名

    //识别变量名
    int cnt = 1;
    for(; isalpha(line[j]); j++, i++) {
        cnt++;
    }
    return Token("VAR", line.substr(start, cnt));
}

Token read_delimiter(int& i, string line) {
    return Token("DELIMITER", line.substr(i, 1));
}

bool is_invector(char item, vector<char> &list) {
    for (auto i:list) {
        if (i == item) {
            return true;
        }
    }
    return false;
}



//非公用函数

//Token类内方法

Token::Token(string itype, string ivalue) {
    type = itype;
    value = ivalue;
}

void Token::show_type() {
    cout << type  << endl;
}

void Token::show_value() {
    cout << value << endl;
}

string Token::get_value() {
    return value;
}

string Token::get_type() {
    return type;
}


//Lexer类内方法

Lexer::Lexer() {
}


void Lexer::get_token(string line, vector<Token>& token_list) {
    Token i_token = Token(" ", " ");
    for (int i = 0; i < line.length(); i++) {
        //遇到数字，模式匹配
        if (isdigit(line[i])) {
            i_token = read_number(i, line);
        }
        //遇到字母，模式匹配
        else if (isalpha(line[i])) {
            i_token = read_letter(i, line);
        }
        //遇到操作符
        else if (is_invector(line[i], OPERATOR)) {
            i_token = Token("OPERATOR", line.substr(i, 1));
        }
        //遇到边界符
        else if (is_invector(line[i], DELIMITER)) {
            i_token = read_delimiter(i, line);
        }
        //遇到空格和句号以及其他，忽略
        else {
            continue;
        }
        token_list.push_back(i_token);
    }
}


void Lexer::test() {
    cout << "This is test!\n" << endl;
}


// //测试主函数
// int main() {
//     Lexer a = Lexer();
//     vector<Token> list;

//     a.get_token("b = a * 2 - a/2;", list);

//     for (auto i:list) {
//         string s = i.get_value();
//         cout << s << endl;
//     }

//     return 0;
// }



