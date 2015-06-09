#pragma once
#include "DxLib.h"
#include <String>

class server {
public:
	server();
	~server();
	void initialize();
	void running();
	void finitialize();
	int getNetHandle();
private:
	int _NetHandleA;
	std::string clientStatusA;
};

