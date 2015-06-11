#pragma once
#include "definer.h"

class DateBase {
public:
	DateBase( );
	virtual ~DateBase();
	void update( int a, int b, int c, int d );
	ScorePack getScore( );
private:
	int _prizeA;
	int _prizeB;
	int _prizeC;
	int _secret;

};

