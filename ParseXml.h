#pragma once

#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include <map>
#include "Result.h"
#include "DealXmlText.h"

using namespace tinyxml2;
using namespace std;

/*
 *	@brief 找到父节点root下名字为nodeName节点text
 * 	@description
 * 		count 为 -1时 获得所有的节点
 * 		count 为 正整数时 获得count个数前的所有节点
 * 		如果节点数小于count 相当于 输出所有节点
 * 		返回的状态:	"XML_ERROR_PARSING_ROOT"	包含nodeName的节点不存在
 * 				"XML_ERROR_PARSING_ELEMENT"	nodeName的节点不存在
 * 				"XML_SUCCESS"			成功找到需要的节点
 *	
 *	@param [XMLNode*] [root] [包含nodeName的父节点]
 * 	@param [const char*] [nodeName] [需要找的节点名字]
 * 	@param [std::size_t] [count] [要前几个这样的节点]
 * 	@param [vector<vector<string>>&] [allTextResult] [节点内所有的text文本]
 * 	
 * 	@return [string] [] [查找的状态]
 *
 * 	@attention
 */
std::string ParserCardOperation(
		tinyxml2::XMLNode* root, 
		const char* nodeName, 
		std::size_t count, 
		std::vector<std::vector<std::string>>& allTextResult
		);

/*
 * 	@brief 按照顺序解析出xml中所有的text
 * 	@description
 * 		解析的状态:	XML_SUCCESS	成功
 * 				其它		失败
 * 	@param [const char*] [path] [xml的文件名字]
 * 	@param [vector<vector<string>>&] [result] [得到所有text的集合]
 *
 * 	@return [int] [] [解析的状态]
 *
 * 	@attention
 */
int ParserXml(const char* fileName, std::vector<std::string>& result);

/*
 * 	@brief ParserXml实现的细节操作，根据头节点递归
 * 	@description
 * 		flag	true	找与这个节点同级别的节点
 * 			false	这个节点下的第一个元素节点
 * 	@param [XMLNode*] [node] [节点]
 * 	@param [bool] [flag] [用来判断是找这个节点下的第一个元素节点 还是 
 * 		找与这个节点同级别的节点]
 * 	@param [vector<vector<string>>&] [result] [得到所有text的集合]
 *
 * 	@return [] [] []
 *
 * 	@attention
 * 		通过判断最后是否回退到了root节点来结束递归，不然就死循环中
 */
void ParserXmlOperation(
		tinyxml2::XMLNode* node, 
		bool flag, 
		std::vector<std::string>& result
		);

/*
 * 	@brief 按照顺序解析出xml中所有的text
 * 	@description
 * 		解析的状态:	XML_SUCCESS  	成功
 * 				其它		失败
 * 	@param [const char*] [path] [xml的文件名字]
 * 	@param [map<string, string>&] [result] [得到所有text的集合和对应的node节点值]
 *
 * 	@return [int] [] [解析的状态]
 *
 * 	@attention
 */
int ParserXmlWithNodeValue(
		const char* fileName, 
		std::map<std::string,std::string>& result
		);
/*
 * 	@brief ParserXml实现的细节操作，根据头节点递归
 * 	@description
 * 		flag	true	找与这个节点同级别的节点
 * 			false	这个节点下的第一个元素节点
 * 	@param [XMLNode*] [node] [节点]
 * 	@param [bool] [flag] [用来判断是找这个节点下的第一个元素节点 
 * 		还是 找与这个节点同级别的节点]
 * 	@param [map<string, string>&] [result] [得到所有text的集合 和 对应的 node 节点值]
 *
 * 	@return [] [] []
 *
 * 	@attention
 * 	通过判断最后是否回退到了root节点来结束递归，不然就死循环中
 */
void ParserXmlOperationWithNodeValue(
		tinyxml2::XMLNode* node, 
		bool flag, 
		std::map<std::string, std::string>& result
		);

/*
 * 	@brief 按照顺序解析出xml中所有的text
 * 	@description
 * 		company
 * 	@param [string&] [_str] [xml的文件名字+地址]
 * 	@param [Result&] [_result] [得到cards所有结果]
 *
 * 	@return [bool] [] [解析的状态]
 *
 * 	@attention
 */
bool ParserXmlWithNodeValue(std::string& _str, Result& _result);

/*
 * 	@brief 按照顺序解析出xml中所有的text
 * 	@description
 * 		own
 * 	@param [string&] [_str] [xml的文件名字+地址]
 * 	@param [Result&] [_result] [得到cards所有结果]
 *
 * 	@return [bool] [] [解析的状态]
 *
 * 	@attention
 */
bool ParserXml(string& _str, Result& _result);

