#include "Echequier.h"
#pragma once

/**
* Entête pour le module du RAII. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace gameObjects {
	class MouvementTemporaire {
	public:
		MouvementTemporaire(std::pair<int, int> originalPos, std::pair<int, int> stealpos, Echequier* input);
		~MouvementTemporaire();
	private :
		std::pair<int, int> originalPos_;
		std::pair<int, int> movePos_;
		gameObjects::Piece* stolen_;
		Echequier* board_;
	};
}