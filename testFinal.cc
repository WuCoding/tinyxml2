#include "func.h"

void print(XMLElement* elem,string elemName){
	const char* txt;
	if(elem==nullptr){
		cout<<elemName<<" is null"<<endl;
	}else{
		txt=elem->GetText();
		if(txt==nullptr){
			cout<<elemName<<" :null"<<endl;
		}else{
			cout<<elemName<<": "<<txt<<endl;
		}
	}
}

void test(string fileName){
	XMLDocument doc;
	XMLError errXml=doc.LoadFile(fileName.c_str());
	if(XML_SUCCESS==errXml){
		XMLElement* Rss=doc.RootElement();//rss
		XMLElement* Channel=Rss->FirstChildElement("channel");//channel

		XMLElement* Title=Channel->FirstChildElement("title");//title
		XMLElement* Link=Channel->FirstChildElement("link");//link
		XMLElement* Description=Channel->FirstChildElement("description");//description
		XMLElement* Content=Channel->FirstChildElement("content");//content
		
		print(Title,"title");
		print(Link,"link");
		print(Description,"description");
		print(Content,"content");

		
#if 0
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

		txt=Description->GetText();	
		if(txt==nullptr){
			cout<<"description: null"<<endl;
		}else{
			cout<<"description: "<< txt <<endl;
		}
#endif

		//XMLElement* elmtItem=elmtChannel->LastChildElement("item");//item
		//XMLElement* elmtAuthor=elmtItem->FirstChildElement();//author
		//XMLElement* elmtLink=elmtChannel->FirstChildElement("link");

		string s;
		XMLElement* Item=Channel->FirstChildElement("item");//item
		while(Item){
			Title=Item->FirstChildElement("title");
			Link=Item->FirstChildElement("link");
			Description=Item->FirstChildElement("description");
			Content=Item->FirstChildElement("content");

			cin>>s;
			print(Title,"title");
			cin>>s;
			print(Link,"link");
			cin>>s;
			print(Description,"description");
			cin>>s;
			print(Content,"content");
#if 0
			if(txt==nullptr){
				cout<<"link: null"<<endl;
			}else{
				cout<<"link: "<< txt <<endl;
			}

			txt=Description->GetText();	
			if(txt==nullptr){
				cout<<"description: null"<<endl;
			}else{
				cout<<"description: "<< txt <<endl;
			}
#endif
			//cout<<"title: "<< Title->GetText() <<endl;
			//cout<<"link: "<< Link->GetText() <<endl;
			//cout<<"description: "<<Description->GetText()<<endl;
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
