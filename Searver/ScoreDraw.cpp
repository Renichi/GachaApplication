#include "ScoreDraw.h"


ScoreDraw::ScoreDraw() {
}


ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update( ) {

	ScorePack sp = _db->getScore( );

	int a, b, c, d;
	a = 10;
	b = 20;
	c = 30;
	d = 40;

	 DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "%d\n", sp.prizeA ) ;
	 DrawFormatString( 0, 30, GetColor( 255, 255, 255 ), "%d\n", sp.prizeB) ;
	 DrawFormatString( 0, 60, GetColor( 255, 255, 255 ), "%d\n", sp.prizeC ) ;
	 DrawFormatString( 0, 90, GetColor( 255, 255, 255 ), "%d\n", sp.secret ) ;
}


