#include "client.h"


client::client() {
}


client::~client() {
}

//初期化処理
void client::Initialize( ) {
	//変数の初期化
	 unsigned Cr = GetColor( 255 , 255 , 255 );
	 char ip[ 30 ] = { 0 };
     char InputChar;
	 int count = 0;

	 //IPアドレスの入力
	 while( !ProcessMessage() && ( CheckHitKey( KEY_INPUT_RETURN ) == 0 ) ) {
		DrawString( 250 , 240 - 32 , "サーバのIPアドレスを入力してください" , Cr );
		// 文字入力バッファから文字を取得する
         InputChar = GetInputChar( TRUE ) ;
        // 操作コード以外の文字入力があった場合のみ表示処理を行う
        if( InputChar != 0 && InputChar >= CTRL_CODE_CMP ) {
            // 画面の消去
            ClearDrawScreen() ;
            // 文字の保存
            ip[ count ] = InputChar ;
			count++;
            // 描画
            DrawString( 312 , 232 , ip , GetColor( 255 , 255 , 255 )  ) ;
		}
	 }
	 //入力データを_Ipに適用
	 std::string str;
	 int vaPlus[ 4 ];
	 int vaCount = 0;

	 for ( int i = 0; i < 20; i++ ) {
		 if ( ip[ i ] == '.' || ip[ i ] == '\0' ) {
			vaPlus[ vaCount ] = std::stoi(str);
			vaCount++;
			str.begin( );
			str.erase( );
			if ( vaCount == 4 ) {
				break;
			}
			continue;
		 }
		str.append( 1, ip[ i ] );
	 }

	 _Ip.d1 = ( unsigned char )vaPlus[ 0 ];
	 _Ip.d2 = ( unsigned char )vaPlus[ 1 ];
	 _Ip.d3 = ( unsigned char )vaPlus[ 2 ];
	 _Ip.d4 = ( unsigned char )vaPlus[ 3 ];
}

void client::running() {
	// データ送信
	int NetHandle;
	int DataLength ;        // 受信データ量保存用変数
	char StrBuf[ 256 ] ;    // データバッファ

	NetHandle = ConnectNetWork( this->getIP( ), 9850 ) ;
    //NetWorkSend( NetHandle , "繋がったか～！？" , 17 ) ;

	while( true ) {
		if ( !ProcessMessage() && ( CheckHitKey( KEY_INPUT_A ) == 1  ) ) {
			DatePack dp;
			dp.command = 0;
			NetWorkSend( NetHandle , (void*)&dp, 30 ) ;
			break;
		}
	}

    // データがくるのを待つ
    while( !ProcessMessage() )  {
        // 取得していない受信データ量を得る
        DataLength = GetNetWorkDataLength( NetHandle ) ;

        // 取得してない受信データ量が０じゃない場合はループを抜ける
        if( DataLength != 0 ) break ;
    }

    // データ受信
    NetWorkRecv( NetHandle , StrBuf , DataLength ) ;    // データをバッファに取得

    // 受信したデータを描画
    DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

   
}

IPDATA client::getIP( ) {
	return _Ip;
}
