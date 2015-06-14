#include "DxLib.h"
#include "client.h"
#include "DrawMain.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
   
    int NetHandle ;        // �l�b�g���[�N�n���h��

	ChangeWindowMode(false);
	SetGraphMode(1280, 1024, 32);

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
         return -1;    // �G���[���N�����璼���ɏI��
    }

	client* pClient = new client( );
	DrawMain* pDraw = new DrawMain();

	pClient->Initialize( );

    //�ʐM���m��
    NetHandle = ConnectNetWork( pClient->getIP( ), 9850 ) ;
    // �m�������������ꍇ�̂ݒ��̏���������
    if( NetHandle != -1 ) { 
		while( true ) {
			pDraw->update( NetHandle );
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				break;
			}
		}
    }
    // �ڑ���f��
    CloseNetWork( NetHandle ) ;

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}