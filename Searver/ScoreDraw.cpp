#include "ScoreDraw.h"


ScoreDraw::ScoreDraw() {
}


ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update( ) {
	_sp = _db->getScore( );
	_rp = _db->getRate();

	ClearDrawScreen();
	DrawString(0, 0, "3tou:", GetColor(255, 255, 255));
	DrawFormatString( 0, 20, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreA );
	DrawString(0, 50, "2tou:", GetColor(255, 255, 255));
	DrawFormatString( 0, 70, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreB);
	DrawString(0, 100, "1tou:", GetColor(255, 255, 255));
	DrawFormatString( 0, 120, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreC );
	DrawString(0, 150, "secret:", GetColor(255, 255, 255));
	DrawFormatString( 0, 170, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreD );

	DrawString(500, 0, "Rate_3tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 20, GetColor(255, 255, 255), "%d\n", _rp.RateA );
	DrawString(500, 50, "Rate_2tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 70, GetColor(255, 255, 255), "%d\n", _rp.RateB);
	DrawString(500, 100, "Rate_1tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 120, GetColor(255, 255, 255), "%d\n", _rp.RateC);
	DrawString(500, 150, "Rate_secret:", GetColor(255, 255, 255));
	DrawFormatString(500, 170, GetColor(255, 255, 255), "%d\n", _rp.RateD);
	DrawString(500, 200, "Rate_Pre,iumA:", GetColor(255, 255, 255));
	DrawFormatString(500, 230, GetColor(255, 255, 255), "%d\n", _rp.RatePA);

	ScreenFlip();
}

void ScoreDraw::readAdress( DateBase& adress ) {
	_db = &adress;
}


