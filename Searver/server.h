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
private:
	int _NetHandleA;
	std::string clientStatusA;
	DateBase* _db;
	DatePack* _dp;
};

