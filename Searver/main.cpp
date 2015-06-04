#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
    char StrBuf[ 256 ] ;        // データバッファ
    int NetHandle , LostHandle ;    // ネットワークハンドル
    int DataLength ;            // 受信データ量保存用変数
    IPDATA Ip ;            // 接続先ＩＰアドレスデータ
	IPDATA myIpAddress;
	int ipNum = 0;
	char buf[ 256 ];

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが起きたら直ちに終了
    }

	// IPアドレスの取得
	GetMyIPAddress( &myIpAddress );
	sprintf_s( buf, "IP Address = %d.%d.%d.%d", myIpAddress.d1, myIpAddress.d2, myIpAddress.d3, myIpAddress.d4 );

    // 接続してくるのを待つ状態にする
    PreparationListenNetWork( 9850 );

    // 接続してくるかＥＳＣキーが押されるまでループ
    NetHandle = -1;

    while ( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
        // 新しい接続があったらそのネットワークハンドルを得る
        NetHandle = GetNewAcceptNetWork();
        if ( NetHandle != -1 ) {
			break;
		}

		DrawString( 0, 0, buf, GetColor( 255, 255, 255 ) );
    }

    // 接続されていたら次に進む
    if( NetHandle != -1 )
    {
        // 接続の受付を終了する
        StopListenNetWork();

        // 接続してきたマシンのＩＰアドレスを得る
        GetNetWorkIP( NetHandle , &Ip );

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