#include "client.h"


client::client() {
}


client::~client() {
}

//����������
void client::Initialize( ) {
	//�ϐ��̏�����
	 unsigned Cr = GetColor( 255 , 255 , 255 );
	 char ip[ 30 ] = { 0 };
     char InputChar;
	 int count = 0;

	 //IP�A�h���X�̓���
	 while( !ProcessMessage() && ( CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) ) {
		DrawString( 250 , 240 - 32 , "�T�[�o��IP�A�h���X����͂��Ă�������" , Cr );
		// �������̓o�b�t�@���當�����擾����
         InputChar = GetInputChar( TRUE ) ;
        // ����R�[�h�ȊO�̕������͂��������ꍇ�̂ݕ\���������s��
        if( InputChar != 0 && InputChar >= CTRL_CODE_CMP ) {
            // ��ʂ̏���
            ClearDrawScreen() ;
            // �����̕ۑ�
            ip[ count ] = InputChar ;
			count++;
            // �`��
            DrawString( 312 , 232 , ip , GetColor( 255 , 255 , 255 )  ) ;
		}
	 }
	 //���̓f�[�^��_Ip�ɓK�p
	 std::string str;
	 int vaPlus[ 4 ];
	 int vaCount = 0;

	 for ( int i = 0; i < 20; i++ ) {
		 if ( ip[ i ] == '.' || ip[ i ] == '\0' ) {
			vaPlus[ vaCount ] = std::stoi(str);
			vaCount++;
			str.begin( );
			str.erase( );
			if ( vaCount == 4 ) {
				break;
			}
			continue;
		 }
		str.append( 1, ip[ i ] );
	 }

	 _Ip.d1 = ( unsigned char )vaPlus[ 0 ];
	 _Ip.d2 = ( unsigned char )vaPlus[ 1 ];
	 _Ip.d3 = ( unsigned char )vaPlus[ 2 ];
	 _Ip.d4 = ( unsigned char )vaPlus[ 3 ];
}

IPDATA client::getIP( ) {
	return _Ip;
}
