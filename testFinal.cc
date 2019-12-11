#include "func.h"

void test(string fileName){
	XMLDocument doc;
	XMLError errXml=doc.LoadFile(fileName.c_str());
	if(XML_SUCCESS==errXml){
		const char* txt;
		XMLElement* Rss=doc.RootElement();//rss
		XMLElement* Channel=Rss->FirstChildElement("channel");//channel
		//------------------------------------------------------------------------
		XMLElement* Title=Channel->FirstChildElement("title");//title
		XMLElement* Link=Channel->FirstChildElement("link");//link
		XMLElement* Description=Channel->FirstChildElement("description");//description
		txt=Title->GetText();
		if(txt==nullptr){
			cout<<"title: nullptr"<<endl;
		}else{
			cout<<"title: "<< txt <<endl;
		}
		txt=Link->GetText();
		if(txt==nullptr){
			cout<<"link: null"<<endl;
		}else{
			cout<<"link: "<< txt <<endl;
		}
		
		if(Description->GetText()==nullptr){
			cout<<"description: null"<<endl;
		}else{
			cout<<"description: "<<Description->GetText() <<endl;
		}

		//XMLElement* elmtItem=elmtChannel->LastChildElement("item");//item
		//XMLElement* elmtAuthor=elmtItem->FirstChildElement();//author
		//XMLElement* elmtLink=elmtChannel->FirstChildElement("link");

		string s;
		XMLElement* Item=Channel->FirstChildElement("item");//item
		while(Item){
			cin>>s;
			Title=Item->FirstChildElement("title");
			Link=Item->FirstChildElement("link");
			Description=Item->FirstChildElement("description");
			cout<<"title: "<< Title->GetText() <<endl;
			cout<<"link: "<< Link->GetText() <<endl;
			cout<<"description: "<<Description->GetText()<<endl;
			Item=Item->NextSiblingElement("item");
		}
		//const char* pTitle=elmtTitle->GetText();
		//printf("%s",pTitle);
		//XMLElement* elmtDescription=elmtTitle->NextSiblingElement("description");
		//const char* pDescription=elmtDescription->GetText();
		//printf("%s",pDescription);
	}
}

int main(){
	string fileName;
	cin>>fileName;
	test(fileName);
}
