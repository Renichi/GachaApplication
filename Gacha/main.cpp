#include "DxLib.h"
#include "client.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
    char StrBuf[ 256 ] ;    // データバッファ
    int NetHandle ;        // ネットワークハンドル
    int DataLength ;        // 受信データ量保存用変数

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
         return -1;    // エラーが起きたら直ちに終了
    }

	client* pClient = new client( );
	pClient->Initialize( );

    // ＩＰアドレスを設定( ここにある４つのＩＰ値は仮です )
   /* Ip.d1 = 172 ;
    Ip.d2 = 18 ;
    Ip.d3 = 10  ;
    Ip.d4 = 122 ;*/

    // 通信を確立
    NetHandle = ConnectNetWork( pClient->getIP( ), 9850 ) ;

    // 確立が成功した場合のみ中の処理をする
    if( NetHandle != -1 )
    { 
        // データ送信
        NetWorkSend( NetHandle , "繋がったか～！？" , 17 ) ;

        // データがくるのを待つ
        while( !ProcessMessage() )
        {
            // 取得していない受信データ量を得る
            DataLength = GetNetWorkDataLength( NetHandle ) ;

            // 取得してない受信データ量が０じゃない場合はループを抜ける
            if( DataLength != 0 ) break ;
        }

        // データ受信
        NetWorkRecv( NetHandle , StrBuf , DataLength ) ;    // データをバッファに取得

        // 受信したデータを描画
        DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // キー入力待ち
        WaitKey() ;

        // 接続を断つ
        CloseNetWork( NetHandle ) ;
    }

    DxLib_End() ;    // ＤＸライブラリ使用の終了処理

    return 0 ;    // ソフトの終了
}