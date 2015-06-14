#include "server.h"


server::server() {
	clientStatus[0] = "OFFLINE";
	clientStatus[1] = "OFFLINE";
	clientStatus[2] = "OFFLINE";
	clientStatus[3] = "OFFLINE";
	clientStatus[4] = "OFFLINE";
	clientStatus[5] = "OFFLINE";
	_dp = new DatePack;
	_sd = new ScoreDraw();
	_pPGacha = new PremiumGacha();
	_pNGacha = new NormalGacha();
	_clientNum;
	_secretFlag = false;
}


server::~server() {
}

void server::initialize() {
	char buf[256];
	int NetHandle;
	IPDATA myIpAddress;
	IPDATA Ip;            // 接続先ＩＰアドレスデータ

	// IPアドレスの取得
	GetMyIPAddress(&myIpAddress);
	sprintf_s(buf, "IP Address = %d.%d.%d.%d", myIpAddress.d1, myIpAddress.d2, myIpAddress.d3, myIpAddress.d4);
	// 接続してくるのを待つ状態にする
	PreparationListenNetWork(9850);

	// 接続してくるかＥＳＣキーが押されるまでループ
	NetHandle = -1;

	while (!ProcessMessage() && CheckHitKey(KEY_INPUT_RETURN) == 0) {
		ClearDrawScreen();
		// 新しい接続があったらそのネットワークハンドルを得る
		NetHandle = GetNewAcceptNetWork();
		if (NetHandle != -1) {
			_NetHandle[ _clientNum ] = NetHandle;
			clientStatus[ _clientNum ] = "ONLINE";
			_clientNum++;
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30, ("CLIENT_A:" + clientStatus[ 0 ] ).c_str( ), GetColor(255, 255, 255));
		DrawString(0, 50, ("CLIENT_B:" + clientStatus[ 1 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 70, ("CLIENT_C:" + clientStatus[ 2 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 90, ("CLIENT_D:" + clientStatus[ 3 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 110, ("CLIENT_E:" + clientStatus[ 4 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 130, ("CLIENT_F:" + clientStatus[ 5 ]).c_str(), GetColor(255, 255, 255));
	}
	// 接続の受付を終了する
	StopListenNetWork();
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(NetHandle, &Ip);
}

void server::running( ) {
	int NetHandle;
    int DataLength ;            // 受信データ量保存用変数

	NetHandle = this->getNetHandle( ); 
	chageRate();
	if (!_secretFlag) {
		if (CheckHitKey(KEY_INPUT_S) == 1) {
			_db->addSecret();
		}
	}
    // 取得していない受信データ量が０以外のときは処理に入る
	for (int i = 0; i < 6; i++) {
		if (GetNetWorkDataLength(_NetHandle[ i ]) != 0) {
			NetHandle = _NetHandle[i];
			// データ受信
			DataLength = GetNetWorkDataLength(NetHandle);    // データの量を取得
			NetWorkRecv(NetHandle, _dp, DataLength);    // データをバッファに取得

			if (_dp->command == 1) {
				_dp->prize = _pNGacha->playGacha(_db);
				NetWorkSend(NetHandle, _dp, 30);
				_db->addPlayCount();
			}
			else if (_dp->command == 2) {
				_dp->prize = _pPGacha->playGacha(_db);
				NetWorkSend(NetHandle, _dp, 30);
				_db->addPlayCount();
			}
			_dp->command = 0;
		}
	}
        
}

void server::readAdress( DateBase& adress) {
	_db = &adress;
}

int server::getNetHandle() {
	return _NetHandle[0];
}

void server::chageRate() {
	if (CheckHitKey(KEY_INPUT_1) == 1) {
		_db->updateRate(1, 0, 0, 0 );
	}
	if (CheckHitKey(KEY_INPUT_2) == 1) {
		_db->updateRate(-1, 0, 0, 0 );
	}
	if (CheckHitKey(KEY_INPUT_3) == 1) {
		_db->updateRate(0, 1, 0, 0 );
	}
	if (CheckHitKey(KEY_INPUT_4) == 1) {
		_db->updateRate(0, -1, 0, 0 );
	}
	if (CheckHitKey(KEY_INPUT_5) == 1) {
		_db->updateRate(0, 0, 1, 0 );
	}
	if (CheckHitKey(KEY_INPUT_6) == 1) {
		_db->updateRate(0, 0, -1, 0 );
	}
	if (CheckHitKey(KEY_INPUT_G) == 1) {
		for (int i = 0; i < _clientNum; i++) {
			_dp->fes = 1;
			NetWorkSend(_NetHandle[ i ], _dp, 30);
			_db->updateRate(0, 1000, 4000, 500);
		}
	}
}