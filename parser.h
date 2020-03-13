#include <string>
#include "token.h"
#include "error.h"



using namespace std;


class var_table {
    public:
        var_table(Token, string, string);
        string get_value();
        string get_name();
        string name;
        string type;
        string value;
};



bool is_keyword(string w);
void test_table();
void test_token(vector<Token>::iterator token_i, vector<Token>::iterator end);
void var_to_num(vector<Token>::iterator token_i, vector<Token>::iterator end);
void set_value(string name, string v);
int num_int(vector<Token>::iterator& t);
float num_float(vector<Token>::iterator& t);
char oprate(vector<Token>::iterator t);
string var(vector<Token>::iterator t);
float factor(vector<Token>::iterator &token_i, vector<Token>::iterator end);
float term(vector<Token>::iterator &token_i, vector<Token>::iterator end);
float expr(vector<Token>::iterator &token_i, vector<Token>::iterator end);
bool declaration(vector<Token>::iterator &token_i);
bool output(vector<Token>::iterator &token_i);
bool assign(vector<Token>::iterator &token_i, vector<Token>::iterator end);
bool parser(vector<Token>::iterator token_i, vector<Token>::iterator end);






