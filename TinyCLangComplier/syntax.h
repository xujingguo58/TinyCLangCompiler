
#include<stack>
#include <sstream>
//目标代码生成

struct tempCode
{
	string op;;
	string arg1;
	string arg2;
	string result;
};
vector<tempCode> temp_code;   //四元式容器

stack<string> semantic_stack;   //语义栈

stack<string> operator_stack;  //运算符栈

stack<int> type_stack;    //类型栈 保存变量类型
int t = 0;     //四元式临时变量申请
string getT(){  //申请临时变量
	stringstream ss;  //将t转换为字符串 
	ss << t;
	//ss.str();
	string s;
	s = ss.str();
	string result = "t" + s;
	t++;
	return result;
}
//四元式函数定义
string semantic_stack_pop(){  //弹出语义栈顶部元素
	string top = semantic_stack.top();
	semantic_stack.pop();
	return top;
}
void send(string op, string arg1, string arg2, string result){   //压栈
	tempCode temp;
	temp.op = op;
	temp.arg1 = arg1;
	temp.arg2 = arg2;
	temp.result = result;
	temp_code.push_back(temp);
	//semantic_stack.push();
}
void GEQ(){   //表达式四元式生成函数
	string op = operator_stack.top();
	operator_stack.pop();
	string arg2 = semantic_stack.top();
	semantic_stack.pop();
	string arg1 = semantic_stack.top();
	semantic_stack.pop();
	string result = getT();
	semantic_stack.push(result);  //保存结果到语义栈
	send(op, arg1, arg2, result);
}
