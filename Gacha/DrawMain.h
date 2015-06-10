#pragma once
#include "Draw2D.h"

class DrawMain {
public:
	DrawMain();
	~DrawMain();
	void update();
	void select();
	void normal();
	void premium();
	void input();
private: 
	Draw2D* _pd2;
	bool _select;
	int _BackGround;
	int _kabe;
	int _kaidan;
	int _Elevator;
	int _normal;
	int _premium;
	int _chara;
	int _secene;
};

