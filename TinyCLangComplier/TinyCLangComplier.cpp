// TinyCLangComplier.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

#include<iostream>
#include<vector>
using namespace std;

struct Token{
	char token_name[10];
	int token_number;
	int line;  //在第几行

}token[100];

//定义函数
int conditional_statement();
int code_block();
int program();
int main_function();
int entrance();
int else_statement();

int p;//token指针
int now_number = 0;
int line = 0;
void nextW(){
	now_number = token[p].token_number;
	line = token[p].line;
	p++;
}
int else_statement(){
	return 1;
}
int conditional_statement(){
	if (now_number == 37) {
		program();
		nextW();
		if (now_number == 38) return 1;
		else
			return 1004;
	}
	else
		return 1003;
}
int code_block(){
	if (now_number == 34) return 1;//说明{}之间没有代码
	else{
		if (now_number == 4 || now_number == 5 || now_number == 6){  //是类型，说明是变量声明语句

		}
		else if (now_number == 0){  //标识符，说明是赋值语句

		}
		else if (now_number == 9){  //if 说明是if语句
			nextW();
			int result=conditional_statement();
			if (result > 1000) return result;
			result=program();
			if (result > 1000) return result;
			result=else_statement();
			if (result > 1000) return result;
		}
		else if (now_number == 12){  //while 循环语句

		}
		else if (now_number == 19){  //return 

		}
		else{   //未识别语句
			cout << "1100";
			return 1100;
		}
		code_block();
	}
	
}
int program(){
	if (now_number == 33){
		nextW();
		int result=code_block();
		if (result > 1000) return result;
		nextW();
		if (now_number == 34) {
			//cout << "right";
			return 1;
		}
		else
		{
			return 1006; //need '}'
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
		if (now_number == 07){
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
		return 1001;//main函数需要类型 
}
int entrance(){
	nextW();
	if (now_number == 18)
	{
		nextW();
		main_function();
	}
	else{
		return 1000;//need stdio.h
	}
}


int  main(){
	token[0].token_number = 18;
	token[0].line = 0;
	token[1].token_number = 4;
	token[1].line = 1; token[2].line = 1; token[3].line = 1; token[4].line = 1;
	token[2].token_number = 7;
	token[3].token_number = 37; token[4].token_number = 38; token[5].token_number = 33; token[6].token_number = 9; token[7].token_number = 37; token[8].token_number = 34;
	//if(entrance()==1000) cout<<"error:line"<<line<<" need stdio.h";
	int result = entrance();
	switch (result){
	case 1:cout << "compiler success"; break;
	case 1000: cout << "error1000:line" << line << " need stdio.h"; break;
	case 1001: cout << "error1001:line" << line << " main 需要类型"; break;
	case 1002: cout << "error1002:line" << line << " need 'main'"; break;
	case 1003: cout << "error1003:line" << line << " need '('"; break;
	case 1004: cout << "error1004:line" << line << " need ')'"; break;
	case 1005: cout << "error1005:line" << line << " need '{'"; break;
	case 1006: cout << "error1006:line" << line << " need '}'"; break;
	case 1100: cout << "error1100:line" << line << " 未识别语句"; break;
	}
}
