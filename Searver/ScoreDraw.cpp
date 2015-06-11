#include "ScoreDraw.h"


ScoreDraw::ScoreDraw() {
}


ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update( ) {
	_sp = _db->getScore( );

	 DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreA ) ;
	 DrawFormatString( 0, 30, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreB) ;
	 DrawFormatString( 0, 60, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreC ) ;
	 DrawFormatString( 0, 90, GetColor( 255, 255, 255 ), "%d\n", _sp.ScoreD ) ;
}

void ScoreDraw::readAdress( DateBase& adress ) {
	_db = &adress;
}


