#include "server.h"


server::server() {
	clientStatusA = "OFFLINE";
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
		// 新しい接続があったらそのネットワークハンドルを得る
		NetHandle = GetNewAcceptNetWork();
		if (NetHandle != -1) {
			_NetHandleA = GetNewAcceptNetWork();
			clientStatusA = "ONLINE";
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30,(  "CLIENT_A:" + clientStatusA ).c_str( ), GetColor(255, 255, 255));

		ClearDrawScreen();
	}
	// 接続の受付を終了する
	StopListenNetWork();
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(NetHandle, &Ip);
}

int server::getNetHandle() {
	int _NetHandleA;
}