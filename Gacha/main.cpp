#include "DxLib.h"
#include "client.h"
#include "DrawMain.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
   
    int NetHandle ;        // ネットワークハンドル

	ChangeWindowMode(false);
	SetGraphMode(1280, 1024, 32);

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
         return -1;    // エラーが起きたら直ちに終了
    }

	client* pClient = new client( );
	DrawMain* pDraw = new DrawMain();

	pClient->Initialize( );

    //通信を確立
    NetHandle = ConnectNetWork( pClient->getIP( ), 9850 ) ;
    // 確立が成功した場合のみ中の処理をする
    if( NetHandle != -1 ) { 
		while( true ) {
			pDraw->update( NetHandle );
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				break;
			}
		}
    }
    // 接続を断つ
    CloseNetWork( NetHandle ) ;

    DxLib_End() ;    // ＤＸライブラリ使用の終了処理

    return 0 ;    // ソフトの終了
}