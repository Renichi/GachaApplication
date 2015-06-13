#pragma once
#include "DxLib.h"
#include "definer.h"
#include "DateBase.h"
#include "ScoreDraw.h"
#include <String>

class server {
public:
	server();
	~server();
	void initialize();
	void running();
	void finitialize();
	int getNetHandle();
	void readAdress( DateBase& adress );
	int normalGacha();
	int premiumGacha();
	void chageRate();
private:
	int _NetHandle[ 7 ];
	int _clientNum;
	std::string clientStatus[ 7 ];
	DateBase* _db;
	ScoreDraw* _sd;
	DatePack* _dp;
	bool _secretFlag;
};

