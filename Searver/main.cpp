#include "DxLib.h"
#include "server.h"
#include "ScoreDraw.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
	int NetHandle;
   
    IPDATA Ip ;            // 接続先ＩＰアドレスデータ
	int ipNum = 0;
	char buf[ 256 ];

	server* ps = new server();
	ScoreDraw* psd = new ScoreDraw( );

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが起きたら直ちに終了
    }

	NetHandle = -1;
	ps->initialize();
	

    while ( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
        // 新しい接続があったらそのネットワークハンドルを得る
		NetHandle = ps->getNetHandle();
		NetHandle = 0;
        if ( NetHandle != -1 ) {
			break;
		}
    }

	
    // 接続されていたら次に進む
    if( NetHandle != -1 ) {
		while( true ) {
			ClearDrawScreen( );
			psd->update( );
			ps->running( );
			
		}
    }

    DxLib_End() ;    // ＤＸライブラリ使用の終了処理

    return 0 ;    // ソフトの終了
}