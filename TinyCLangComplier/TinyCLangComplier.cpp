// TinyCLangComplier.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


#include<vector>
#include"token.h"


/*struct Token{
	string token_name;
	int token_number;
	int line;  //在第几行

}token[100];*/

//定义函数
int relation_operator();
int arithmetic_expression();
int logic_expression();  //<逻辑表达式>
int condition();  //<条件>
int conditional_statement();  //条件语句
int code_block();
int program();
int main_function();
int entrance();
int else_statement();
int E();
int F();
int T();
int assignment();  //<赋值>

//int p;//token指针
int now_number = 0;
int line = 0;
void nextW(){
	now_number = token[p].token_number;
	line = token[p].line;
	p++;
}
int assignment(){
	return 1012;
}
int relation_operator(){
	if (now_number == 20 || now_number == 21 || now_number == 22 || now_number == 23 || now_number == 24 || now_number == 25)
		return 1;
	else
		return 1007;//neeed operator
}
int F(){
	if (now_number == 3){
		nextW();
	}
	else{
		if (now_number == 37){
			nextW();
			E();
			if (now_number == 38) nextW();
			else
				return 1008;//need ')'
		}
		else
			return 1009;//need '('
	}
}
int T(){
	int result =F();
	if (result >= 1000) return result;
	loop_F: 
	if (now_number==28||now_number==29){
		nextW();
		result=F();
		if (result >= 1000) return result;
		goto loop_F;
	}
}
int E(){
	int result;
	loop_T:result=T();
	if (result >= 1000) return 1000;
	if (now_number == 26 || now_number == 27){
		nextW();
		result=T();
		if (result >= 1000) return 1000;
		goto loop_T;
	}
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
				return 1011;  //右值类型错误
		}
		else
			return 1010;  //左值类型错误
		nextW();
		if (now_number == 38) return 1;
		else
			return 1004;
	}
	else
		cout << now_number;
		return 1003;
}
int else_statement(){
	return 1;
}
int conditional_statement(){   //条件语句
	
		//nextW();
		int result = condition();
		//int result=program();
		if (result >= 1000) return result;
		nextW();
		/*if (now_number == 38) return 1;
		else
			return 1004;*/
		result = program();
		if (result >= 1000) return result;
		result = else_statement();
		if (result >= 1000) return result;
			return 1;
	
}
int code_block(){
	if (now_number == 34) return 1;//说明{}之间没有代码
	else{
		if (now_number == 4 || now_number == 5 || now_number == 6){  //是类型，说明是变量声明语句

		}
		else if (now_number == 0){  //标识符，说明是赋值语句
			cout << "赋值语句";
			nextW();
			if (now_number == 20){
				nextW();
				int result = assignment();
				if (result >= 1000) return result;
			}
			else
				return 1012;//need '='
		}
		else if (now_number == 9){  //if 说明是if语句
			cout << "if语句" << endl;
			nextW();
			int result=conditional_statement();
			if (result > 1000) return result;
			//else
				//return 1;
			/*result=program();
			if (result > 1000) return result;
			result=else_statement();
			if (result > 1000) return result;*/
		}
		else if (now_number == 12){  //while 循环语句
			nextW();
			int result = condition();
			if (result >= 1000) return result;
			nextW();
			result = program();
			if (result >= 1000) return result;
		}
		else if (now_number == 19){  //return 

		}
		else{   //未识别语句
			cout << "1100";
			return 1100;
		}
		cout << "一个语句分析结束" << endl;
		nextW();
		code_block();
	}
	
}
int program(){
	if (now_number == 33){
		nextW();
		if (now_number == 34)  return 1;//现在为{}说明中间没有代码
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
	/*token[0].token_number = 18;token[0].line = 0;
	token[1].token_number = 4;
	token[1].line = 1; token[2].line = 1; token[3].line = 1; token[4].line = 1;
	token[2].token_number = 7;
	token[3].token_number = 37; token[4].token_number = 38; token[5].token_number = 33; token[6].token_number = 9; 
	token[7].token_number = 37; token[8].token_number = 3; token[9].token_number = 21; token[10].token_number = 3;
	token[11].token_number = 38; token[12].token_number = 33; token[13].token_number = 34; //token[14].token_number = 34;
	//while(i<5){i=i+1;}
	token[14].token_number = 12; token[15].token_number = 37; token[16].token_number = 0; token[17].token_number = 22; token[18].token_number = 3; token[19].token_number = 38;
	token[20].token_number = 33; token[21].token_number = 0; token[22].token_number = 20; token[23].token_number = 3; token[24].token_number = 0; token[25].token_number = 26;
	token[26].token_number = 3; token[27].token_number = 43; token[28].token_number = 34; token[29].token_number = 34;*/
	//if(entrance()==1000) cout<<"error:line"<<line<<" need stdio.h";

	//p = 0;
	scanf();
	p = 0;
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
	case 1007: cout << "error1007:line" << line << " need operator"; break;
	case 1008: cout << "error1008:line" << line << " 算数表达式错误1"; break;
	case 1009: cout << "error1009:line" << line << " 算数表达式错误2"; break;
	case 1010: cout << "error1010:line" << line << " 左值类型错误"; break;
	case 1011: cout << "error1011:line" << line << " 右值类型错误"; break;
	case 1100: cout << "error1100:line" << line << " 未识别语句"; break;
		
	}
}
