#include "Roi.h"

using namespace gameObjects;
gameObjects::Roi::Roi(bool isBlack, bool isTemp) : Piece(std::vector<std::pair<int, int>>{
	{1, 1},
	{ 1,0 },
	{ 1,-1 },
	{ 0,1 },
	{ 0,-1 },
	{ -1,1 },
	{ -1,0 },
	{ -1,-1 }
}
, false, isBlack, (QString)"R"), isTemp_(isTemp)
{
	if (isTemp == true) {
		nRois;
	}
	else {
		nRois++;
		if (nRois > 2) {
			nRois--;
			throw errors::tooManyKings("Plus de 2 rois!");
		} //change error to affect GUI
	}
}
Roi::~Roi() {
	if (!isTemp_) {
		nRois = nRois - 1;
	}
}