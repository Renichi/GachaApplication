#include "server.h"


server::server() {
	clientStatusA = "OFFLINE";
	_dp = new DatePack;
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
			_NetHandleA = NetHandle;
			clientStatusA = "ONLINE";
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30,(  "CLIENT_A:" + clientStatusA ).c_str( ), GetColor(255, 255, 255));

		
	}
	
	// 接続の受付を終了する
	StopListenNetWork();
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(NetHandle, &Ip);
}

void server::running( ) {
	int NetHandle,LostHandle;
    int DataLength ;            // 受信データ量保存用変数

	NetHandle = this->getNetHandle( ); 

	 // データが送られて来るまで待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量が０以外のときはループから抜ける
            if( GetNetWorkDataLength( NetHandle ) != 0 ) {
				break;
			}
        }

        // データ受信
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // データの量を取得

		NetWorkRecv( NetHandle , _dp , DataLength );    // データをバッファに取得

		if ( _dp->command == 0 ) {
			_db->update( 1, 0, 0, 0 );
			NetWorkSend( NetHandle , "もらったよ", 30 ) ;
		}

		_dp->command = 1;

        // 受信したデータを描画
        //DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // 受信成功のデータを送信
       //NetWorkSend( NetHandle , "繋がったぞ～！！" , 17 ) ;

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
	return _NetHandleA;
}