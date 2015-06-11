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
	void readAdress( DateBase& adress );
private:
	ScorePack _sp;
	DateBase* _db;
};

