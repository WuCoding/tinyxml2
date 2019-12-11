#include "func.h"

int createXML(const char* xmlPath){
	XMLDocument doc;
	if(3 != doc.LoadFile(xmlPath)){
		cout <<"file has been existed !"<<endl;
		return 0;
	}

	//添加申明可以使用如下两行
	XMLDeclaration* declaration=doc.NewDeclaration();
	doc.InsertFirstChild(declaration);

	XMLElement* root=doc.NewElement("XMLUSER");
	doc.InsertEndChild(root);
	
	XMLElement* userNode = doc.NewElement("User");
	/*添加属性*/
	userNode->SetAttribute("Name","liangbaikai");
	userNode->SetAttribute("Password ","bbbbbb");
	root->InsertEndChild(userNode);
	
	return doc.SaveFile(xmlPath);
}

int test1(){
	/*创建*/
	createXML("bbb1.xml");
	/*增*/
	//addXML1("bbb1.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	//addXML2("bbb1.xml");/*在性别后面添加年龄，再添加一个号码*/
	/*删*/
	//deleteXML("bbb1.xml");/*删除第一个号码，删除第二个号码的属性*/
	/*改*/
	/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
	//changeXML("bbb1.xml");
	/*查*/
	//selectXML("bbb1.xml");/*将liangbaikai的信息打印出来*/
	return 0;
}

//增
int addXML1(const char* xmlPath)
{
	XMLDocument doc;
	if(doc.LoadFile(xmlPath) != 0){
		cout<<"load xml file failed"<<endl;
		return false;
	}
	XMLElement* root=doc.RootElement();
	XMLElement* userNode=root->FirstChildElement("User");

	XMLElement* gender = doc.NewElement("Gender");
	XMLText* genderText=doc.NewText("man");
	gender->InsertFirstChild(genderText);
	userNode->InsertFirstChild(gender);

	XMLElement* mobile = doc.NewElement("Mobile");
	mobile->InsertFirstChild(doc.NewText("188****6211"));
	userNode->InsertEndChild(mobile);

	XMLElement* email = doc.NewElement("Email");
	email->InsertFirstChild(doc.NewText("1157***657@qq.com"));
	userNode->InsertEndChild(email);

	XMLElement* userNode1 = doc.NewElement("User");
	userNode1->SetAttribute("Name","Wenbaikai");
	userNode1->SetAttribute("Password ","aaaaa");
	root->InsertEndChild(userNode1);

	XMLElement* mobile1 = doc.NewElement("Mobile");
	mobile1->InsertFirstChild(doc.NewText("166****6666"));
	userNode1->InsertEndChild(mobile1);

	return doc.SaveFile(xmlPath);
}

int addXML2(const char* xmlPath){
	XMLDocument doc;
	if(doc.LoadFile(xmlPath) != 0){
		cout<<"load xml file failed"<<endl;
		return false;
	}
	XMLElement* root=doc.RootElement();
	XMLElement* userNode=root->FirstChildElement("User");

	XMLElement*gender = userNode->FirstChildElement("Gender");
	XMLElement* age = doc.NewElement("Age");
	age->InsertFirstChild(doc.NewText("18"));
	userNode->InsertAfterChild(gender,age);

	XMLElement*mobile = userNode->FirstChildElement("Mobile");
	mobile->SetAttribute("Location","home");
	XMLElement* mobile1 = doc.NewElement("Mobile");
	mobile1->SetAttribute("Location","company");
	mobile1->InsertFirstChild(doc.NewText("188****8888"));
	userNode->InsertAfterChild(mobile,mobile1);

	return doc.SaveFile(xmlPath);
}
int test2(){
	/*创建*/
	createXML("bbb2.xml");
	/*增*/
	addXML1("bbb2.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	addXML2("bbb2.xml");/*在性别后面添加年龄，再添加一个号码*/
	/*删*/
	//deleteXML("bbb2.xml");/*删除第一个号码，删除第二个号码的属性*/
	/*改*/
	/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
	//changeXML("bbb2.xml");
	/*查*/
	//selectXML("bbb2.xml");/*将liangbaikai的信息打印出来*/
	return 0;
}
#if 0
//效果如下
<?xml version="1.0" encoding="UTF-8"?>
	<XMLUSER>
		<User Name="liangbaikai" Password="bbbbbb">
			<Gender>man</Gender>
			<Age>18</Age>
			<Mobile Location="home">188****6211</Mobile>
			<Mobile Location="company">188****8888</Mobile>
			<Email>1157***657@qq.com</Email>
		</User>
		<User Name="Wenbaikai" Password="aaaaa">
			<Mobile>166****6666</Mobile>
		</User>
	</XMLUSER>
#endif
//删
int deleteXML(const char* xmlPath){
	XMLDocument doc;
	if(doc.LoadFile(xmlPath) != 0){
		cout<<"load xml file failed"<<endl;
		return false;
	}
	XMLElement* root=doc.RootElement();
	XMLElement* userNode=root->FirstChildElement("User");
	XMLElement* mobile = userNode->FirstChildElement("Mobile");
	userNode->DeleteChild(mobile);
	XMLElement* mobile1 = userNode->FirstChildElement("Mobile");
	mobile1->DeleteAttribute("Location");
	return doc.SaveFile(xmlPath);
}
int test3(){
	/*创建*/
	createXML("bbb3.xml");
	/*增*/
	addXML1("bbb3.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	addXML2("bbb3.xml");/*在性别后面添加年龄，再添加一个号码*/
	/*删*/
	deleteXML("bbb3.xml");/*删除第一个号码，删除第二个号码的属性*/
	/*改*/
	/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/	
	//changeXML("bbb3.xml");
	/*查*/
	//selectXML("bbb3.xml");/*将liangbaikai的信息打印出来*/
	return 0;
}
#if 0
效果如下
<?xml version="1.0" encoding="UTF-8"?>
<XMLUSER>
	<User Name="liangbaikai" Password="bbbbbb">
		<Gender>man</Gender>
		<Age>18</Age>
		<Mobile>188****8888</Mobile>
		<Email>1157***657@qq.com</Email>
	</User>
	<User Name="Wenbaikai" Password="aaaaa">
		<Mobile>166****6666</Mobile>
	</User>
</XMLUSER>
#endif
//改
int changeXML(const char* xmlPath){
	XMLDocument doc;
	if(doc.LoadFile(xmlPath)!=0){
		cout<<"load xml file failed"<<endl;
		return false;
	}
	XMLElement* root=doc.RootElement();
	XMLElement* userNode=root->FirstChildElement("User");
	while(userNode != NULL){
		if( 0 == strncmp("liangbaikai",(userNode->Attribute("Name")),11)){
			userNode->FirstChildElement("Age")->SetText("10000");
			userNode = userNode->NextSiblingElement();
		}else if(( 0 == strncmp("Wenbaikai",(userNode->Attribute("Name")),11))){
			userNode->FirstChildElement("Mobile")->SetText("166****8888");
			userNode = userNode->NextSiblingElement();
		}else{
			userNode = userNode->NextSiblingElement();
		}
	}
	return doc.SaveFile(xmlPath);
}
int test4()
{
	/*创建*/
	createXML("bbb4.xml");
	/*增*/
	addXML1("bbb4.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	addXML2("bbb4.xml");/*在性别后面添加年龄，再添加一个号码*/
	/*删*/
	deleteXML("bbb4.xml");/*删除第一个号码，删除第二个号码的属性*/
	/*改*/
	/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
	changeXML("bbb4.xml");
	/*查*/
	//selectXML("bbb4.xml");/*将liangbaikai的信息打印出来*/
	return 0;
}
#if 0
效果如下
<?xml version="1.0" encoding="UTF-8"?>
<XMLUSER>
	<User Name="liangbaikai" Password="bbbbbb">
		<Gender>man</Gender>
		<Age>10000</Age>
		<Mobile>188****8888</Mobile>
		<Email>1157***657@qq.com</Email>
	</User>
	<User Name="Wenbaikai" Password="aaaaa">
		<Mobile>166****8888</Mobile>
	</User>
</XMLUSER>
#endif

//查
int selectXML(const char* xmlPath){
	XMLDocument doc;
	if(doc.LoadFile(xmlPath)!=0){
		cout<<"load xml file failed"<<endl;
		return false;
	}
	XMLElement* root=doc.RootElement();
	XMLElement* userNode=root->FirstChildElement("User");
	while(userNode != NULL){
		if( 0 == strncmp("liangbaikai",(userNode->Attribute("Name")),11)){
			cout << userNode->Attribute("Name") << endl;
			cout << userNode->Attribute("Password") << endl;
			cout << userNode->FirstChildElement("Age")->GetText() << endl;
			cout << userNode->FirstChildElement("Gender")->GetText() << endl;
			cout << userNode->FirstChildElement("Mobile")->GetText() << endl;
			cout << userNode->FirstChildElement("Email")->GetText() << endl;
			userNode = userNode->NextSiblingElement();
		}else{
			userNode = userNode->NextSiblingElement();
		}
	}
	return 0;
}

int test5(){
	/*创建*/
	createXML("bbb5.xml");
	/*增*/
	addXML1("bbb5.xml");/*添加性别，号码，邮箱*/ /*再添加一个用户*/
	addXML2("bbb5.xml");/*在性别后面添加年龄，再添加一个号码*/
	/*删*/
	deleteXML("bbb5.xml");/*删除第一个号码，删除第二个号码的属性*/
	/*改*/
	/*将liangbaikai的年龄改为10000岁，将wenbaikai的号码改为8888结尾*/
	changeXML("bbb5.xml");
	/*查*/
	selectXML("bbb5.xml");/*将liangbaikai的信息打印出来*/
	return 0;
}
int main(){
	test5();
}
#if 0
效果如下
liangbaikai
bbbbbb
10000
man
188****8888
1157***657@qq.com
#endif
