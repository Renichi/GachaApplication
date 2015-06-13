#pragma once
#include "DxLib.h"
#include "definer.h"
#include "DateBase.h"
#include "ScoreDraw.h"
#include "PremiumGacha.h"
#include "NormalGacha.h"
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
	bool _secretFlag;
	int _NetHandle[ 7 ];
	int _clientNum;
	std::string clientStatus[ 7 ];
	DateBase* _db;
	DatePack* _dp;
	ScoreDraw* _sd;
	PremiumGacha* _pPGacha;
	NormalGacha* _pNGacha;
};

