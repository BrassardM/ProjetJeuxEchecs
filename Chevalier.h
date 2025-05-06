#include "Piece.h"
#pragma once

/**
* Ent�te pour le module de chevalier qui h�rite de l'objet Piece. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

namespace gameObjects {
	class Chevalier : public Piece {
	public:
		Chevalier(bool isBlack);
	};
}