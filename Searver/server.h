#pragma once
#include "DxLib.h"
#include "definer.h"
#include "DateBase.h"
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
private:
	int _NetHandle[ 6 ];
	int _clientNum;
	std::string clientStatus[ 6 ];
	DateBase* _db;
	DatePack* _dp;
};

