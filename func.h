#ifndef __FUNC_H__
#define __FUNC_H__
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <unordered_map>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <json/json.h>
#include <stack>
#include <ctype.h>
#include <algorithm>

#include "stdio.h"
//#include "../cppjieba/include/cppjieba/Jieba.hpp"
#include "tinyxml2.h"

#define ARGS_CHECK(argc,num) {if(argc!=num){printf("error args\n");return -1;}}
#define FSTREAM_CHECK(fstream) {if(!fstream.is_open()){printf("error fstream\n");}}

using namespace tinyxml2;
using std::fstream;
using std::ios;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::unordered_map;
using std::pair;
using std::vector;
using std::set;
using std::queue;
using std::priority_queue;
using std::istringstream;
using std::stringstream;
using std::stack;

//候选词队列节点，用于候选词优先级队列
class QueueNode{
public:	
	QueueNode(string word,int frequency)
	: _word(word),_frequency(frequency)
	{};
	void setDifferentDegree(int differentDegree){
		_differentDegree=differentDegree;
	}
	string getWord()const {
		return _word;
	}
	int getFrequency()const{
		return _frequency;
	}
	int getDifferentDegree()const{
		return _differentDegree;
	}
	void print()const{
		cout<<_word<<" "<<_frequency<<" "<<_differentDegree<<endl;
	}
	// < 运算符重载
	bool operator <(const QueueNode&) const;
	//赋值运算符重载
	QueueNode& operator =(const QueueNode&);
private:
	string _word;//候选词
	int _frequency;//词频
	int _differentDegree;//与目标单词的差别度
};

//用于内存Cache的链表和map
class LRUCache{
	//内存Cache的链表节点，双向链表
	struct CacheNode{
		CacheNode(string key,string json)
		: _key(key),_json(json),_next(nullptr),_last(nullptr)
		{}

		string _key;
		string _json;
		CacheNode* _next;
		CacheNode* _last;
	};		
public:
	LRUCache(size_t capacity=10)
	: _QueHead(nullptr),_QueTail(nullptr),_QueLen(0),_Capacity(capacity)
	{}
	//返回队列长度
	size_t size() const { return _QueLen;}
	//查找Cache中有无关键字
	bool exist(string key) const{
		auto it=_keys.find(key);
		if(it==_keys.end()){//Cache中无该关键词
			return false;
		}else{//Cache中有该关键词
			return true;
		}
	}
	//队列是否已满
	bool full() const {
		if(_QueLen<_Capacity){//队列未满
			return false;
		}else{//队列已满
			return true;
		}
	}
	//队列是否为空
	bool empty() const{
		if(_QueLen==0){//队列为空
			return true;
		}else{//队列不空
			return false;
		}
	}
	//将队列中的信息打印
	void print()const{
		cout<<"队列长度="<<_QueLen<<endl;
		cout<<"队列容量="<<_Capacity<<endl;
		cout<<"队列节点依次是（正序）："<<endl;
		CacheNode* pCurNode=_QueHead;
		while(pCurNode!=nullptr){
			cout<<pCurNode->_key<<" "<<pCurNode->_json<<endl;
			pCurNode=pCurNode->_next;
		}
		cout<<"队列节点依次是（倒序）："<<endl;
		pCurNode=_QueTail;
		while(pCurNode!=nullptr){
			cout<<pCurNode->_key<<" "<<pCurNode->_json<<endl;
			pCurNode=pCurNode->_last;
		}
		cout<<"map中的节点："<<endl;
		for(auto it=_keys.begin();it!=_keys.end();++it){
			cout<<it->first<<" "<<it->second->_json<<endl;
		}
	}
	//删除尾节点
	void deleteTailNode();
	//插入一个新的节点
	void insert(string key,string json);
	//访问一个已存在的节点，返回其json字符串
	string getJson(string key);
	//将LRUCache中的cache转为json风格字符串
	string output();
	//将json风格字符串转为LRUCache内的数据
	void input(string json);
private:
	CacheNode* _QueHead;//队列头
	CacheNode* _QueTail;//队列尾
	size_t _QueLen;//队列长度
	size_t _Capacity;//容量
	map<string,CacheNode*> _keys;
};
//输入语料，输出字典
void wordFrequency(string corpusFile,string dictionaryFile);
///输入字典文件，输出索引文件
void createIndex(string dictionaryFile,string indexFile);
//读入字典文件和索引文件
void loadDictionaryIndex(string dictionaryFile,string indexFile,vector<pair<string,int>> &dictionary,unordered_map<string,set<int>> &index);
//输入3个数，返回最小值
int minThreenum(int num1,int num2,int num3);
//返回一个字符所占的字节数
size_t nBytesCode(const char ch);
//返回一个字符串中的字符数
size_t length(string str);
//输入一个字符串返回一个存储该字符串字符的vector<string>
void getCharFromString(string str,vector<string> &vecStr);
//输入两个字符串，返回两字符串的最小编辑距离
size_t minLevenshtein(string str1,string str2);
//用set来存储要查询单词所含的字母
void getIndexChar(set<string> &setStr,string str);
//用set来存储与要查询单词含相同字母的候选单词
void getIndexWord(set<int> &setInt,set<string> &setStr,unordered_map<string,set<int>> &index);
//用优先级队列来获得关联度最高的前n个单词
void getPriorityQueue(
		set<int> &setInt,string str,
		vector<pair<string,int>> &dictionary,
		priority_queue<QueueNode> &priQue,
		int queLen);
//输入文件，要查询的单词，队列长度，输出队列
void getCandidateWords(string dictionaryFile,string indexFile,string word,
		stack<QueueNode> &staQue,int queLen);
//将string类型的json写入到文件中
void writeInFile(string json,string file);
//将文件中全部数据读取到一个string，返回该string
string readFromFile(string file);
//将一个字符串用jieba分词放入map中
int cutStringWithJieba(string str,vector<string> &words);
#endif
