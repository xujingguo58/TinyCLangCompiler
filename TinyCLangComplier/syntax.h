
#include<stack>
#include <sstream>
//Ŀ���������

struct tempCode
{
	string op;;
	string arg1;
	string arg2;
	string result;
};
vector<tempCode> temp_code;   //��Ԫʽ����

stack<string> semantic_stack;   //����ջ

stack<string> operator_stack;  //�����ջ

stack<int> type_stack;    //����ջ �����������
int t = 0;     //��Ԫʽ��ʱ��������
string getT(){  //������ʱ����
	stringstream ss;  //��tת��Ϊ�ַ��� 
	ss << t;
	//ss.str();
	string s;
	s = ss.str();
	string result = "t" + s;
	t++;
	return result;
}
//��Ԫʽ��������
string semantic_stack_pop(){  //��������ջ����Ԫ��
	string top = semantic_stack.top();
	semantic_stack.pop();
	return top;
}
void send(string op, string arg1, string arg2, string result){   //ѹջ
	tempCode temp;
	temp.op = op;
	temp.arg1 = arg1;
	temp.arg2 = arg2;
	temp.result = result;
	temp_code.push_back(temp);
	//semantic_stack.push();
}
void GEQ(){   //���ʽ��Ԫʽ���ɺ���
	string op = operator_stack.top();
	operator_stack.pop();
	string arg2 = semantic_stack.top();
	semantic_stack.pop();
	string arg1 = semantic_stack.top();
	semantic_stack.pop();
	string result = getT();
	semantic_stack.push(result);  //������������ջ
	send(op, arg1, arg2, result);
}
