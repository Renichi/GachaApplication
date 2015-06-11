#include "DateBase.h"


DateBase::DateBase() {
	_prizeA = 50;
	_prizeB = 50;
	_prizeC = 50;
	_secret = 20;
}


DateBase::~DateBase() {
}

void DateBase::update( int a, int b, int c, int d ) {
	_prizeA += a;
	_prizeB += b;
	_prizeC += c;
	_secret += d;
}

ScorePack DateBase::getScore( ) {
	
	ScorePack score = { _prizeA, _prizeB, _prizeC, _secret }; 
	return score;
}