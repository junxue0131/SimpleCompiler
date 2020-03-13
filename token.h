#include <string>
#include <vector>

using namespace std;


//Token类
class Token {
    public:
        Token(string, string);
        void show_type();
        void show_value();
        string get_value();
        string get_type();
        string type;
        string value;
};




//词法分析类
class Lexer {
    public:
        Lexer();
        void test();
        void get_token(string, vector<Token>&);
};



Token read_number(int &i, string line);
Token read_letter(int& i, string line);
Token read_delimiter(int& i, string line);
bool is_invector(char item, vector<char> &list);

    


