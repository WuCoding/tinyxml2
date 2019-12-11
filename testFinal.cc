#include "func.h"

void test(){
	XMLDocument docXml;
	XMLError errXml=docXml.LoadFile("coolshell.xml");
	if(XML_SUCCESS==errXml){
		XMLElement* elmtRoot=docXml.RootElement();//rss
		XMLElement* elmtChannel=elmtRoot->FirstChildElement();//channel
		XMLElement* elmtItem=elmtChannel->LastChildElement("item");//item
		//XMLElement* elmtAuthor=elmtItem->FirstChildElement();//author
		//XMLElement* elmtLink=elmtChannel->FirstChildElement("link");
		XMLElement* elmtTitle=elmtItem->FirstChildElement("title");
		const char* pTitle=elmtTitle->GetText();
		printf("%s",pTitle);
		XMLElement* elmtDescription=elmtTitle->NextSiblingElement("description");
		const char* pDescription=elmtDescription->GetText();
		printf("%s",pDescription);
	}
}

int main(){
	test();
}
