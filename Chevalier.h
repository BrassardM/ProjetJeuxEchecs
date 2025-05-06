#include "Piece.h"
#pragma once

/**
* Entête pour le module de chevalier qui hérite de l'objet Piece. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace gameObjects {
	class Chevalier : public Piece {
	public:
		Chevalier(bool isBlack);
	};
}