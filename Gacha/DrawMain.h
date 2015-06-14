#pragma once
#include "Draw2D.h"
#include "definer.h"

class DrawMain {
public:
	DrawMain();
	~DrawMain();
	void update( int NetHandle );
	void select();
	void normal();
	void premium();
	void input();
private: 
	DatePack* _rb;
	bool _select;
	int _BackGround;
	int _BackGroundN;
	int _BackGroundP;
	int _kabe;
	int _kaidan[ 2 ];
	int _Elevator[ 2 ];
	int _normal;
	int _premium;
	int _chara[ 3 ];
	int _secene;
	int _scratchPlate;
	int _scratch[4];
	int _gin[ 2 ];
	int _drawWidth;
	int _pushCount;
	int _prize[4];
	int _drawHeight;
	int _addSpeed;
	int _charaSelect;
	int _prizeSelect;
	int _NetHandle;
	int _catin;
	int _catInPosition;
	int _god;
	int _godFlag;
};

