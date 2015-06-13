#include "ScoreDraw.h"


ScoreDraw::ScoreDraw() {
}


ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update( ) {
	_sp = _db->getScore( );
	_rp = _db->getRate();

	DrawString(0, 0, "–{“ú‚ÌƒKƒ`ƒƒ‚Ì‰ñ”:", GetColor(255, 255, 255));
	DrawFormatString( 170, 0, GetColor(255, 255, 255), "%d\n", _db->getPlayCount( ) );
	DrawString(0, 40, "3tou:", GetColor(255, 255, 255));
	DrawFormatString( 70, 40, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreA );
	DrawString(0, 60, "2tou:", GetColor(255, 255, 255));
	DrawFormatString( 70, 60, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreB);
	DrawString(0, 80, "1tou:", GetColor(255, 255, 255));
	DrawFormatString( 70, 80, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreC );
	DrawString(0, 100, "secret:", GetColor(255, 255, 255));
	DrawFormatString( 70, 100, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreD );

	DrawString(500, 0, "Rate_3tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 20, GetColor(255, 255, 255), "%d\n", _rp.RateA );
	DrawString(500, 50, "Rate_2tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 70, GetColor(255, 255, 255), "%d\n", _rp.RateB);
	DrawString(500, 100, "Rate_1tou:", GetColor(255, 255, 255));
	DrawFormatString(500, 120, GetColor(255, 255, 255), "%d\n", _rp.RateC);
	DrawString(500, 150, "Rate_secret:", GetColor(255, 255, 255));
	DrawFormatString(500, 170, GetColor(255, 255, 255), "%d\n", _rp.RateD);
}

void ScoreDraw::readAdress( DateBase& adress ) {
	_db = &adress;
}


