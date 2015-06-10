#include "DxLib.h"
#include "client.h"
#include "DrawMain.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
   
    int NetHandle ;        // �l�b�g���[�N�n���h��

	ChangeWindowMode(true);
	SetGraphMode(2160, 1440, 32);
	

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
         return -1;    // �G���[���N�����璼���ɏI��
    }

	client* pClient = new client( );
	DrawMain* pDraw = new DrawMain();

	/*pClient->Initialize( );

    // �ʐM���m��
    NetHandle = ConnectNetWork( pClient->getIP( ), 9850 ) ;*/

	NetHandle = 0;
    // �m�������������ꍇ�̂ݒ��̏���������
    if( NetHandle != -1 )
    { 
		while( true ) {
			ClearDrawScreen();
			pDraw->update();
			//pClient->running( );
			if (CheckHitKey(CheckHitKey(KEY_INPUT_RETURN) == 0)) {
				break;
			}
		}
    }

    // �ڑ���f��
    CloseNetWork( NetHandle ) ;

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}