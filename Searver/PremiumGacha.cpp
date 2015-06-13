#include "PremiumGacha.h"


PremiumGacha::PremiumGacha()
{
}


PremiumGacha::~PremiumGacha()
{
}

int PremiumGacha::playGacha( DateBase* _db ) {
	//景品の倍率
	int prize = 4;
	int rare_C_probability = _db->getRate().RateC;
	int rare_B_probability = _db->getRate().RateB;
	//ランダムの確立
	int random_probability = 10000;
	int probability;
	//乱数の初期化
	srand((unsigned int)time(NULL));
	while (true) {
		//乱数の生成
		probability = rand() % 10000 + 1;
		//ガチャの抽選
		//一等賞
		if (probability <= rare_C_probability) {
			prize = 2;
			_db->update(0, 0, 1, 0);
			break;
		}
		//二等賞
		else if (probability <= (rare_C_probability + rare_B_probability)) {
			prize = 1;
			_db->update(0, 1, 0, 0);
			break;
		}
		//三等賞
		else {
			prize = 0;
			_db->update(1, 0, 0, 0);
			break;
		}
	}
	return prize;
}
