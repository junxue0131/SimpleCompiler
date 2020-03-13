#include <iostream>
#include<typeinfo>
#include <string>
#include <vector>
#include "parser.h"


using namespace std;

//公用常量
vector<string> ALL_KEY_WORDS = {"int", "float", "write"};
vector<var_table> VAR_TABLE = {};


//公用函数
bool is_keyword(string w) {
    for (auto i:ALL_KEY_WORDS) {
        if (i == w) {
            return true;
        }
    }
    return false;
}

void test_table() {
    for (auto i:VAR_TABLE) {
        cout << i.get_name() << endl;
        cout << i.get_value() << endl;
        cout << i.type << endl;
    }
}

void test_token(vector<Token>::iterator token_i, vector<Token>::iterator end) {
    while (token_i != end) {
        Token t = *token_i;
        cout << t.value << endl;
        token_i++;
    }
}

var_table find_var(string name) {
    for (auto i:VAR_TABLE) {
        if (name == i.get_name()) {
            return i;
        }
    }
    //错误处理：未定义该变量
    undefined_error(name);
    exit(1);
}

void var_to_num(vector<Token>::iterator token_i, vector<Token>::iterator end) {
    while (token_i != end) {
        Token t = *token_i;
        if (t.get_type() == "VAR") {
            var_table tt = find_var(t.get_value());
            // cout << tt.name << endl;
            // cout << tt.value << endl;
            // cout << tt.type << endl;
            (*token_i).value = tt.value;
            (*token_i).type = tt.type;
            // cout << "test" << endl;
            // cout << (*token_i).value << endl;
            // cout << (*token_i).type << endl;
        }
        token_i++;
    }
}


var_table::var_table(Token var, string v, string t) {
    name = var.get_value();
    value = v;
    type = t;
}

string var_table::get_name() {
    return name;
}

string var_table::get_value() {
    return value;
}


void set_value(string name, string v) {
    for (auto i = VAR_TABLE.begin(); i != VAR_TABLE.end(); i++) {
        var_table t = *i;
        if (name == t.get_name()) {
            (*i).value = v;
            return;
        }
    }
    undefined_error(name);
}



//处理语法单元的函数
float expr(vector<Token>::iterator &token_i, vector<Token>::iterator end);


int num_int(vector<Token>::iterator& t) {
    Token tt = *t;
    //错误处理：类型错误
    if (tt.get_type() != "INT" && tt.get_type() != "int") {
        type_error(tt.get_value(), "INT", tt.get_type());
        exit(1);
    }
    //错误处理：未赋值
    if (tt.get_value() == "NULL") {
        not_assigned_error(tt.get_value());
        exit(1);
    }
    t++;
    return stoi(tt.get_value(), 0, 10);
}

float num_float(vector<Token>::iterator& t) {
    Token tt = *t;
    t++;
    return stof(tt.get_value(), 0);
}

char oprate(vector<Token>::iterator t) {
    Token tt = *t;
    char op = tt.get_value()[0];
    return op;
}

string var(vector<Token>::iterator t) {
    Token tt = *t;
    string var = tt.get_value();
    return var;
}




float factor(vector<Token>::iterator &token_i, vector<Token>::iterator end) {
    float res;

    char op = oprate(token_i);    
    if (op == '(') { 
        token_i++;
        res = expr(token_i ,end);
        char op = oprate(token_i);
        if (op == ')') {  
            token_i++;
        }
    } else {
        Token t = *token_i;
        auto type = t.get_type();
        if (type == "INT" || type == "int") {
            res = num_int(token_i);
        } else if (type == "FLOAT" || type == "float") {
            res = num_float(token_i);
        }   
    }
    // cout << "factor:" << endl;
    // cout << res << endl;

    return float(res);
}


float term(vector<Token>::iterator &token_i, vector<Token>::iterator end) {
    float res = factor(token_i, end);

    char flag = oprate(token_i);

    while(flag == '*' || flag == '/') {
        char op = oprate(token_i);
        token_i++;
        if (op == '*') {
            res *= factor(token_i, end);
        } else {
            res /= factor(token_i, end);
        }
        if (token_i == end) {
            break;
        }
        flag = oprate(token_i);
    }

    // cout << "term:" << endl;
    // cout << res << endl;

    return float(res);
}


float expr(vector<Token>::iterator &token_i, vector<Token>::iterator end) {
    float res = term(token_i, end);

    if (token_i == end) {
        return float(res);
    }
    char flag = oprate(token_i);

    while((flag == '+' || flag == '-') && token_i != end) {
        char op = oprate(token_i);
        token_i++;
        if (op == '+') {
            res += term(token_i, end);
        } else{
            res -= term(token_i, end);
        }
        if (token_i == end) {
            break;
        }
        flag = oprate(token_i);
    }
    // cout << "expr:" << endl;
    // cout << res << endl;
    return float(res);
}




bool declaration(vector<Token>::iterator &token_i, string type) {
    token_i++;
    Token t = *token_i;
    string v = var(token_i);
    //错误处理:使用关键字做变量名
    if (is_keyword(v)) {
        use_key_word_error(v);
        exit(1);
    }
    if (t.get_type() == "VAR") {
        token_i++;
        v = var(token_i);
        if (v == ";") {
            var_table item = var_table(t, "NULL", type);
            VAR_TABLE.push_back(item);
            token_i++;
            return true;
        } else if (v == ".") {
            //遇到终结符号，推出程序
            exit(1);
        } else {
            //错误处理：定义语句语法错误
            define_error(t.get_value());
        }
    }
}

//TODO:这个函数写得非常冗余，需要改进23333
bool output(vector<Token>::iterator &token_i) {
    token_i++;
    char v = oprate(token_i);
    if (v == '(') {
        token_i++;
        string name = var(token_i);
        var_table t = find_var(name);
        if (t.type == "INT") {
            cout << int(stof(t.get_value(), 0)) << endl;
        } else {
            cout << t.get_value() << endl;
        }
        token_i++;
        v = oprate(token_i);
        if (v == ')') {
            token_i++;
            v = oprate(token_i);
        } else {
            syntax_error();
            exit(1);
        }

        if (v == '.') {
            //遇到终结符，退出程序
            exit(1);
        } else if (v == ';') {
            token_i++;
            return true;
        } else {
            //错误处理：输出语法错误
            syntax_error();
            exit(1);
        }
    } else {
        //错误处理：输出语法错误
        syntax_error();
        exit(1);
    }
}


bool assign(vector<Token>::iterator &token_i, vector<Token>::iterator end) {
    Token t = *token_i;
    string name = t.get_value();
    token_i++;
    char op = oprate(token_i);
    if (op == '=') {
        token_i++;
        var_to_num(token_i, end);
        string ttt = to_string(expr(token_i, end));
        set_value(name, ttt);
        op = oprate(token_i);
        if (op == ';') {
            token_i++;
            return true;
        } else if (op == '.')  {
            //遇到结束符，退出程序
            exit(1);
        } else {
            //错误处理：缺少分号
            lack_semicolon();
            exit(1);    
        }
    } else {
        //错误处理：赋值语法错误
        syntax_error();
        exit(1);
    }
}


bool parser(vector<Token>::iterator token_i, vector<Token>::iterator end) {
    string word = var(token_i);
    while (token_i != end) {
        if (word == "int" || word == "float") {
            string type = var(token_i);
            declaration(token_i, type);
        } else if (word == "write") {
            output(token_i);
        } else {
            assign(token_i, end);
        }
    }   
    return true;
}





// //测试主函数
// int main() {
//     //计算表达式部分的测试

//     Token left = Token("DELIMITER", "(");
//     Token a = Token("FLOAT", "3");
//     Token c = Token("OPRATE", "+");
//     Token b = Token("INT", "zxc");
//     Token right = Token("DELIMITER", ")");
//     Token e = Token("OPRATE", "*");
//     Token d = Token("INT", "8");
//     vector<Token> list = {a, c, b};
    
//     auto i = list.begin();
//     auto end = list.end();

//     cout << expr(i, end) << endl;


//     //其他语法的测试
//     Token a = Token("VAR", "int");
//     Token c = Token("VAR", "a");
//     Token b = Token("DELIMITER", ";");
//     vector<Token> list1 = {a, c, b};

//     Token d = Token("VAR", "a");
//     Token e = Token("VAR", "=");
//     Token f = Token("INT", "1");
//     Token g = Token("DELIMITER", ";");
//     vector<Token> list2 = {d, e, f, g};

//     auto i1 = list1.begin();
//     auto end1 = list1.end();


//     key_word(i1 , end1);


//     auto i2 = list2.begin();
//     auto end2 = list2.end();

//     key_word(i2, end2);


//     Token aa = Token("VAR", "write");
//     Token bb = Token("DELIMITER", "(");
//     Token cc = Token("VAR", "a");
//     Token dd = Token("DELIMITER", "(");
//     Token ee = Token("DELIMITER", ";");
//     vector<Token> list3 = {aa, bb, cc, dd};

//     auto i3 = list3.begin();
//     auto end3 = list3.end();

//     key_word(i3, end3);

//     return 0;
// }