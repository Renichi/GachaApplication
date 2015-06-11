#include "ScoreDraw.h"


ScoreDraw::ScoreDraw() {
	_db = new DateBase( );
}


ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update( ) {

	ScorePack sp = _db->getScore( );

	 DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "%d\n", sp.ScoreA ) ;
	 DrawFormatString( 0, 30, GetColor( 255, 255, 255 ), "%d\n", sp.ScoreB) ;
	 DrawFormatString( 0, 60, GetColor( 255, 255, 255 ), "%d\n", sp.ScoreC ) ;
	 DrawFormatString( 0, 90, GetColor( 255, 255, 255 ), "%d\n", sp.ScoreD ) ;
}


