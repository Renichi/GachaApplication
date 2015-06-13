#include "DxLib.h"
#include "server.h"
#include "ScoreDraw.h"
#include "DateBase.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
	int NetHandle;
   
	int ipNum = 0;

	server* ps = new server();
	ScoreDraw* psd = new ScoreDraw( );

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
        return -1;    // �G���[���N�����璼���ɏI��
    }

	NetHandle = -1;
	ps->initialize();

	DateBase* datebase = new DateBase( );

	ps->readAdress( *datebase );
	//psd->readAdress( *datebase );
	
	while( true ) {
		ClearDrawScreen( );
		//psd->update( );
		ps->running( );
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}