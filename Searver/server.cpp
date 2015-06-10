#include "server.h"


server::server() {
	clientStatus[0] = "OFFLINE";
	clientStatus[1] = "OFFLINE";
	clientStatus[2] = "OFFLINE";
	clientStatus[3] = "OFFLINE";
	clientStatus[4] = "OFFLINE";
	clientStatus[5] = "OFFLINE";
	_dp = new DatePack;
	_clientNum;
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
			_clientNum++;
			clientStatus[ _clientNum ] = "ONLINE";
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

	 // データが送られて来るまで待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量が０以外のときはループから抜ける
			for (int i = 0; i < 6; i++) {
				if (GetNetWorkDataLength(_NetHandle[ i ]) != 0) {
					NetHandle = _NetHandle[i];
					break;
				}
			}
			if (NetHandle != 0) {
				break;
			}
        }
        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得
		NetWorkRecv( NetHandle , _dp , DataLength );    // データをバッファに取得
		if (_dp->command == 1) {
			_dp->prize = normalGacha();
			NetWorkSend(NetHandle, _dp, 30);
		}
		if (_dp->command == 2) {
			_dp->prize = premiumGacha();
			NetWorkSend(NetHandle, _dp, 30);
		}
		_dp->command = 0;

        // 受信したデータを描画
        //DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // 受信成功のデータを送信
       //NetWorkSend( NetHandle , "繋がったぞ〜！！" , 17 ) ;

        // 相手が通信を切断するまで待つ
        /*while( !ProcessMessage() )
        {
            // 新たに切断されたネットワークハンドルを得る
            LostHandle = GetLostNetWork() ;

            // 切断された接続が今まで通信してた相手だった場合ループを抜ける
            if( LostHandle == NetHandle ) break ;
        }

        // 切断確認表示
        DrawString( 0 , 16 , "切断しました" , GetColor( 255 , 255 , 255 ) ) ;
		*/

}

void server::readAdress( DateBase& adress) {
	_db = &adress;
}

int server::getNetHandle() {
	return _NetHandle[0];
}

int server::normalGacha() {
	//景品の倍率
	int prize;
	int rare_B_probability = 2389;
	int rare_A_probability = 6928;
	//ランダムの確立
	int random_probability = 10000;
	int probability = GetRand(10000);
	if (probability <= rare_B_probability) {
		prize = 1;
		_db->update(0, 1, 0, 0);
	} else {
		prize = 2;
		_db->update(1, 0, 0, 0);
	}
	return prize;
}

int server::premiumGacha() {
	int prize;
	int rare_S_probability = 125;
	int rare_C_probability = 558;
	int rare_B_probability = 2389;
	//ランダムの確立
	int random_probability = 10000;
	int probability = GetRand(10000);
	if (probability <= rare_S_probability) {
		prize = 3;
		_db->update(0, 0, 0, 1);
	}
	else if ( probability <= ( rare_S_probability + rare_C_probability)) {
		prize = 0;
		_db->update(0, 0, 1, 0);
	} else {
		prize = 1;
		_db->update(0, 1, 0, 0);
	}
	return prize;

}