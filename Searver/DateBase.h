#pragma once
#include "definer.h"

class DateBase {
public:
	DateBase();
	~DateBase();
	ScorePack getScore( );
private:
	int _prizeA;
	int _prizeB;
	int _prizeC;
	int _secret;
};

