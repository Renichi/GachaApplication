#include "server.h"


server::server() {
	clientStatusA = "OFFLINE";
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
		// �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
		NetHandle = GetNewAcceptNetWork();
		if (NetHandle != -1) {
			_NetHandleA = GetNewAcceptNetWork();
			clientStatusA = "ONLINE";
		}
		DrawString(0, 0, buf, GetColor(255, 255, 255));
		DrawString(0, 30,(  "CLIENT_A:" + clientStatusA ).c_str( ), GetColor(255, 255, 255));

		ClearDrawScreen();
	}
	// �ڑ��̎�t���I������
	StopListenNetWork();
	// �ڑ����Ă����}�V���̂h�o�A�h���X�𓾂�
	GetNetWorkIP(NetHandle, &Ip);
}

int server::getNetHandle() {
	int _NetHandleA;
}