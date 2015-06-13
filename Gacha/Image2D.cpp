#include "Image2D.h"


Image2D::Image2D() {
	_BackGround[ 0 ] = LoadGraph("Select_Haikei.png");
	_BackGround[ 1 ] = LoadGraph("kaidan_odoriba .png");
	_BackGround[ 2 ] = LoadGraph("Elevator_naka_2.png");
	_selectPart[0] = LoadGraph("kabe.png");
	_selectPart[1] = LoadGraph("kaidan.png");
	_selectPart[2] = LoadGraph("Elevator.png");
	_selectPart[3] = LoadGraph("N_icon.png");
	_selectPart[4] = LoadGraph("P_icon.png");
	_chara[0] = LoadGraph("Jinbutu1.png");
	_chara[1] = LoadGraph("Jinbutu2.png");
	_chara[2] = LoadGraph("Jinbutu3.png");
	_scratchPlate = LoadGraph("N_Scratch.png");
	_scratch[0] = LoadGraph("1tou.png");
	_scratch[1] = LoadGraph("2tou.png");
	_scratch[2] = LoadGraph("3tou.png");
	_scratch[3] = LoadGraph("secret.png");
	_gin = LoadGraph("Gin.png");
	_prize[0] = LoadGraph("1tou_icon.png");
	_prize[1] = LoadGraph("2tou_icon.png");
	_prize[2] = LoadGraph("3tou_icon.png");
	_prize[3] = LoadGraph("secret_icon.png");
}


Image2D::~Image2D() {
}
