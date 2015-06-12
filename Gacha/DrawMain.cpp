#include "DrawMain.h"


DrawMain::DrawMain() {
	_select = true;
	_secene = 0;
	_drawWidth = 0;
	_drawHeight = 0;
	_pushCount = 0;
	_addSpeed = 0;

	_BackGround = LoadGraph("Select_Haikei.png");
	_BackGroundN = LoadGraph("kaidan_odoriba .png");
	_BackGroundP = LoadGraph("Elevator_naka_2.png");
	_kabe = LoadGraph("kabe.png");
	_kaidan = LoadGraph("kaidan.png");
	_Elevator = LoadGraph("Elevator.png");
	_normal = LoadGraph("N_icon.png");
	_premium = LoadGraph("P_icon.png");
	_chara = LoadGraph("Jinbutu2.png");
	_scratchPlate = LoadGraph("N_Scratch.png");
	_scratchN = LoadGraph("1tou.png");
	_gin = LoadGraph("Gin.png");
	_prize = LoadGraph("1tou_icon.png");
}

DrawMain::~DrawMain() {
}

void DrawMain::update() {
	//âÊñ ÇÃèâä˙âª
	ClearDrawScreen();

	//ï`âÊseceneÇÃëIë
	switch (_secene) {
	case 0:
		select();
		break;
	case 1:
		normal();
		break;
	case 2:
		premium();
		break;
	}

	// ó†âÊñ ÇÃì‡óeÇï\âÊñ Ç…îΩâfÇ≥ÇπÇÈ
	ScreenFlip();

	// ÇQÇOï™ÇÃÇPïbë“Ç¬
	WaitTimer(50);
}

void DrawMain::select() {
	DrawExtendGraph(0, 0, 1280, 1024, _BackGround, TRUE);
	DrawExtendGraph(375, 200, 825, 1024, _kaidan, TRUE);
	DrawExtendGraph(0, 0, 375, 1024, _kabe, TRUE);
	DrawExtendGraph(885, 180, 1255, 1024, _Elevator, TRUE);
	DrawExtendGraph(200, 100, 350, 300, _normal, TRUE);
	DrawExtendGraph(1000, 0, 1150, 200, _premium, TRUE);
	if (_select) {
		DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
	} else {
		DrawExtendGraph(600, 300, 1000, 1024, _chara, TRUE);
	}
	//ì¸óÕë“Çø
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			_select = true;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			_select = false;
		}
		else if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			_drawWidth = 0;
			_drawHeight = 0;
			_addSpeed = 0;
			if (_select) {
				_secene = 1;
			}
			else {
				_secene = 2;
			}
		}
	}
}

void DrawMain::normal() {
	DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
	DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
	DrawGraph(350, 130, _scratchPlate, TRUE);
	DrawGraph(350, 130, _scratchN, TRUE);
	DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);

	//ì¸óÕë“Çø
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			_pushCount++;
			for (int i = 0; i < 190; i++) {
				ClearDrawScreen();
				_drawWidth++;
				DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
				DrawGraph(350, 130, _scratchPlate, TRUE);
				DrawGraph(350, 130, _scratchN, TRUE);
				DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);
				WaitTimer(10);
			}
		}
		if (_pushCount == 3) {
			for (int i = 0; i < 31; i++) {
				ClearDrawScreen();
				_drawWidth++;
				_addSpeed += _drawHeight;
				DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
				DrawGraph(350, 130, _scratchPlate, TRUE);
				DrawGraph(350, 130, _scratchN, TRUE);
				DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);
				DrawGraph(250, -100 + _addSpeed, _prize, TRUE);
				_drawHeight++;
				WaitTimer(20);
			}
			_pushCount = 0;
			WaitKey();
			_secene = 0;
		}
	}
	
}

void DrawMain::premium() {
	DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
	DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
	DrawGraph(390, 220, _scratchN, TRUE);
	DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);

	//ì¸óÕë“Çø
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			_pushCount++;
			for (int i = 0; i < 190; i++) {
				ClearDrawScreen();
				_drawWidth++;
				DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
				DrawGraph(390, 220, _scratchN, TRUE);
				DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);
				WaitTimer(10);
			}
		}
		if (_pushCount == 3) {
			for (int i = 0; i < 31; i++) {
				ClearDrawScreen();
				_drawWidth++;
				_addSpeed += _drawHeight;
				DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara, TRUE);
				DrawGraph(390, 220, _scratchN, TRUE);
				DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin, TRUE, FALSE);
				DrawGraph(250, -100 + _addSpeed, _prize, TRUE);
				_drawHeight++;
				WaitTimer(20);
			}
			_pushCount = 0;
			WaitKey();
			_secene = 0;
		}
	}
}