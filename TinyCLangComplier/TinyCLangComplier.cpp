// TinyCLangComplier.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


#include<vector>
#include"token.h"
#include"syntax.h"
#include"symbolTable.h"
#include <sstream>

/*struct Token{
	string token_name;
	int token_number;
	int line;  //�ڵڼ���

}token[100];*/

//���庯��
int relation_operator();  //��ϵ�����
int arithmetic_expression();//�������ʽ
int logic_expression();  //<�߼����ʽ>
int condition();  //<����>
int conditional_statement();  //�������
int variable_declatation(); //<�����������>
int code_block();
int program();
int main_function();
int entrance();
int else_statement();
int E();
int F();
int T();
int assignment();  //<��ֵ>
int char_constant();//<�ַ�����>
int declaration_or_assign();//<������ֵ>
int if_assign(); //<�Ƿ�ֵ>
int branch_program();  //<�ֳ���>
//int p;//tokenָ��
string now_name = "";   //�ֱ��ǵ�ǰtoken��ֵ�����кţ�Դ����������
int now_number = 0;
int line = 1;

int t=0;     //��Ԫʽ��ʱ��������
string getT(){  //������ʱ����
	stringstream ss;  //��tת��Ϊ�ַ��� 
	ss << t;
	ss.str();
	string s;
	s = ss.str();
	string result = "t" + s;
	return result;
}
//��Ԫʽ��������
string semantic_stack_pop(){  //��������ջ����Ԫ��
	string top = semantic_stack.top();
	semantic_stack.pop();
	return top;
}
void send(string op,string arg1,string arg2,string result){   //ѹջ
	tempCode temp;
	temp.op = op;
	temp.arg1 = arg1;
	temp.arg2 = arg2;
	temp.result = result;
	temp_code.push_back(temp);
}
void GEQ(){   //���ʽ��Ԫʽ���ɺ���
	string op = operator_stack.top();
	operator_stack.pop();
	string arg1 = semantic_stack.top();
	semantic_stack.pop();
	string arg2 = semantic_stack.top();
	semantic_stack.pop();
	string result = getT();
	semantic_stack.push(result);  //������������ջ
	t++;
	send(op, arg1, arg2, result);
}
void nextW(){
	now_name = token[p].token_name;
	now_number = token[p].token_number;
	line = token[p].line;
	p++;
}
void lastW(){
	p--;
	now_number = token[p].token_number;
	line = token[p].line;
}
int if_assign(){
	nextW();
	if (now_number == 20) {  //������"=",˵����������ʱֱ�Ӹ�ֵ
		nextW();
		int result = assignment();
		if (result >= 1000) return result;
		else
			return 1;
	}
	else if (now_number == 43){  //�գ�����ֵ
		//lastW();
		return 1;
	}
	else 
		return 1013; //need ';'
}
int declaration_or_assign(){
	int result = if_assign();
	if (result >= 1000) return result;
	else
		return 1;
	
}
int variable_declatation(){     //��������
	int result= declaration_or_assign();
	if (result >= 1000) return result;
loop_assign:
	//nextW();
	if (now_number == 31){  //, ��ʾ������ֵ
		nextW();
		result = declaration_or_assign();
		if (result >= 1000) return result;
		//nextW();
		if (now_number == 31) goto loop_assign;
		else if (now_number == 43) return 1;
		else 
			return 1013; //need ';'
	}
	else if (now_number == 43) return 1;
	else
		return 1013;  //need ';'
}
int assignment(){        //<��ֵ>
	if (now_number == 0 || now_number == 3){  //����ǳ������ʶ������Ϊ�������ʽ
		int result = arithmetic_expression();
		if (result >= 1000) return result;
		
		//nextW();
		//if (now_number == 43) return 1;
		//else
			//return 1013;
		return 1;
	}
	else if (now_number == 1){  //������ַ�����Ϊ�ַ�����
		//send("=",)
		return 1;
		/*nextW();
		if (now_number == 43){
			cout << "��ֵ�����ȷ" << endl;
			return 1;
		}
		else
			return 1013;  //need ';'*/
	}
	else
		return 1200;  //���ʽ��ֵ����
}
int relation_operator(){
	if (now_number == 20 || now_number == 21 || now_number == 22 || now_number == 23 || now_number == 24 || now_number == 25)
		return 1;
	else
		return 1007;//neeed operator
}
int F(){
	int result;
	if (now_number == 3||now_number==0){
		semantic_stack.push(now_name);  //ѹ������ջ
		nextW();
	}
	else{
		if (now_number == 37){
			nextW();
			result=E();
			if (result >= 1000) return result;
			if (now_number == 38) {
				nextW();
				return 1;
			}
			else
				return 1008;//error1
		}
		else
			return 1009;//error2
	}
	
}
int T(){
	int result =F();
	if (result >= 1000) return result;
	loop_F: 
	if (now_number==28||now_number==29){
		operator_stack.push(now_name);  //�������������ջ
		nextW();
		result=F();	
		if (result >= 1000) return result;
		GEQ();    //�����������ʽ��Ԫʽ
		goto loop_F;
	}
	return 1;
}
int E(){
	int result;
	result = T();
	if (result >= 1000) return result;
	loop_T:
	if (now_number == 26 || now_number == 27){
		operator_stack.push(now_name);  //�������������ջ
		nextW();
		result=T();
		GEQ();    //�����������ʽ��Ԫʽ
		if (result >= 1000) return result;
		goto loop_T;
	}
	return 1;
}
int arithmetic_expression(){
	int result = E();
	if (result >= 1000) return result;
	else
		return 1;
}
int logic_expression(){
	//nextW();
	int result = arithmetic_expression();
	if (result >= 1000) return result;
	nextW();
	result = relation_operator();
	if (result >= 1000) return result;
	nextW();
	result = arithmetic_expression();
	if (result >= 1000) return result;
	return 1;
}
int condition(){
	if (now_number == 37){
		nextW();
		//int result=logic_expression();
		//if (result >= 1000) return result;
		if (now_number == 3 || now_number == 0){
			nextW();
			int result = relation_operator();
			if (result >= 1000) return result;
			nextW();
			if (now_number == 3 || now_number == 0) {
				nextW();
				if (now_number == 38) return 1;
				else
					return 1004;//need ')'
			}
			else
				return 1011;  //��ֵ���ʹ���
		}
		else
			return 1010;  //��ֵ���ʹ���
		nextW();
		if (now_number == 38) return 1;
		else
			return 1004;
	}
	else
		cout << now_number;
		return 1003;  //neeed '('
}
int else_statement(){  //<else����>
	nextW();
	int result = branch_program();
	if (result >= 1000) return result;
	return 1;
}
int conditional_statement(){   //�������
	
		//nextW();
		int result = condition();
		//int result=program();
		if (result >= 1000) return result;
		nextW();
		result = branch_program();
		if (result >= 1000) return result;
		//nextW();
		nextW();
		if (now_number == 10){
			result = else_statement();
			if (result >= 1000) return result;
			else
				return 1;
		}
		lastW();
		return 1;
	
}
int code_block(){
	if (now_number == 34) {
		lastW();
		return 1;//˵��{}֮��û�д���
	}
	else{
		if (now_number == 4 || now_number == 5 || now_number == 6){  //�����ͣ�˵���Ǳ����������
			//semantic_stack.push(now_name);
			cout << "�������" << endl;
			nextW();
			int result = variable_declatation();
			if (result >= 1000)
				return result;
		}
		else if (now_number == 0){  //��ʶ����˵���Ǹ�ֵ���
			semantic_stack.push(now_name);
			cout << "��ֵ���";
			nextW();
			if (now_number == 20){
				nextW();
				int result = assignment();
				if (result >= 1000) return result;
				string str1 = semantic_stack_pop();
				cout << str1 << endl;
				string str2 = semantic_stack_pop();
				cout << str2 << endl;
				send("=", str1, "_", str2);
				if (now_number != 43) {
					//nextW();
					return 1013; //need ';'
				}
				//else
					//return 1;
					//return 1013;  //need ';'
			}
			else
				return 1012;//need '='
		}
		else if (now_number == 9){  //if ˵����if���
			cout << "if���" << endl;
			nextW();
			int result=conditional_statement();
			if (result > 1000) return result;
		}
		else if (now_number == 12){  //while ѭ�����
			cout << "while���" << endl;
			nextW();
			int result = condition();
			if (result >= 1000) return result;
			nextW();
			result = program();
			if (result >= 1000) return result;
		}
		else if (now_number == 19){  //return 

		}
		else{   //δʶ�����
			cout << "1100";
			return 1100;
		}
		cout << "һ������������" << endl;
		nextW();
		cout << now_number << endl;
		code_block();
	}
	
}
int branch_program(){
	if (now_number == 33){
		nextW();
		if (now_number == 34)  return 1;//����Ϊ{}˵���м�û�д���
		int result = code_block();
		if (result > 1000) return result;
		nextW();
		if (now_number == 34) {
			//cout << "right";
			return 1;
		}
		else
		{
			cout << "error here" << p; return 1006; //need '}'
		}
	}
	else
	{
		return 1005; //need '{'
	}
}
int program(){
	if (now_number == 33){
		nextW();
		if (now_number == 34)  return 1;//����Ϊ{}˵���м�û�д���
		int result=code_block();
		if (result > 1000) return result;
		nextW();
		if (now_number == 34) {
			//cout << "right";
			return 1;
		}
		else
		{
			cout << "error here"<<p; return 1006; //need '}'
		}
	}
	else
	{
		return 1005; //need '{'
	}
}
int main_function(){
	if (now_number == 4){
		nextW();
		if (now_number == 07){  //��main����main������Ԫʽ
			send("main", "_", "_", "_");
			nextW();
			if (now_number == 37){
				nextW();
				if (now_number == 38){
					nextW();
					program();
				}
				else
					return 1004;//need ')'
			}
			else
				return 1003;//need '('
		}
		else
			return 1002; //need 'main'
	}
	else
		return 1001;//main������Ҫ���� 
}
int entrance(){
	nextW();
	if (now_number == 18)
	{
		nextW();
		if (now_number == 101){
			nextW();
			if (now_number == 22){
				nextW();
				if (now_number == 100){
					nextW();
					if (now_number == 21){
						nextW();
						main_function();
					}
					else
						return 1000;
				}
				else
					return 1000;
			}
			else
				return 1000;
		}
		else
			return 1000;

	}
	else{
		return 1000;//need ��#��
	}
}


int  main(){

	int result;
	result = scanf();
	if (result >= 2000)
	{
		cout << "error2200:line " << error_line << " δ��ʶ����ַ�";
		return 0;
	}

	createSymbolTable();
	p = 0;
	line = 1;
	result = entrance();
	switch (result){
	case 1:cout << "compiler success"; break;
	case 1000: cout << "error1000:line " << line << " ͷ�ļ���ʽ����"; break;
	case 1001: cout << "error1001:line " << line << " main ��Ҫ����"; break;
	case 1002: cout << "error1002:line " << line << " need 'main'"; break;
	case 1003: cout << "error1003:line " << line << " need '('"; break;
	case 1004: cout << "error1004:line " << line << " need ')'"; break;
	case 1005: cout << "error1005:line " << line << " need '{'"; break;
	case 1006: cout << "error1006:line " << line << " need '}'"; break;
	case 1007: cout << "error1007:line " << line << " need operator"; break;
	case 1008: cout << "error1008:line " << line << " �������ʽ����1"; break;
	case 1009: cout << "error1009:line " << line << " �������ʽ����2"; break;
	case 1010: cout << "error1010:line " << line << " ��ֵ���ʹ���"; break;
	case 1011: cout << "error1011:line " << line << " ��ֵ���ʹ���"; break;
	case 1012: cout << "error1012:line " << line << " need '='"; break;
	case 1013: cout << "error1013:line " << line << " need ';'"; break;
	case 1200: cout << "error1200:line " << line << " ���ʽ��ֵ����"; break;
	case 1100: cout << "error1100:line " << line << " δʶ�����"; break;
	default: cout << "δ�������" << endl;
	}
	cout << "��Ԫʽ" << endl;
	for (tempCode t : temp_code){
		cout << t.op << " " << t.arg1 << " " << t.arg2 << " " << t.result << endl;
	}
	//cout << temp_code.top().op << " " << temp_code.top().arg1 << " " << temp_code.top().arg2 << " " << temp_code.top().result << endl;
	//cout << semantic_stack.top();
}
