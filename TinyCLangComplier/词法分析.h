
#include<iostream>
using namespace std;
/*class Token//Token类
{
private:
string name[16];//token
int num;//token编号
int line;//token行数
public:
void setToken(&token,int i,int count)//输入
{
name=token;
num=i;
line=count;
}
void printToken()//输出
{
cout<<"token="<<name<<endl;
cout<<"num="<<num<<endl;
cout<<"line="<<endl;
}
}*/
struct Token{
	string token_name;
	int token_number;
	int line;
}token[200];

int p = 0;//指针
string temp_string; //暂存
int turn_num(char c)//字符转为数字
{
	if (c == ' ') return 0;//空格
	else if (c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z' || c == '_')
		return 1;//标识符
	else if (c >= '0'&&c <= '9') return 2;//常数

	else if (c == '>' || c == '<' || c == '=') return 3;
	else if (c == '/')  return 4;
	else return 5;//其他
}

void state_change(int state_before, int state_now, char c){
	switch (state_before){
	case 0:
		token[0].token_name = temp_string;
		temp_string = "";
		p++;
	case 1:
		if (state_now == 1){
			//strcpy(temp_string, c);
		}
		if (state_now == 4)
	case 4:
		if (state_now == 4){  //注释

		}
	case 8:
	}
}

int check_table(string str){
	//if (strcmp(str, "main")) return 4;

}
int main()
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
	c = fgetc(fp);
	while (c != EOF)
	{
		if (c == '\n') count++; break;

		//while(c!=' '&&c!='\n')
		//{
		//str[i++]=c;//临时token
		state_now = turn_num(c);
		c++;
		state_before = state_now;
		state_change(state_before, state_now, c);  //状态转换

		//}
	}
	for (int i = 0; i<p; i++){
		token[i].token_number = check_table(token[i].token_name);
	}
}

