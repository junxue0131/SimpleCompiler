# 计算器编译程序
> 实现对特定类型文法语言简单编译功能的简单程序

## 版本记录
* v0.1.0:初始版本

## TODO
* 支持声明式赋值
* 把终结符的处理逻辑从三类句法中抽离出来
* 解决混乱的私有变量改共有变量引发的混乱问题
* 完善异常处理机制，理顺各类错误的关系，对错误进行更细分


## 项目说明
> * 本项目使用c++语言编写，由于作者对于c++语言的特性不够熟悉，所以很多地方出现了很冗余的写法，这点会在后续予以改善
> * 本项目在linux下进行开发，测试时请务必保证测试环境为linux
> * 源代码中留存很多注释，这些是在开发和测试过程中留下的调试代码，在后续的开发中仍有作用，因此予以保留
* main.cpp:主函数代码，用来进行文件读写，和调用编译器的子功能的工作
* error.cpp/error.h:错误处理模块，主要负责打印报错信息，放在一切统一管理，进行解耦，方便后续扩展
* token.cpp/token.h:词法分析模块
* parser.cpp/parser.h:语法分析模块
* code:将测试代码写入该文件即可进行运行测试
* readme:本项目文档

## 开始使用
* 所有文件放于同一目录下，运行：
```
g++ token.cpp parser.cpp error.cpp main.cpp -o test -std=c++11
```
* 生成二进制文件test后，即可填入在code内填入代码进行运行测试
* 结果将在控制台直接显示


## 语言特性的一些说明
* 本程序不支持声明式赋值，例如：
```
int a = 3;
```
必须使用如下形式：
```
int a;
a = 3;
```
* 本程序不支持同时声明多个变量：
```
int a, b;
```
>后续版本会修复这些问题




## 支持语言的文法

#### 终结符号集合
```
+ - * / = float int ; . ( )  write
```

#### 非终结符号集合
* number:数字字符
* letter:字母字符
* num_int:整型数字
* num_float:浮点型数字
* oprate:非变量和数字字符
* var:变量
* expr:表达式，计算式的最大单元
* term:处理乘除号的计算单元
* factor:最小的计算单元
* declaration:变量声明
* assign:赋值语句
* output:输出语句


#### 产生式集合
* number -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
* letter -> a | b | ... | z
* oprate -> + | - | * | / | ( | ) | ; | . | =
* var -> letter(letter | number)...(letter | number)
* num_int -> number...number
* num_float -> number_int.number_int
* expr -> expr '+' term | expr '-' term | term
* term -> term '*' factor | term '/' factor | factor
* factor -> number | '(' expr ')'
* declaration -> int var; | float var;
* assign -> var = expr;
* output -> write(var);


## 错误处理说明
* use_key_word_error:使用关键词作为变量名
* define_error:定义语句出现错误
* syntax_error:默认情况下的语法错误
* undefined_error:变量未定义错误
* lack_semicolon:语法错误，可能是缺少分号
* not_assigned_error:该变量未被赋值
* type_error:变量类型错误


## Test Cases
>以下为我使用且测试通过的测试样例
1.输入：
```
float a;
int b;
a = (10.44*356+1.28) / 2 + 1024 * 1.6;
b = a * 2 – c/2;
write(b).
```
输出：
```
(ERROR)In line 4:
undefined error: "c" is undefined.
```

2.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
ggsda = 9434.0;
a = (1 + 1)  ;
f = a * ((1+2) *4    )+sssye;
ggsda = (f + (a*sssye) + ggsda)/3.5;
a = (	(ggsda/43)+(f/a))  ;
write(a);
write(f);
write  (  ggsda  ).
```
输出：
```
76.923584
28.000000
2705.714355
```

3.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
ggsda = 9434.0;
a = (1 + 1)  ;
f = abc * ((1+2) *4    )+sssye;
ggsda = f + (a*sssye) + ggsda;
a = ((ggsda/43)+(f/a))  ;
write(a);
write(f);
write  (  ggsda  )  ;
```
输出：
```
(ERROR)In line 9:
undefined error: "abc" is undefined.
```

4.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
float 5ggsda = 9434.0;
5ggsda = 9434.0;
a = (1 + 1)  ;
f = a * ((1+2) *4    )+sssye;
ggsda = f + (a*sssye) + ggsda;
a = ((ggsda/43)+(f/a))  ;
write(a);
write(fd);
write  (  ggsda  )  .
```
输出：
```
(ERROR)In line 7:
define error: The defination of "ggsda" is wrong.
(ERROR)In line 8:
Syntax error!
```

5.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
ggsda = 9434.0;
a = (1 + 1)  ;
f = a * ((1+2) *4    )+sssye;
ggsda = f + (a*sssye) + ggsda;
a = ((ggsda/43)+(f/a))  ;
write(a);
write(fd);
write  (  ggsda  )  ;
```
输出：
```
(ERROR)In line 8:
not assigned error: "NULL" is not assigned.
```

6.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
ggsda = 9434.0;
a = (1 + 1)  ;
f = a * ((1+2)
 *4    )+sssye;
ggsda = f + (a*sssye) + ggsda;
a = ((ggsda/43)+(f/a))  ;
write(a);
write(f);
write  (  ggsda  ) .
```
输出：
```
(ERROR)In line 9:
lack_semicolon error.
```

7.输入：
```
int a; float f;
a = 6;
f = 7.8;
int sssye;
sssye = 4;
float ggsda  ;
ggsda = 9434.0;
a = (1 + 1)  ;
f = a * ((1+2) *4    ))+sssye;
ggsda = (f + (a*sssye) + ggsda)/3.5;
a = (	(ggsda/43)+(f/a))  ;
write(a);
write(f);
write  (  ggsda  ) .
```
输出：
```
(ERROR)In line 9:
Syntax error: maybe lack_semicolon error.
```
