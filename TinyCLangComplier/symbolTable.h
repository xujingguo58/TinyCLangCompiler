//符号总表
//关键字表
//界符表
//标识符表
//算数常量表
//字符常量表


struct symbolTotalTable{  //总表
	string name;
	//string tpe;  //类型
	string cat;   //种类
	string addr;   //地址
};
vector<symbolTotalTable> symbol_total_table;

struct typeTable{  //类型表
	string tpe;  //类型码
	string tpoint;  //指向不同的信息表项
};
vector<typeTable> type_table;

struct identifierTable  //标识符表
{
	int number;  //序号
	int type;   //标识符类型，比如int(04)，char(06）
	string name;   //标识符名称
};
vector<identifierTable> identifier_table;
struct constantTable{  //常数表
	int number;    //序号
	string value;  //值
};
//constantTable constant_table[50];
vector<constantTable> constant_table;  //关键字表
struct keywordTable{
	int number;   //序列码
	string name;
};
vector<keywordTable> keyword_table;
int checkKeywordTable(int number){   //检查关键字表中是否已存在
	for (auto t : keyword_table){
		if (t.number == number)
			return 1;
	}
	return 0;
}
int checkConstantTable(string value){  //检查常数表是否存在该常数
	for (auto t : constant_table){
		if (t.value == value)
			return 1;
	}
	return 0;
}

void createConstantTable(){  //生成常数表
	int i = 0;
	int k = 0;
	while (token[i].token_name != ""){
		if (token[i].token_number == 3&&checkConstantTable(token[i].token_name)==0){
			constantTable temp;
			temp.number = k;
			temp.value = token[i].token_name;
			constant_table.push_back(temp);
			k++;
		}
		i++;
	}
	cout << "常数表" << endl;
	for (auto t : constant_table)
		cout << t.number << " " << t.value << endl;
}
void createKeywordTable(){   //生成关键字表
	int i = 0;
	while (token[i].token_name != ""){
		if ((token[i].token_number >= 4 && token[i].token_number <= 19) || token[i].token_number >= 100){
			if (checkKeywordTable(token[i].token_number) == 0){
				keywordTable temp;
				temp.name = token[i].token_name;
				temp.number = token[i].token_number;
				keyword_table.push_back(temp);
			}
			//k++;
		}
		i++;
	}
	cout << "关键字表" << endl;
	for (auto t : keyword_table)
		cout << t.number << " " << t.name << endl;
}
int checkIdentifierTable(string identifier,int type){   //检查标识符表是否存在
	//cout << "现在要检查的标识符是" << identifier << endl;
	for (auto t : identifier_table){
		if (t.name == identifier)
			return 1;
		if (t.name == identifier&&t.type != type)
			return -1;
	}
	return 0;
}
void addIdentifierTable(string identifier,int type){  //添加新项到标识符表
	//identifier_table.push_back(identifier);
	identifierTable temp;
	temp.name = identifier;
	temp.number = identifier_table.size() + 1;
	temp.type = type;
	identifier_table.push_back(temp);
}
void createIdentifierTable(){    //输出标识符表
	cout << "标识符表" << endl;
	for (auto t : identifier_table)
		cout << t.number << " " << t.name <<" "<<t.type<< endl;
}
void createSymbolTotalTable(){
	symbolTotalTable temp;  //中间变量
	for (auto t : keyword_table){   //把关键字表加到总表里
		temp.name = t.name; 
		temp.cat = "k";       //用k来代表关键字的种类
		temp.addr = "->常量表";
		symbol_total_table.push_back(temp);
	}
	for (auto t : identifier_table){  //把标识符表加到总表里
		temp.name = t.name;
		temp.cat = "v";				//v代表变量
		temp.addr = "->标识符表";
		symbol_total_table.push_back(temp);
	}
	for (auto t : constant_table){   //把常数表加到总表里
		temp.name = t.value;
		temp.cat = "c";			//用c代表常量
		temp.addr = "->常量表";
		symbol_total_table.push_back(temp);
	}
	cout << "符号总表" << endl;
	for (auto t : symbol_total_table){
		cout << t.name << "  " << t.cat << "  " << t.addr << endl;
	}
}
//生成符号表
void createSymbolTable(){
	createConstantTable();
	createKeywordTable();
	createIdentifierTable();
	createSymbolTotalTable();
}