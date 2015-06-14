#include "NormalGacha.h"

NormalGacha::NormalGacha() {
}

NormalGacha::~NormalGacha() {
}

int NormalGacha::playGacha( DateBase* _db ) {
	//�i�i�̔{��
	int prize = 4;
	int rare_S_probability = _db->getRate().RateD;
	int rare_B_probability = _db->getRate().RateB;
	//�����_���̊m��
	int random_probability = 10000;
	int probability;
	while (true) {
		//�����̐���
		probability = GetRand(10000);
		//�K�`���̒��I
		//secret
		if ( probability <= rare_S_probability ) {
			prize = 3;
			_db->update(0, 0, 0, 1);
			break;
		}
		//�񓙏�
		else if ( rare_S_probability + rare_B_probability ) {
			prize = 1;
			_db->update(0, 1, 0, 0);
			break;
		} 
		//�O����
		else {
			prize = 2;
			_db->update(1, 0, 0, 0);
			break;
		}
	}
	return prize;
}
