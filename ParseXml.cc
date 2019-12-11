#include "ParseXml.h"

string ParserCardOperation(
		XMLNode* root, 
		const char* nodeName, 
		std::size_t count, 
		vector<vector<string>>& allTextResult)
{
	if (nullptr == root){
		return "XML_ERROR_PARSING_ROOT";
	}
	XMLElement* node = nullptr;
	std::size_t i = 0;
	bool isFindAll = count == -1 ? true : false;
	do{
		if (i == 0){
			node = root->FirstChildElement(nodeName);
		}else{
			//返回当前元素同级的元素
			node = node->NextSiblingElement(nodeName);
		}
		
		if (nullptr == node){
			return "XML_ERROR_PARSING_ELEMENT";
		}

		const char* text = node->ToElement()->GetText();
		string str(text);
		vector<string> s;
		s.push_back(str);
		allTextResult.push_back(s);
		i++;
	} while (isFindAll || (!isFindAll && i < count));

	return "XML_SUCCESS";
}

int ParserXml(const char* fileName, vector<string>& result) {
	XMLDocument xmlDoc;
	XMLError tmpResult = xmlDoc.LoadFile(fileName);
	if (tmpResult != XML_SUCCESS){
		return tmpResult;
	}
	XMLNode* root = xmlDoc.RootElement();
	ParserXmlOperation(root, false, result);
	return XML_SUCCESS;
}

void ParserXmlOperation(XMLNode* node, bool flag, vector<string>& result)
{
	XMLNode* element;
	if (!flag){
		element = node->FirstChildElement();
	}else{
		element = node->NextSiblingElement();
	}
	if (element != nullptr){
		if (element->ToElement()->GetText() == nullptr){
			ParserXmlOperation(element, false, result);
		}else{
			string text(element->ToElement()->GetText());
			result.push_back(text);
			ParserXmlOperation(element, true, result);
		}
	}else{
		if (strcmp("Root", node->Value()) != 0) {
			ParserXmlOperation(node->Parent(), true, result);
		}
	}
}

int ParserXmlWithNodeValue(const char* fileName, map<string,string>& result)
{
	XMLDocument xmlDoc;
	XMLError tmpResult = xmlDoc.LoadFile(fileName);
	if (tmpResult != XML_SUCCESS){
		return tmpResult;
	}
	XMLNode* root = xmlDoc.RootElement();
	ParserXmlOperationWithNodeValue(root, false, result);
	return XML_SUCCESS;
}

void ParserXmlOperationWithNodeValue(XMLNode* node, bool flag, map<string,string>& result)
{
	XMLNode* element;
	if (!flag){
		element = node->FirstChildElement();
	}else{
		element = node->NextSiblingElement();
	}
	if (element != nullptr){
		if (element->ToElement()->GetText() == nullptr){
			ParserXmlOperationWithNodeValue(element, false, result);
		}else{
			string text(element->ToElement()->GetText());
			string keyValue = element->ToElement()->Value();
			result.insert(map<string, string>::value_type(keyValue, text));
			ParserXmlOperationWithNodeValue(element, true, result);
		}
	}else{
		if (strcmp("Root", node->Value()) != 0) {
			ParserXmlOperationWithNodeValue(node->Parent(), true, result);
		}
	}
}

bool ParserXmlWithNodeValue(string& _str, Result& _result)
{
	map<string, string> rsCards;
	int r = ParserXmlWithNodeValue(_str.c_str(), rsCards);
	if (r != XML_SUCCESS){
		return false;
	}
	map<string, string>::iterator rsCardsIter = rsCards.begin();
	vector<unsigned char> parsedCards;
	vector<uint16_t> parsedCounts;
	vector<unsigned char> parsedLeftCards;
	for (;rsCardsIter != rsCards.end();rsCardsIter++){
		string keyValue = (*rsCardsIter).first;
		if (keyValue == "Vesion"){
			_result.vesion = (*rsCardsIter).second;
		}else if (keyValue == "Cards"){
			ParserText((*rsCardsIter).second, ',', parsedCards);
		}else if (keyValue == "Count"){
			ParserText((*rsCardsIter).second, ',', parsedCounts);
		}else if (keyValue == "LeftCards"){
			ParserText((*rsCardsIter).second, ',', parsedLeftCards);
		}
	}
	
	if (!parsedCards.empty() && !parsedCounts.empty()){
		vector<uint16_t>::iterator countsIter = parsedCounts.begin();
		for (;countsIter != parsedCounts.end();countsIter++){
			_result.countsList.push_back((*countsIter));
		}
		if (parsedCounts.size() == 5){
			uint16_t index = 0;
			for (uint16_t i = 0;i < 4; i++){
				vector<unsigned char> tmpParsedCards;
				for (uint16_t j = 0;j < parsedCounts[i];j++){
					index = j + i * parsedCounts[i];
					tmpParsedCards.push_back(parsedCards[index]);
				}
				_result.cards[i] = tmpParsedCards;
			}
			vector<unsigned char> tmpRestedCards;
			for (uint16_t z = index; z <= index + parsedCounts[4];z++){
				tmpRestedCards.push_back(parsedCards[z]);
			}
			_result.restCardsList = tmpRestedCards;
		}
	}

	if (!parsedLeftCards.empty()){
		_result.outCardsList = parsedLeftCards;
	}
	return true;
}

bool ParserXml(string& _str, Result& _result)
{
	vector<string> rsCards;
	int r = ParserXml(_str.c_str(), rsCards);

	if (r != XML_SUCCESS){
		return false;
	}

	map<int, vector<unsigned char>> cards;
	for (size_t i = 0;i < rsCards.size();i++){
		vector<unsigned char> parsedCards;
		ParserText(rsCards[i], ',', parsedCards);
		if (i == 0){
			vector<unsigned char> baiDaCardList;
			baiDaCardList.push_back(parsedCards[0]);
			_result.baiDaCardList = baiDaCardList;
		}else if (i == rsCards.size()-1){
			_result.outCardsList = parsedCards;
		}else{
			_result.cards[i-1] = parsedCards;
		}
	}
	return true;
}

