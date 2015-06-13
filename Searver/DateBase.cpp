#include "DateBase.h"


DateBase::DateBase() {
	_prizeA = 246;
	_prizeB = 24;
	_prizeC = 8;
	_secret = 0;
	_rateA = 6928;
	_ratePremiumA = 900;
	_rateB = 2389;
	_rateC = 558;
	_rateSecret = 125;
}


DateBase::~DateBase() {
}

void DateBase::update( int a, int b, int c, int d ) {
	_prizeA -= a;
	_prizeB -= b;
	_prizeC -= c;
	_secret -= d;
}
void DateBase::updateRate(int a, int b, int c, int d, int e) {
	_rateA += a;
	_ratePremiumA += e;
	_rateB += b;
	_rateC += c;
	_rateSecret += d;
}

ScorePack DateBase::getScore( ) {
	ScorePack score = { _prizeA, _prizeB, _prizeC, _secret }; 
	return score;
}

RatePack DateBase::getRate() {
	RatePack rate = { _rateA, _rateB, _rateC, _rateSecret, _ratePremiumA };
	return rate;
}

void DateBase::addSecret() {
	_secret = 1;
}