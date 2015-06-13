#include "DateBase.h"


DateBase::DateBase() {
	_prizeA = 0;
	_prizeB = 0;
	_prizeC = 0;
	_secret = 0;
	_rateA = 6928;
	_rateB = 2389;
	_rateC = 558;
	_rateSecret = 0;
	_playCount = 0;
}


DateBase::~DateBase() {
}

void DateBase::update( int a, int b, int c, int d ) {
	_prizeA += a;
	_prizeB += b;
	_prizeC += c;
	_secret += d;
}
void DateBase::updateRate( int a, int b, int c, int d ) {
	_rateA += a;
	_rateB += b;
	_rateC += c;
	_rateSecret += d;
}

ScorePack DateBase::getScore( ) {
	ScorePack score = { _prizeA, _prizeB, _prizeC, _secret }; 
	return score;
}

RatePack DateBase::getRate() {
	RatePack rate = { _rateA, _rateB, _rateC, _rateSecret };
	return rate;
}

int DateBase::getPlayCount() {
	return _playCount;
}

void DateBase::addSecret() {
	_rateSecret = 100;
}

void DateBase::addPlayCount() {
	_playCount++;
}