#include "Echequier.h"
#pragma once

/**
* Ent�te pour le module du RAII. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
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