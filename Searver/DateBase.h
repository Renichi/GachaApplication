#pragma once
#include "definer.h"

class DateBase {
public:
	DateBase( );
	virtual ~DateBase( );
	void update( int a, int b, int c, int d );
	void updateRate( int a, int b, int c, int d );
	ScorePack getScore( );
	RatePack getRate();
	int getPlayCount( );
	void addSecret( );
	void addPlayCount();
private:
	int _prizeA;
	int _prizeB;
	int _prizeC;
	int _secret;
	int _rateA;
	int _rateB;
	int _rateC;
	int _rateSecret;
	int _playCount;
};

