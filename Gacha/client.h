#pragma once
#include "DxLib.h"
#include "definer.h"
#include <string>

class client {
public:
	client();
	~client();
	void Initialize( );
	void running( );
	void finitialize( );
	IPDATA getIP( );
private:
	char _StrBuf[ 256 ];  //�f�[�^�o�b�t�@
	IPDATA _Ip;           //�ڑ��pIP�A�h���X�f�[�^
	int _NetHandle;       //�l�b�g���[�N�n���h��
	int _DataLength;      //��M��0���ʕۑ��p�ϐ�
};

