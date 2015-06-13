#pragma once
#include "DxLib.h"

class Image2D {
public:
	Image2D();
	~Image2D();
private:
	int _BackGround[ 3 ];
	int _selectPart[5];
	int _chara[3];
	int _scratchPlate;
	int _scratch[4];
	int _gin;
	int _prize[4];
};

