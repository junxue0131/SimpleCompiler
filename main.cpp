#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"

using namespace std;

int line = 0;

int main(int argc, char** argv) {
    //初始化工具
    Lexer tokenizer;
    vector<Token> token_list;

    //文件流
    ifstream fp_in;
    ofstream fp_out;

    //打开文件
    fp_in.open("code");
    fp_out.open("res");

    //循环读取每一行
    while (!fp_in.eof()) {
        line++;
        string buffer = "";
        getline(fp_in, buffer);
        // cout << "This is line" << line << ":" << buffer << endl;
        //获取每一行的token        

        tokenizer.get_token(buffer, token_list);

        // 输出每一行的token
        // for (auto i:token_list) {
        //     i.show_value();
        // }


        //每一行的语法分析
        auto token_i = token_list.begin();
        auto end = token_list.end();
        parser(token_i, end);
        // test_table();

        token_list.clear();
    }

    //关闭文件
    fp_in.close();
    fp_out.close();

    return 0;
}