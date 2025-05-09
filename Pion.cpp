#include "Pion.h"

gameObjects::Pion::Pion(bool isBlack): Piece(std::vector<std::pair<int, int>>{
	{ (1-(2 * (int)isBlack))*1,0 }, //regular (index 0)
	{ (1 - (2 * (int)isBlack)) * 1,1 }, // capture (index 1)
	{ (1 - (2 * (int)isBlack)) * 1,-1 }, // capture (index 2)
	{ (1 - (2 * (int)isBlack)) * 2, 0 } // initial (index 3)
}
, false, isBlack, (QString)"P")
{
}

void gameObjects::Pion::playerMove()
{
	if (Piece::getHasMoved() == false) {
		Piece::removePossMoves(3);
	}
	Piece::playerMove();
}