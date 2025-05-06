#pragma once
#include "Piece.h"

/**
* Ent�te pour le module reine qui h�rite de Piece. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

namespace gameObjects {
	class Reine : public Piece {
	public:
		Reine(bool isBlack);
	};
}