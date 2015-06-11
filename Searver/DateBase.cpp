#include "DateBase.h"


DateBase::DateBase() {
	_prizeA = 50;
	_prizeB = 50;
	_prizeC = 50;
	_secret = 20;
}


DateBase::~DateBase() {
}

ScorePack DateBase::getScore( ) {
	ScorePack score = { _prizeA, _prizeB, _prizeC, _secret }; 
	return score;
}