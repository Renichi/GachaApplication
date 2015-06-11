#include "DxLib.h"
#include "client.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
   
    int NetHandle ;        // �l�b�g���[�N�n���h��
   

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
         return -1;    // �G���[���N�����璼���ɏI��
    }

	client* pClient = new client( );
	pClient->Initialize( );

    // �ʐM���m��
    NetHandle = ConnectNetWork( pClient->getIP( ), 9850 ) ;

    // �m�������������ꍇ�̂ݒ��̏���������
    if( NetHandle != -1 )
    { 
		while( true ) {
			pClient->running( );
		}
    }

    // �ڑ���f��
    CloseNetWork( NetHandle ) ;

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}