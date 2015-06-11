#include "server.h"


server::server() {
	clientStatusA = "OFFLINE";
	_dp = new DatePack;
}


server::~server() {
}

void server::initialize() {
	char buf[256];
	int NetHandle;
	IPDATA myIpAddress;
	IPDATA Ip;            // �ڑ���h�o�A�h���X�f�[�^

	// IP�A�h���X�̎擾
	GetMyIPAddress(&myIpAddress);
	sprintf_s(buf, "IP Address = %d.%d.%d.%d", myIpAddress.d1, myIpAddress.d2, myIpAddress.d3, myIpAddress.d4);
	// �ڑ����Ă���̂�҂�Ԃɂ���
	PreparationListenNetWork(9850);

	// �ڑ����Ă��邩�d�r�b�L�[���������܂Ń��[�v
	NetHandle = -1;

	while (!ProcessMessage() && CheckHitKey(KEY_INPUT_RETURN) == 0) {
		ClearDrawScreen();
		// �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
		NetHandle = GetNewAcceptNetWork();
		if (NetHandle != -1) {
			_NetHandleA = NetHandle;
			clientStatusA = "ONLINE";
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30,(  "CLIENT_A:" + clientStatusA ).c_str( ), GetColor(255, 255, 255));

		
	}
	
	// �ڑ��̎�t���I������
	StopListenNetWork();
	// �ڑ����Ă����}�V���̂h�o�A�h���X�𓾂�
	GetNetWorkIP(NetHandle, &Ip);
}

void server::running( ) {
	int NetHandle,LostHandle;
    int DataLength ;            // ��M�f�[�^�ʕۑ��p�ϐ�

	NetHandle = this->getNetHandle( ); 

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

		NetWorkRecv( NetHandle , _dp , DataLength );    // �f�[�^���o�b�t�@�Ɏ擾

		if ( _dp->command == 0 ) {
			_db->update( 1, 0, 0, 0 );
			NetWorkSend( NetHandle , "���������", 30 ) ;
		}

		_dp->command = 1;

        // ��M�����f�[�^��`��
        //DrawString( 0 , 0 , StrBuf , GetColor( 255 , 255 , 255 ) ) ;

        // ��M�����̃f�[�^�𑗐M
       //NetWorkSend( NetHandle , "�q���������`�I�I" , 17 ) ;

        // ���肪�ʐM��ؒf����܂ő҂�
        /*while( !ProcessMessage() )
        {
            // �V���ɐؒf���ꂽ�l�b�g���[�N�n���h���𓾂�
            LostHandle = GetLostNetWork() ;

            // �ؒf���ꂽ�ڑ������܂ŒʐM���Ă����肾�����ꍇ���[�v�𔲂���
            if( LostHandle == NetHandle ) break ;
        }

        // �ؒf�m�F�\��
        DrawString( 0 , 16 , "�ؒf���܂���" , GetColor( 255 , 255 , 255 ) ) ;
		*/

}

void server::readAdress( DateBase& adress) {
	_db = &adress;
}

int server::getNetHandle() {
	return _NetHandleA;
}