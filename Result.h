#pragma once
#include "stdafx.h"

class Result{
public:
	Result();
	Result(
		std::vector<unsigned char> _baiDaCardList,
	       	std::map<int, std::vector<unsigned char>>_cards);
	virtual ~Result();
public:
	std::vector<unsigned char> baiDaCardList;	//百塔牌的值
	std::map<int,vector<unsigned char>> cards;	//根据xml排的顺序存放配的牌
	std::vector<unsigned char> restCardsList;	//剩余的牌
	std::vector<unsigned char> outCardsList;	//不用的牌
	std::vector<uint16_t> countsList;		//每个玩家手牌数量，剩余牌数量
	string vesion;					//版本
public:
	void View();
	void Clear();
};
