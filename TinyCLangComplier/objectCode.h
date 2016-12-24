

vector<string> object_code; //目标代码存储的容器

void showObjectCode(){
	cout << "目标代码" << endl;
	for (auto t : object_code)
		cout << t << endl;
}

void createObjectCode(){
	object_code.push_back("DSEG SEGMENT");
	for (auto t : identifier_table){
		switch (t.type){
		case 4:
			object_code.push_back("DW    " + t.name);
			break;
		case 5:
			object_code.push_back("DB    " + t.name);
			break;
		case 6:
			object_code.push_back("DD    " + t.name);
		}
	}
	showObjectCode();
}