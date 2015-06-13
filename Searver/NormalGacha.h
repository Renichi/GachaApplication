#pragma once
#include "definer.h"
#include "DateBase.h"
#include <iostream>
#include <time.h>

class NormalGacha {
public:
	NormalGacha();
	~NormalGacha();
	int playGacha( DateBase* _db );
};

