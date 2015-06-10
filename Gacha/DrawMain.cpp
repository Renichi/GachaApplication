#include "DrawMain.h"


DrawMain::DrawMain() {
	_pd2 = new Draw2D();
	_select = true;
	_secene = 0;

	_BackGround = LoadGraph("Select_Haikei.png");
	_kabe = LoadGraph("kabe.png");
	_kaidan = LoadGraph("kaidan.png");
	_Elevator = LoadGraph("Elevator.png");
	_normal = LoadGraph("N_icon.png");
	_premium = LoadGraph("P_icon.png");
	_chara = LoadGraph("Jinbutu2.png");
}


DrawMain::~DrawMain() {
}

void DrawMain::update() {
	switch (_secene) {
	case 0:
		this->select();
	case 1:
		this->normal();
		break;
	case 2:
		this->premium();
	}
	
}

void DrawMain::select() {
	//描画します(『DrawGraph』を使用)
	// 読みこんだグラフィックを拡大描画
	DrawExtendGraph(0, 0, 2160, 1440, _BackGround, TRUE);
	DrawExtendGraph(610, 280, 1390, 1440, _kaidan, TRUE);
	DrawExtendGraph(0, 0, 644, 1440, _kabe, TRUE);
	DrawExtendGraph(1490, 250, 2115, 1440, _Elevator, TRUE);
	DrawExtendGraph(400, 100, 600, 300, _normal, TRUE);
	DrawExtendGraph(1690, 50, 1890, 250, _premium, TRUE);
	if (_select) {
		DrawExtendGraph(100, 300, 800, 1440, _chara, TRUE);
	} else {
		DrawExtendGraph(850, 300, 1550, 1440, _chara, TRUE);
	}

	//入力待ち
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			_select = true;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			_select = false;
		}
		else if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			if (_select) {
				_secene = 1;
			}
			else {
				_secene = 2;
			}
		}
		if (ProcessMessage() == -1) {
			break;
		}
	}
	
}

void DrawMain::normal() {

}

void DrawMain::premium() {

}