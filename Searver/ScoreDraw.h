#pragma once
#include "Dxlib.h"
#include "DateBase.h"
#include "definer.h"


class ScoreDraw {
public:
	ScoreDraw();
	~ScoreDraw();
	void update ( );
	void loadScore( );
private:
	DateBase* _db;
	ScorePack _sp;
};

