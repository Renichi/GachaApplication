#include "NormalGacha.h"

NormalGacha::NormalGacha() {
}

NormalGacha::~NormalGacha() {
}

int NormalGacha::playGacha( DateBase* _db ) {
	//景品の倍率
	int prize = 4;
	int rare_S_probability = _db->getRate().RateD;
	int rare_B_probability = _db->getRate().RateB;
	//ランダムの確立
	int random_probability = 10000;
	int probability;
	while (true) {
		//乱数の生成
		probability = GetRand(10000);
		//ガチャの抽選
		//secret
		if ( probability <= rare_S_probability ) {
			prize = 3;
			_db->update(0, 0, 0, 1);
			break;
		}
		//二等賞
		else if (probability <= (rare_S_probability + rare_B_probability)) {
			prize = 1;
			_db->update(0, 1, 0, 0);
			break;
		} 
		//三等賞
		else {
			prize = 2;
			_db->update(1, 0, 0, 0);
			break;
		}
	}
	return prize;
}
