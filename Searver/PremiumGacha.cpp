#include "PremiumGacha.h"


PremiumGacha::PremiumGacha()
{
}


PremiumGacha::~PremiumGacha()
{
}

int PremiumGacha::playGacha( DateBase* _db ) {
	//�i�i�̔{��
	int prize = 4;
	int rare_C_probability = _db->getRate().RateC;
	int rare_B_probability = _db->getRate().RateB;
	//�����_���̊m��
	int random_probability = 10000;
	int probability;
	//�����̏�����
	while (true) {
		//�����̐���
		probability = GetRand(10000);
		//�K�`���̒��I
		//�ꓙ��
		if (probability <= rare_C_probability) {
			prize = 0;
			_db->update(0, 0, 1, 0);
			break;
		}
		//�񓙏�
		else if (probability <= (rare_C_probability + rare_B_probability)) {
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
