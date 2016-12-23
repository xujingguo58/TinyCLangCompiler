
#include<stack>
//目标代码生成

struct tempCode
{
	string op;;
	string arg1;
	string arg2;
	string result;
};
vector<tempCode> temp_code;   //四元式栈

stack<string> semantic_stack;   //语义栈

stack<string> operator_stack;  //运算符栈

