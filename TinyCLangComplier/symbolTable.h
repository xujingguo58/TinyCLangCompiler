//�����ܱ�
//�ؼ��ֱ�
//�����
//��ʶ����
//����������
//�ַ�������


struct symbolTotalTable{  //�ܱ�
	string name;
	//string tpe;  //����
	string cat;   //����
	string addr;   //��ַ
};
vector<symbolTotalTable> symbol_total_table;

struct typeTable{  //���ͱ�
	string tpe;  //������
	string tpoint;  //ָ��ͬ����Ϣ����
};
vector<typeTable> type_table;

struct identifierTable  //��ʶ����
{
	int number;  //���
	int type;   //��ʶ�����ͣ�����int(04)��char(06��
	string name;   //��ʶ������
};
vector<identifierTable> identifier_table;
struct constantTable{  //������
	int number;    //���
	string value;  //ֵ
};
//constantTable constant_table[50];
vector<constantTable> constant_table;  //�ؼ��ֱ�
struct keywordTable{
	int number;   //������
	string name;
};
vector<keywordTable> keyword_table;
int checkKeywordTable(int number){   //���ؼ��ֱ����Ƿ��Ѵ���
	for (auto t : keyword_table){
		if (t.number == number)
			return 1;
	}
	return 0;
}
int checkConstantTable(string value){  //��鳣�����Ƿ���ڸó���
	for (auto t : constant_table){
		if (t.value == value)
			return 1;
	}
	return 0;
}

void createConstantTable(){  //���ɳ�����
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
	cout << "������" << endl;
	for (auto t : constant_table)
		cout << t.number << " " << t.value << endl;
}
void createKeywordTable(){   //���ɹؼ��ֱ�
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
	cout << "�ؼ��ֱ�" << endl;
	for (auto t : keyword_table)
		cout << t.number << " " << t.name << endl;
}
int checkIdentifierTable(string identifier,int type){   //����ʶ�����Ƿ����
	//cout << "����Ҫ���ı�ʶ����" << identifier << endl;
	for (auto t : identifier_table){
		if (t.name == identifier)
			return 1;
		if (t.name == identifier&&t.type != type)
			return -1;
	}
	return 0;
}
void addIdentifierTable(string identifier,int type){  //��������ʶ����
	//identifier_table.push_back(identifier);
	identifierTable temp;
	temp.name = identifier;
	temp.number = identifier_table.size() + 1;
	temp.type = type;
	identifier_table.push_back(temp);
}
void createIdentifierTable(){    //�����ʶ����
	cout << "��ʶ����" << endl;
	for (auto t : identifier_table)
		cout << t.number << " " << t.name <<" "<<t.type<< endl;
}
void createSymbolTotalTable(){
	symbolTotalTable temp;  //�м����
	for (auto t : keyword_table){   //�ѹؼ��ֱ�ӵ��ܱ���
		temp.name = t.name; 
		temp.cat = "k";       //��k������ؼ��ֵ�����
		temp.addr = "->������";
		symbol_total_table.push_back(temp);
	}
	for (auto t : identifier_table){  //�ѱ�ʶ����ӵ��ܱ���
		temp.name = t.name;
		temp.cat = "v";				//v�������
		temp.addr = "->��ʶ����";
		symbol_total_table.push_back(temp);
	}
	for (auto t : constant_table){   //�ѳ�����ӵ��ܱ���
		temp.name = t.value;
		temp.cat = "c";			//��c������
		temp.addr = "->������";
		symbol_total_table.push_back(temp);
	}
	cout << "�����ܱ�" << endl;
	for (auto t : symbol_total_table){
		cout << t.name << "  " << t.cat << "  " << t.addr << endl;
	}
}
//���ɷ��ű�
void createSymbolTable(){
	createConstantTable();
	createKeywordTable();
	createIdentifierTable();
	createSymbolTotalTable();
}