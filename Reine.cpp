#include "Reine.h"

/**
* Module pour la reine. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


gameObjects::Reine::Reine(bool isBlack) : Piece(std::vector<std::pair<int, int>>{
	{ 1, 1 },
	{ 1, 0 },
	{ 1,-1 },
	{ 0, 1 },
	{ 0,-1 },
	{ -1,1 },
	{ -1, 0 },
	{ -1,-1 }
}
, true, isBlack, (QString)"Q")
{
}
