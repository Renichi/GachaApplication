#include "DxLib.h"
#include "server.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nCmdShow )
{
    char StrBuf[ 256 ] ;        // �f�[�^�o�b�t�@
    int NetHandle , LostHandle ;    // �l�b�g���[�N�n���h��
    int DataLength ;            // ��M�f�[�^�ʕۑ��p�ϐ�
    IPDATA Ip ;            // �ڑ���h�o�A�h���X�f�[�^
	int ipNum = 0;
	char buf[ 256 ];

	server* ps = new server();

	ChangeWindowMode( true );

    if( DxLib_Init() == -1 )    // �c�w���C�u��������������
    {
        return -1;    // �G���[���N�����璼���ɏI��
    }

	ps->initialize();

    while ( !ProcessMessage() && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {
        // �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
		NetHandle = ps->getNetHandle();
        if ( NetHandle != -1 ) {
			break;
		}
    }

    // �ڑ�����Ă����玟�ɐi��
    if( NetHandle != -1 ) {
   
        // �f�[�^�������ė���܂ő҂�
        while( !ProcessMessage() )
        {
            // �擾���Ă��Ȃ���M�f�[�^�ʂ��O�ȊO�̂Ƃ��̓��[�v���甲����
            if( GetNetWorkDataLength( NetHandle ) != 0 ) {
				break;
			}
        }

        // �f�[�^��M
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // �f�[�^�̗ʂ��擾
        NetWorkRecv( NetHandle , StrBuf , DataLength );    // �f�[�^���o�b�t�@�Ɏ擾

        // ��M�����f�[�^��`��
        DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // ��M�����̃f�[�^�𑗐M
        NetWorkSend( NetHandle , "�q���������`�I�I" , 17 ) ;

        // ���肪�ʐM��ؒf����܂ő҂�
        while( !ProcessMessage() )
        {
            // �V���ɐؒf���ꂽ�l�b�g���[�N�n���h���𓾂�
            LostHandle = GetLostNetWork() ;

            // �ؒf���ꂽ�ڑ������܂ŒʐM���Ă����肾�����ꍇ���[�v�𔲂���
            if( LostHandle == NetHandle ) break ;
        }

        // �ؒf�m�F�\��
        DrawString( 0 , 16 , "�ؒf���܂���" , GetColor( 255 , 255 , 255 ) ) ;

        // �L�[���͑҂�
        WaitKey() ;
    }

    DxLib_End() ;    // �c�w���C�u�����g�p�̏I������

    return 0 ;    // �\�t�g�̏I��
}