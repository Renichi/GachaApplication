#include "server.h"


server::server() {
	clientStatus[0] = "OFFLINE";
	clientStatus[1] = "OFFLINE";
	clientStatus[2] = "OFFLINE";
	clientStatus[3] = "OFFLINE";
	clientStatus[4] = "OFFLINE";
	clientStatus[5] = "OFFLINE";
	_dp = new DatePack;
	_sd = new ScoreDraw();
	_clientNum;
	_secretFlag = false;
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
			_NetHandle[ _clientNum ] = NetHandle;
			clientStatus[ _clientNum ] = "ONLINE";
			_clientNum++;
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30, ("CLIENT_A:" + clientStatus[ 0 ] ).c_str( ), GetColor(255, 255, 255));
		DrawString(0, 50, ("CLIENT_B:" + clientStatus[ 1 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 70, ("CLIENT_C:" + clientStatus[ 2 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 90, ("CLIENT_D:" + clientStatus[ 3 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 110, ("CLIENT_E:" + clientStatus[ 4 ]).c_str(), GetColor(255, 255, 255));
		DrawString(0, 130, ("CLIENT_F:" + clientStatus[ 5 ]).c_str(), GetColor(255, 255, 255));
	}
	// �ڑ��̎�t���I������
	StopListenNetWork();
	// �ڑ����Ă����}�V���̂h�o�A�h���X�𓾂�
	GetNetWorkIP(NetHandle, &Ip);
}

void server::running( ) {
	int NetHandle;
    int DataLength ;            // ��M�f�[�^�ʕۑ��p�ϐ�

	NetHandle = this->getNetHandle( ); 
	_sd->readAdress( *_db );

	 // �f�[�^�������ė���܂ő҂�
        while( !ProcessMessage() )
        {
			_sd->update();
			chageRate();
			if (!_secretFlag) {
				if (CheckHitKey(KEY_INPUT_S) == 1) {
					_db->addSecret();
				}
			}

            // �擾���Ă��Ȃ���M�f�[�^�ʂ��O�ȊO�̂Ƃ��̓��[�v���甲����
			for (int i = 0; i < 6; i++) {
				if (GetNetWorkDataLength(_NetHandle[ i ]) != 0) {
					NetHandle = _NetHandle[i];
					break;
				}
			}
			if (NetHandle != 0) {
				break;
			}
        }
        // �f�[�^��M
        DataLength = GetNetWorkDataLength( NetHandle ) ;    // �f�[�^�̗ʂ��擾
		NetWorkRecv( NetHandle , _dp , DataLength );    // �f�[�^���o�b�t�@�Ɏ擾
		if (_dp->command == 1) {
			_dp->prize = normalGacha();
			NetWorkSend(NetHandle, _dp, 30);
		} else if (_dp->command == 2) {
			_dp->prize = premiumGacha();
			NetWorkSend(NetHandle, _dp, 30);
		}
		_dp->command = 0;

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
	return _NetHandle[0];
}

int server::normalGacha() {
	//�i�i�̔{��
	int prize = 4;
	int rare_B_probability = _db->getRate().RateB;
	int rare_A_probability = _db->getRate().RateA;
	//�����_���̊m��
	int random_probability = 10000;
	int probability;
	while (true) {
		probability = GetRand(10000);
		if (probability <= rare_B_probability  && _db->getScore().ScoreB != 0) {
			prize = 1;
			_db->update(0, 1, 0, 0);
			break;
		} else {
			prize = 2;
			_db->update(1, 0, 0, 0);
			break;
		}
	}
	return prize;
}

int server::premiumGacha() {
	int prize;
	int rare_S_probability = _db->getRate( ).RateD;
	int rare_C_probability = _db->getRate().RateC;
	int rare_B_probability = _db->getRate().RateB;
	int rare_PA_probability = _db->getRate().RatePA;
	//�����_���̊m��
	int random_probability = 10000;
	int probability;
	probability = GetRand(10000);
	while (true) {
		if (probability <= rare_S_probability) {
			if (_db->getScore().ScoreD != 0 && _db->getScore().ScoreD != 0) {
				prize = 3;
				_db->update(0, 0, 0, 1);
				break;
			}
		} else if (probability <= (rare_S_probability + rare_C_probability) && _db->getScore().ScoreC != 0) {
			prize = 0;
			_db->update(1, 0, 0, 0);
			break;
		} else if (probability <= (rare_S_probability + rare_C_probability + rare_B_probability )  && _db->getScore().ScoreC != 0) {
			prize = 1;
			_db->update(0, 1, 0, 0);
			break;
		} else {
			prize = 2;
			_db->update(1, 0, 0, 0);
			break;
		}
	}
	return prize;

}

void server::chageRate() {
	if (CheckHitKey(KEY_INPUT_1) == 1) {
		_db->updateRate(1, 0, 0, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_2) == 1) {
		_db->updateRate(-1, 0, 0, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_3) == 1) {
		_db->updateRate(0, 1, 0, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_4) == 1) {
		_db->updateRate(0, -1, 0, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_5) == 1) {
		_db->updateRate(0, 0, 1, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_6) == 1) {
		_db->updateRate(0, 0, -1, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_7) == 1) {
		_db->updateRate(0, 0, 0, 1, 0);
	}
	if (CheckHitKey(KEY_INPUT_8) == 1) {
		_db->updateRate(0, 0, 0, -1, 0);
	}
	if (CheckHitKey(KEY_INPUT_9) == 1) {
		_db->updateRate(0, 0, 0, 0, 1);
	}
	if (CheckHitKey(KEY_INPUT_0) == 1) {
		_db->updateRate(0, 0, 0, 0, -1);
	}
}