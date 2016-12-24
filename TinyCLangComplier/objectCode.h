

vector<string> object_code; //目标代码存储的容器

int returnType(string name){
	for (auto t : identifier_table){
		if (name == t.name)
			return t.type;
		if (name == "_"){     //如果是_,返回0
			return 0;
		}
		if (isNum(name))
			return 3;
	}
	
}
void showObjectCode(){
	cout << "目标代码" << endl;
	for (auto t : object_code)
		cout << t << endl;
}
int temp_T = t;
int checkTempCode(){
	for (auto t : temp_code){
		if (returnType(t.arg1) != returnType(t.arg2)) {  //表达式类型前后不匹配
			return 3003;			//表达式类型不匹配
		}
		else{

		}
	}
	return 1;
}
void createObjectCode(){
	object_code.push_back("DSEG SEGMENT");
	for (auto t : identifier_table){
		switch (t.type){
		case 4:
			object_code.push_back("DW    " + t.name);
			break;
		case 5:
			object_code.push_back("DD    " + t.name);
			break;
		case 6:
			object_code.push_back("DB    " + t.name);
		}
	}
	for (auto t : temp_code){
		char temp_char = t.result[0];
		cout << temp_char << endl;
		if (temp_char == 't'){
			switch (returnType(t.arg1)){
			case 3:
				object_code.push_back("DW    " + t.result);
				break;
			case 4:
				object_code.push_back("DW    " + t.result);
				break;
			case 5:
				object_code.push_back("DD    " + t.result);
				break;
			case 6:
				object_code.push_back("DB    " + t.result);
			}
		}
	}

	showObjectCode();
}