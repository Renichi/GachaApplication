#include "DxLib.h"
#include "server.h"
#include "ScoreDraw.h"
#include "DateBase.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
	int ipNum = 0;

	server* ps = new server();
	ScoreDraw* psd = new ScoreDraw( );

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが起きたら直ちに終了
    }

	ps->initialize();

	DateBase* datebase = new DateBase( );

	ps->readAdress( *datebase );
	psd->readAdress( *datebase );
	while( true ) {
		ClearDrawScreen( );
		psd->update( );
		ps->running( );
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

    DxLib_End() ;    // ＤＸライブラリ使用の終了処理

    return 0 ;    // ソフトの終了
}