#include "func.h"
void example1()
{
	XMLDocument doc;
	doc.LoadFile("test.xml");
	const char* content= doc.FirstChildElement("Hello")->GetText();
	printf( "Hello,%s", content );
}

int test()
{
	example1();
	return 0;
}

void example2()
{
	XMLDocument doc;
	doc.LoadFile("test2.xml");
	XMLElement *scene=doc.RootElement();
	XMLElement *node=scene->FirstChildElement("node");
	while (node){
		XMLElement *nodeChild=node->FirstChildElement();
		const char* content;
		const XMLAttribute *attributeOfNode = node->FirstAttribute();
		cout<< attributeOfNode->Name() << ":" 
			<< attributeOfNode->Value() << endl;
		while(nodeChild){
			content=nodeChild->GetText();
			nodeChild=nodeChild->NextSiblingElement();
			cout<<content<<endl;
		}
		node=node->NextSiblingElement();
	}
}
int main()
{
	example2();
	return 0;
}
