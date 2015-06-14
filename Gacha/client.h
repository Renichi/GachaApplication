#pragma once
#include "DxLib.h"
#include "definer.h"
#include <string>

class client {
public:
	client();
	~client();
	void Initialize( );
	void running( );
	void finitialize( );
	IPDATA getIP( );
	void receiveDate();
private:
	char _StrBuf[ 256 ];  //データバッファ
	IPDATA _Ip;           //接続用IPアドレスデータ
	int _NetHandle;       //ネットワークハンドル
	int _DataLength;      //受信で0た量保存用変数
};

