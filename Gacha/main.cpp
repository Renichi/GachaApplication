#include "DxLib.h"
#include "client.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
             LPSTR lpCmdLine, int nCmdShow )
{
    char StrBuf[ 256 ] ;    // �f�[�^�o�b�t�@
    int NetHandle ;        // �l�b�g���[�N�n���h��
    int DataLength ;        // ��M�f�[�^�ʕۑ��p�ϐ�

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
        // �f�[�^���M
        NetWorkSend( NetHandle , "�q���������`�I�H" , 17 ) ;

        // �f�[�^������̂�҂�
        while( !ProcessMessage() )
        {
            // �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
            DataLength = GetNetWorkDataLength( NetHandle ) ;

            // �擾���ĂȂ���M�f�[�^�ʂ��O����Ȃ��ꍇ�̓��[�v�𔲂���
            if( DataLength != 0 ) break ;
        }

        // �f�[�^��M
        NetWorkRecv( NetHandle , StrBuf , DataLength ) ;    // �f�[�^���o�b�t�@�Ɏ擾

        // ��M�����f�[�^��`��
        DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // �L�[���͑҂�
        WaitKey() ;

        // �ڑ���f��
        CloseNetWork( NetHandle ) ;
    }

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}