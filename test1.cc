#include "func.h"

void test(){
	XMLDocument docXml;
	char const *pXml = "<Item>Hello World</Item>";
	XMLError errXml = docXml.Parse(pXml);
	if(XML_SUCCESS == errXml){
		XMLElement* elmtRoot = docXml.RootElement();
		if(elmtRoot){
			const char* pContent= elmtRoot->GetText();
			printf( "%s", pContent);
		}
	}
}

#if 0
<?xml version="1.0"?>  
<Group>
	<User>
		<Name>John</Name>
		<Age>18</Age>
	</User>
</Group>  
#endif

void test1(){
	XMLDocument docXml;
	XMLError errXml=docXml.LoadFile("example.xml");
	if(XML_SUCCESS==errXml){
		XMLElement* elmtRoot = docXml.RootElement();
		XMLElement *elmtUser = elmtRoot->FirstChildElement("User");
		XMLElement *elmtName = elmtUser->FirstChildElement("Name");
		if (elmtName){
			const char* pContent= elmtName->GetText();
			printf( "%s", pContent);
		}
		XMLElement *elmtAge = elmtName->NextSiblingElement();
		if (elmtAge){
			const char* pContent= elmtAge->GetText();
			printf( "%s", pContent);
		}
	}
}
int main(){
//	test();
	test1();
}
