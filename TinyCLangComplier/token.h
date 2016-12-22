#include<iostream>
#include<vector>
#include<string>
using namespace std;



struct Token{
	string token_name;
	int token_number;
	int line;
}token[200];

int p = 0;//指针
int input_line;//行数

int error_line=0; //错误行数
string temp_string; //暂存
//vector<char> temp_string;
int turn_num(char c)//字符转为数字
{
	if (c == ' ' || c == '\t' || c == '\n') return 0;//空格
	else if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z' || c == '_'))
		return 1;//标识符
	else if (c >= '0'&&c <= '9') return 2;//常数
	//else if (c == '.') return 2;
	else if (c == '>' || c == '<' || c == '=') return 3;
	else if (c == '/')  return 4;
	else if (c == '.') return 6;
	else if (c == '\'') return 7;
	else if (c == '"') return 8;
 	else return 5;//其他
}

void state_change(int state_before, int state_now, char temp_char){ //自动机
	string c = "";
	c += temp_char;


	switch (state_before){
		case 0:
			if (state_now != 0&&state_now!=5) //temp_string.push_back(c);//读下一个
				temp_string += c;
			if (state_now == 5){
				token[p].token_name = c;
				token[p].line = input_line;
				p++;
			}
			break;

			case 1:
			if (state_now == 1 || state_now == 2) //标识符
				temp_string += c;
			else if (state_now == 6){
				temp_string += c;
			}
			else if (state_now == 5){
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = "";
				p++;
				token[p].token_name = c;
				token[p].line = input_line;
				p++;
			}
			else if (state_now == 7 || state_now == 8){
				temp_string += c;
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = "";
				p++;
			}
			else {
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = "";
				p++;
				if (state_now != 0)
					temp_string += c;
			}
			break;

			case 2:
			if (state_now == 2||state_now==6 ) //temp_string.push_back(c);//数字
			temp_string += c;
			else if (state_now == 4){
				token[p].token_name = temp_string;
				token[p].line = input_line;
				p++;
				temp_string = c;

			}
			else if (state_now == 7 || state_now == 8){
				temp_string += c;
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = "";
				p++;
			}
			else if (state_now == 0){
				token[p].token_name = temp_string;
				token[p].line = input_line-1;
				p++;
				temp_string = "";
			}
			else {
				token[p].token_name = temp_string;
				token[p].line = input_line;
				p++;
				temp_string = "";
				token[p].token_name = c;
				token[p].line = input_line;
				p++;
			}
			break;
			case 3:
			if (temp_char=='='){  //>=,<=,==
				temp_string += c;
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = "";
				p++;
			}
			else {   //>,<,=
				if (temp_string != ""){
					token[p].token_name = temp_string;
					token[p].line = input_line;
					temp_string = "";
					p++;
				}
					if (state_now != 0) //temp_string.push_back(c);
						temp_string += c;
			
			}
			break;
			case 4:
			if (state_now == 4){  //注释
				temp_string = "";

			}
			else {
			if (temp_string != ""){
				token[p].token_name = temp_string;
				token[p].line = input_line;
				temp_string = c;
				p++;
			}
			else{
			temp_string = c;
			}
			}
			break;
			case 5:
				if (state_now != 0 && state_now != 5) //temp_string.push_back(c);
				{
					temp_string = "";
					temp_string += c;
				}
				if (state_now == 5){
					token[p].token_name = c;
					token[p].line = input_line;
					temp_string = "";
					p++; 	
				}
			break;
			case 6:			
				temp_string += c;
				break;
			case 7:
				if (state_now == 5){
					token[p].token_name = c;
					token[p].line = input_line;
					temp_string = "";
					p++;
				}
				else
					temp_string +=c;
				break;
			case 8:
				if (state_now == 5){
					token[p].token_name = c;
					token[p].line = input_line;
					temp_string = "";
					p++;
				}
				else
					temp_string += c;
		}
}
int isIdentifier(string str){
	if ((str[0] >= 'a'&&str[0] <= 'z') || (str[0] >= 'A'&&str[0] <= 'Z'))
		return true;
	return false;
}
int isChar(string str){
	if (str[0] == '\''&&str[str.size()-1] == '\'')
		return true;
	return false;
}
int isStr(string str){
	if (str[0] == '"'&&str[str.size() - 1] == '"')
		return true;
	return false;
}
int isNum(string str){
	int point_count=0;  //小数点个数
	for (int i = 0; i < str.size(); i++){
		int temp = (int)str[i];
		if (temp < 48 || temp>57){
			if (str[i]=='.')
				point_count++;
			else
				return false;
		}	
	}
	if (point_count >= 2) return false;
	return true;
}
int check_table(string str) { //判断词法编号

	if (isChar(str)) return 1;
	if (isStr(str)) return 2;
	if (isNum(str)) return 3;
	if (str == "int") return 4;
	if (str == "float") return 5;
	if (str == "char") return 6;
	if (str == "main") return 7;
	if (str == "void") return 8;
	if (str == "if") return 9;
	if (str == "else") return 10;
	if (str == "do") return 11;
	if (str == "while") return 12;
	if (str == "for") return 13;
	if (str == "switch") return 14;
	if (str == "case") return 15;
	if (str == "break") return 16;
	if (str == "continue") return 17;
	if (str == "#") return 18;
	if (str == "return") return 19;
	if (str == "stdio.h") return 100;
	if (str == "include") return 101;
	if (str == "printf") return 102;
	if (str == "=") return 20;
	if (str == ">") return 21;
	if (str == "<") return 22;
	if (str == ">=") return 23;
	if (str == "<=") return 24;
	if (str == "==") return 25;
	if (str == "+") return 26;
	if (str == "-") return 27;
	if (str == "*") return 28;
	if (str == "/") return 29;
	if (str == ".") return 30;
	if (str == ",") return 31;
	if (str == "\\") return 32;
	if (str == "{") return 33;
	if (str == "}") return 34;
	if (str == "[") return 35;
	if (str == "]") return 36;
	if (str == "(") return 37;
	if (str == ")") return 38;
	if (str == "&") return 39;
	if (str == "|") return 40;
	if (str == "!") return 41;
	if (str == "^") return 42;
	if (str == ";") return 43;
	if (str == ":") return 44;
	if (str == "'") return 45;
	if (str == "\"") return 46;
	if (isIdentifier(str)) return 0;
	return 404;

}

int scanf()//输入
{
	for (int i = 1; i < 200; i++){
		token[i].token_number = 404;
	}
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		cout << "error!";
		exit(0);
	}
	int state_now = 0;//现在状态
	int state_before = 0;//上一状态

	char c;
	//c= fgetc(fp);
	input_line = 1;
	while ((c = fgetc(fp)) != EOF) //逐个读取
	{
		//cout << c;
		if (c == '\n') {
			input_line++;
			//continue;
		}
		state_now = turn_num(c);

		state_change(state_before, state_now, c);  //状态转换
		state_before = state_now;

	}

	for (int i = 0; i<p; i++){
		//cout << token[i].token_name.size() << " ";
		//if (token[i].token_number != EOF)
			token[i].token_number = check_table(token[i].token_name);
			if (token[i].token_number == 404)
			{
				error_line = token[i].line;
				return 2000;
			}
	}
	
	for (int i = 0; i < p; i++)
		cout << token[i].token_name << " " << token[i].token_number <<" " <<token[i].line<< endl;
	return 1;
}

