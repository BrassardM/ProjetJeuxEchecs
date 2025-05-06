#include "Fou.h"

/**
* Module pour le fou. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/


gameObjects::Fou::Fou(bool isBlack):Piece(std::vector<std::pair<int, int>>{
	{1, 1},
	{1,-1},
	{-1,1},
	{-1,-1}
}
, true, isBlack, (QString)"F")
{
}