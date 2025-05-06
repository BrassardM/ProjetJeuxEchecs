#include "Piece.h"
#pragma once

/**
* Entête pour le module du fou, hérite de Piece. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace gameObjects {
	class Fou : public Piece {
	public:
		Fou(bool isBlack);
	};
}