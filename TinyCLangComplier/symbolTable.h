//�����ܱ�
//�ؼ��ֱ�
//�����
//��ʶ����
//����������
//�ַ�������


struct symbolTotalTable{
	string name;
	string tpe;  //����
	string cat;   //����
	string addr;   //��ַ
};
symbolTotalTable symbol_total_table[50];
//string symbol_total_table[20];
struct typeTable{  //���ͱ�
	string tpe;  //������
	string tpoint;  //ָ��ͬ����Ϣ����
};
typeTable type_table[50];

struct identifierTable  //��ʶ����
{
	int number;  //���
	string name;   //��ʶ������
};
//identifierTable identifier_table[50];
vector<identifierTable> identifier_table;
struct constantTable{  //������
	int number;    //���
	string value;  //ֵ
};
constantTable constant_table[50];
void createIdentifierTable(){    //���ɱ�ʶ����
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
void createConstantTable(){  //���ɳ�����
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
	cout << "������" << endl;
	for (int j = 0; j < k; j++){
		cout << constant_table[j].number << "  " << constant_table[j].value << endl;
	}
}
//���ɷ��ű�
void createSymbolTable(){
	/*int i = 0;
	while (token[i].token_name != ""){
		symbol_total_table[i].name = token[i].token_name;

	}*/
	//createIdentifierTable();
	createConstantTable();
}