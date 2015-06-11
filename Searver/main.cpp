#include "DxLib.h"
#include "server.h"
#include "ScoreDraw.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
	int NetHandle;
   
    IPDATA Ip ;            // �ڑ���h�o�A�h���X�f�[�^
	int ipNum = 0;
	char buf[ 256 ];

	server* ps = new server();
	ScoreDraw* psd = new ScoreDraw( );

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
        return -1;    // �G���[���N�����璼���ɏI��
    }

	NetHandle = -1;
	ps->initialize();
	

    while ( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
        // �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
		NetHandle = ps->getNetHandle();
		NetHandle = 0;
        if ( NetHandle != -1 ) {
			break;
		}
    }

	
    // �ڑ�����Ă����玟�ɐi��
    if( NetHandle != -1 ) {
		while( true ) {
			ClearDrawScreen( );
			psd->update( );
			ps->running( );
			
		}
    }

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}