#pragma once
#include "definer.h"
#include "DateBase.h"
#include "DxLib.h"

class PremiumGacha {
public:
	PremiumGacha();
	~PremiumGacha();
	int playGacha( DateBase* _db );
};

