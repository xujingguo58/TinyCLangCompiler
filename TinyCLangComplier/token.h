#include<iostream>
#include<vector>
#include<string>
using namespace std;



#include<iostream>
using namespace std;

struct Token{
	string token_name;
	int token_number;
	int line;
}token[200];

int p = 0;//指针
string temp_string; //暂存
//vector<char> temp_string;
int turn_num(char c)//字符转为数字
{
	if (c == ' ') return 0;//空格
	else if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z' || c == '_'))
		return 1;//标识符
	else if (c >= '0'&&c <= '9') return 2;//常数
	else if (c == '>' || c == '<' || c == '=') return 3;
	else if (c == '/')  return 4;
	else return 5;//其他
}

void state_change(int state_before, int state_now, char temp_char, int count){ //自动机
	string c = "";
	c += temp_char;


	switch (state_before){
	case 0:
		if (state_now != 0) //temp_string.push_back(c);//读下一个
			temp_string += c;
		break;
	case 1:
		if (state_now == 1 || state_now == 2) //temp_string.push_back(c);//标识符
			temp_string += c;
		else{
			token[p++].token_name = temp_string;
			temp_string = "";
			if (state_now != 0)// temp_string.push_back(c);
				temp_string += c;
		}
		break;
	case 2:
		if (state_now == 2 || state_now == '.') //temp_string.push_back(c);//数字
			temp_string += c;
		/*
		else if (state_now == 1){ //未定义2.5.5
		temp_string.push_back(c);
		token[p].token_number = -1;
		state_now = 2;
		}
		*/
		else {
			token[p].token_name = temp_string;
			token[p].line = count;
			p++;
			temp_string = "";
			if (state_now != 0) //temp_string.push_back(c);
				temp_string += c;
		}
		break;
	case 3:
		if (state_now == '='){  //>=,<=,==
			//temp_string.push_back(c);
			temp_string += c;
			token[p++].token_name = temp_string;
			temp_string = "";
		}
		else {   //>,<,=
			token[p++].token_name = temp_string;
			temp_string = "";
			if (state_now != 0) //temp_string.push_back(c);
				temp_string += c;
		}
		break;
	case 4:
		if (state_now == 4){  //注释

		}
		break;
	case 5:
		token[p++].token_name = temp_string;
		temp_string = "";
		if (state_now != 0) //temp_string.push_back(c);
			temp_string += c;
		break;
	}
}

int check_table(string str) { //判断词法编号

	if (str == "int") return 4;
	if (str == "float") return 5;
	if (str == "void") return 6;
	if (str == "if") return 7;
	if (str == "else") return 8;
	/*if (strcmp(str, "char") == 1) return 6;
	if (strcmp(str, "main") == 1) return 7;
	if (strcmp(str, "void") == 1) return 8;
	if (strcmp(str, "if") == 1) return 9;
	if (strcmp(str, "else") == 1) return 10;
	if (strcmp(str, "do") == 1) return 11;
	if (strcmp(str, "while") == 1) return 12;
	if (strcmp(str, "for") == 1) return 13;
	if (strcmp(str, "switch") == 1) return 14;
	if (strcmp(str, "case") == 1) return 15;
	if (strcmp(str, "break") == 1) return 16;
	if (strcmp(str, "continue") == 1) return 17;
	if (strcmp(str, "return") == 1) return 18;
	if (strcmp(str, "=") == 1) return 20;
	if (strcmp(str, ">") == 1) return 21;
	if (strcmp(str, "<") == 1) return 22;
	if (strcmp(str, ">=") == 1) return 23;
	if (strcmp(str, "<=") == 1) return 24;
	if (strcmp(str, "==") == 1) return 25;
	if (strcmp(str, "+") == 1) return 26;
	if (strcmp(str, "-") == 1) return 27;
	if (strcmp(str, "*") == 1) return 28;
	if (strcmp(str, "/") == 1) return 29;
	if (strcmp(str, ".") == 1) return 30;
	if (strcmp(str, ",") == 1) return 31;
	if (strcmp(str, "\\") == 1) return 32;
	if (strcmp(str, "{") == 1) return 33;
	if (strcmp(str, "}") == 1) return 34;
	if (strcmp(str, "[") == 1) return 35;
	if (strcmp(str, "]") == 1) return 36;
	if (strcmp(str, "(") == 1) return 37;
	if (strcmp(str, ")") == 1) return 38;
	if (strcmp(str, "&") == 1) return 39;
	if (strcmp(str, "|") == 1) return 40;
	if (strcmp(str, "!") == 1) return 41;
	if (strcmp(str, "^") == 1) return 42;
	if (strcmp(str, ";") == 1) return 43;
	if (strcmp(str, ":") == 1) return 44;*/

}
void scanf()//输入
{
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		cout << "error!";
		exit(0);
	}
	int state_now = 0;//现在状态
	int state_before = 0;//上一状态
	int count = 1;//行数
	char c;
	//c= fgetc(fp);

	while ((c = fgetc(fp)) != EOF) //逐个读取
	{
		//cout << c;
		if (c == '\n') {
			count++;
			continue;
		}
		state_now = turn_num(c);

		state_change(state_before, state_now, c, count);  //状态转换
		//c++;
		state_before = state_now;

	}

	for (int i = 0; i<p; i++){
		if (token[i].token_number != EOF)
			token[i].token_number = check_table(token[i].token_name);
	}
	for (int i = 0; i < p; i++)
		cout << token[i].token_name << " " << token[i].token_number << endl;
}

int main(){
	scanf();
}