#include "Chevalier.h"

/**
* Module pour le chevalier. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


gameObjects::Chevalier::Chevalier(bool isBlack) : Piece(std::vector<std::pair<int, int>>{
	{2, 1},
	{2,-1},
	{1,2},
	{1,-2},
	{-1,2},
	{-1,-2},
	{-2,1},
	{-2,-1}
}
, false, isBlack, (QString)"C")
{
}