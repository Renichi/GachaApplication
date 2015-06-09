#include "DxLib.h"
#include "server.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
    char StrBuf[ 256 ] ;        // データバッファ
    int NetHandle , LostHandle ;    // ネットワークハンドル
    int DataLength ;            // 受信データ量保存用変数
    IPDATA Ip ;            // 接続先ＩＰアドレスデータ
	int ipNum = 0;
	char buf[ 256 ];

	server* ps = new server();

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが起きたら直ちに終了
    }

	ps->initialize();

    while ( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
        // 新しい接続があったらそのネットワークハンドルを得る
		NetHandle = ps->getNetHandle();
        if ( NetHandle != -1 ) {
			break;
		}
    }

    // 接続されていたら次に進む
    if( NetHandle != -1 ) {
   
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
        NetWorkRecv( NetHandle , StrBuf , DataLength );    // データをバッファに取得

        // 受信したデータを描画
        DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // 受信成功のデータを送信
        NetWorkSend( NetHandle , "繋がったぞ～！！" , 17 ) ;

        // 相手が通信を切断するまで待つ
        while( !ProcessMessage() )
        {
            // 新たに切断されたネットワークハンドルを得る
            LostHandle = GetLostNetWork() ;

            // 切断された接続が今まで通信してた相手だった場合ループを抜ける
            if( LostHandle == NetHandle ) break ;
        }

        // 切断確認表示
        DrawString( 0 , 16 , "切断しました" , GetColor( 255 , 255 , 255 ) ) ;

        // キー入力待ち
        WaitKey() ;
    }

    DxLib_End() ;    // ＤＸライブラリ使用の終了処理

    return 0 ;    // ソフトの終了
}