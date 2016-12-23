//符号总表
//关键字表
//界符表
//标识符表
//算数常量表
//字符常量表


struct symbolTotalTable{
	string name;
	string tpe;  //类型
	string cat;   //种类
	string addr;   //地址
};
symbolTotalTable symbol_total_table[50];
//string symbol_total_table[20];
struct typeTable{  //类型表
	string tpe;  //类型码
	string tpoint;  //指向不同的信息表项
};
typeTable type_table[50];

struct identifierTable  //标识符表
{
	int number;  //序号
	string name;   //标识符名称
};
//identifierTable identifier_table[50];
vector<identifierTable> identifier_table;
struct constantTable{  //常数表
	int number;    //序号
	string value;  //值
};
constantTable constant_table[50];
void createIdentifierTable(){    //生成标识符表
	int i = 0;
	int k = 0;
	while (token[i].token_name != ""){
		if (token[i].token_number == 0){
			identifier_table[k].number = k;
			identifier_table[k].name = token[i].token_name;
			k++;
		}
		i++;
	}
	for (int j = 0; j < k; j++){
		cout << identifier_table[j].number << "  " << identifier_table[j].name << endl;
	}
}
void createConstantTable(){  //生成常数表
	int i = 0;
	int k = 0;
	while (token[i].token_name != ""){
		if (token[i].token_number == 3){
			constant_table[k].number = k;
			constant_table[k].value = token[i].token_name;
			k++;
		}
		i++;
	}
	cout << "常数表" << endl;
	for (int j = 0; j < k; j++){
		cout << constant_table[j].number << "  " << constant_table[j].value << endl;
	}
}
//生成符号表
void createSymbolTable(){
	/*int i = 0;
	while (token[i].token_name != ""){
		symbol_total_table[i].name = token[i].token_name;

	}*/
	//createIdentifierTable();
	createConstantTable();
}