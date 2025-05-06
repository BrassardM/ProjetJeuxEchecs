#pragma once
#include "Piece.h"

/**
* Entête pour le module de tour, hérite de Piece. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace gameObjects {
	class Tour : public Piece {
	public:
		Tour(bool isBlack);
	private : 
	};
}