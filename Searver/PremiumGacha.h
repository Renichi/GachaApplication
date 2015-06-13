#pragma once
#include "definer.h"
#include "DateBase.h"
#include <iostream>
#include <time.h> 

class PremiumGacha {
public:
	PremiumGacha();
	~PremiumGacha();
	int playGacha( DateBase* _db );
};

