#include "DrawMain.h"


DrawMain::DrawMain() {
	_select = true;
	_rb = new DatePack;
	_secene = 0;
	_drawWidth = 0;
	_drawHeight = 0;
	_pushCount = 0;
	_addSpeed = 0;
	_charaSelect = GetRand( 2 );
	_prizeSelect = 0;
	_god = 0;
	_godFlag = 0;

	_BackGround = LoadGraph("Select_Haikei.png");
	_BackGroundN = LoadGraph("kaidan_odoriba .png");
	_BackGroundP = LoadGraph("Elevator_naka_2.png");
	_kabe = LoadGraph("kabe.png");
	_kaidan[ 0 ] = LoadGraph("kaidan.png");
	_kaidan[ 1 ] = LoadGraph("Kaidan1.png");
	_Elevator[ 0 ] = LoadGraph("Elevator.png");
	_Elevator[1] = LoadGraph("godfes_elevator.png");
	_normal = LoadGraph("N_icon.png");
	_premium = LoadGraph("P_icon.png");
	_chara[ 0 ] = LoadGraph("Jinbutu1.png");
	_chara[ 1 ] = LoadGraph("Jinbutu2.png");
	_chara[ 2 ] = LoadGraph("Jinbutu3.png");
	_scratchPlate = LoadGraph("N_Scratch.png");
	_scratch[0] = LoadGraph("1tou.png");
	_scratch[1] = LoadGraph("2tou.png");
	_scratch[2] = LoadGraph("3tou.png");
	_scratch[3] = LoadGraph("secret.png");
	_gin[ 0 ] = LoadGraph("Gin.png");
	_gin[1] = LoadGraph("godfes_gin.png");
	_prize[0] = LoadGraph("1tou_icon.png");
	_prize[1] = LoadGraph("2tou_icon.png");
	_prize[2] = LoadGraph("3tou_icon.png");
	_prize[3] = LoadGraph("secret_icon.png");
	_catin = LoadGraph("catin.jpg");
	_catInPosition = -1280;
}

DrawMain::~DrawMain() {
}

void DrawMain::update( int NetHandle ) {
	//画面の初期化
	ClearDrawScreen();

	_NetHandle = NetHandle;

	//描画seceneの選択
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

	// 裏画面の内容を表画面に反映させる
	ScreenFlip();
	// ２０分の１秒待つ
	WaitTimer(50);
}

void DrawMain::select() {
	int DataLength;        // 受信データ量保存用変数

	if (_catInPosition >= 600) {
		_god = 1;
	}
	DrawExtendGraph(0, 0, 1280, 1024, _BackGround, TRUE);
	DrawExtendGraph(275, 200, 825, 980, _kaidan[ _god ], TRUE);
	DrawExtendGraph(0, 0, 375, 1024, _kabe, TRUE);
	DrawExtendGraph(879, 180, 1255, 978, _Elevator[ _god ], TRUE);
	DrawExtendGraph(100, 100, 350, 300, _normal, TRUE);
	DrawExtendGraph(950, 0, 1200, 200, _premium, TRUE);
	DrawExtendGraph(0 + _catInPosition, 0, 1280 + _catInPosition, 1024, _catin, TRUE);
	if (_godFlag == 1) {
		_catInPosition += 32;
	}
	if (_catInPosition >= 00) {
		_god = 1;
	}
	if (_select) {
		DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
	} else {
		DrawExtendGraph(600, 300, 1000, 1024, _chara[ _charaSelect ], TRUE);
	}
	//入力待ち
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
			DatePack dp;
			dp.command = 1;
			NetWorkSend( _NetHandle, (void*)&dp, 30);
		}
		else {
			_secene = 2;
			DatePack dp;
			dp.command = 2;
			NetWorkSend(_NetHandle, (void*)&dp, 30);
		}
	}
	// 取得していない受信データ量を得る
	DataLength = GetNetWorkDataLength(_NetHandle);

	// 取得してない受信データ量が０じゃない場合はループを抜ける
	if (DataLength != 0) {
		// データ受信
		NetWorkRecv(_NetHandle, _rb, DataLength);    // データをバッファに取得
		_prizeSelect = _rb->prize;
		_godFlag = _rb->fes;
	}
}

void DrawMain::normal() {
	DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
	DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
	DrawGraph(350, 130, _scratchPlate, TRUE);
	DrawGraph(350, 130, _scratch[ _prizeSelect ], TRUE);
	DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);

	//入力待ち
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			_pushCount++;
			for (int i = 0; i < 190; i++) {
				ClearDrawScreen();
				_drawWidth++;
				DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
				DrawGraph(350, 130, _scratchPlate, TRUE);
				DrawGraph(350, 130, _scratch[_prizeSelect], TRUE);
				DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);
				WaitTimer(5);
			}
		}
		if (_pushCount == 3) {
			for (int i = 0; i < 31; i++) {
				ClearDrawScreen();
				_drawWidth++;
				_addSpeed += _drawHeight;
				DrawExtendGraph(0, 0, 1280, 1024, _BackGroundN, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
				DrawGraph(350, 130, _scratchPlate, TRUE);
				DrawGraph(350, 130, _scratch[ _prizeSelect ], TRUE);
				DrawRectGraph(360 + _drawWidth, 130, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);
				DrawGraph(250, -100 + _addSpeed, _prize[ _prizeSelect ], TRUE);
				_drawHeight++;
				WaitTimer(20);
			}
			_pushCount = 0;
			WaitKey();
			WaitTimer(1000);
			_secene = 0;
		}
	}
	
}

void DrawMain::premium() {
	DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
	DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
	DrawGraph(390, 220, _scratch[ _prizeSelect ], TRUE);
	DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);

	//入力待ち
	while (CheckHitKeyAll() == 0) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			_pushCount++;
			for (int i = 0; i < 190; i++) {
				ClearDrawScreen();
				_drawWidth++;
				DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
				DrawGraph(390, 220, _scratch[ _prizeSelect ], TRUE);
				DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);
				WaitTimer(10);
			}
		}
		if (_pushCount == 3) {
			for (int i = 0; i < 31; i++) {
				ClearDrawScreen();
				_drawWidth++;
				_addSpeed += _drawHeight;
				DrawExtendGraph(-780, -80, 2000, 1544, _BackGroundP, TRUE);
				DrawExtendGraph(0, 300, 400, 1024, _chara[ _charaSelect ], TRUE);
				DrawGraph(390, 220, _scratch[ _prizeSelect ], TRUE);
				DrawRectGraph(400 + _drawWidth, 220, _drawWidth, 0, 600, 360, _gin[ _god ], TRUE, FALSE);
				DrawGraph(250, -100 + _addSpeed, _prize[ _prizeSelect ], TRUE);
				_drawHeight++;
				WaitTimer(20);
			}
			_pushCount = 0;
			WaitKey();
			_secene = 0;
		}
	}
}