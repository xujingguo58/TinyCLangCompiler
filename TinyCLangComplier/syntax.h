
#include<stack>
//Ŀ���������

struct tempCode
{
	string op;;
	string arg1;
	string arg2;
	string result;
};
vector<tempCode> temp_code;   //��Ԫʽջ

stack<string> semantic_stack;   //����ջ

stack<string> operator_stack;  //�����ջ

