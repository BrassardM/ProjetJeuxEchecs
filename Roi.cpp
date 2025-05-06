#include "Roi.h"

/**
* Module pour le roi. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


using namespace gameObjects;
gameObjects::Roi::Roi(bool isBlack, bool isTemp) : Piece(std::vector<std::pair<int, int>>{
	{1, 1},
	{ 1,0 },
	{ 1,-1 },
	{ 0,1 },
	{ 0,-1 },
	{ -1,1 },
	{ -1,0 },
	{ -1,-1 },
	{ 0,2 }, //castling (index 8)
	{ 0,-2 } //castling (index 9)
}
, false, isBlack, (QString)"R"), isTemp_(isTemp)
{
	if (isBlack) {
		nRoisBlack++;
		if (nRoisBlack > 1) {
			nRoisBlack--;
			throw errors::TropDeRois("Plus de 1 roi noir!");
		} 
	}
	else {
		nRoisWhite++;
		if (nRoisWhite > 1) {
			nRoisWhite--;
			throw errors::TropDeRois("Plus de 1 roi blanc!");
		}
	}
}
Roi::~Roi() {
	if (!isTemp_) {
		if (isBlack()) {
			nRoisBlack--;
		}
		else {
			nRoisWhite--;
		}
	}
}

void gameObjects::Roi::playerMove()
{
	if (Piece::getHasMoved() == false) {
		Piece::removePossMoves(9);
		Piece::removePossMoves(8);
	}
	Piece::playerMove();
}
