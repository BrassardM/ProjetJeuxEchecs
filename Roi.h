#pragma once
#include "Piece.h"
#include "TropDeRois.h"

/**
* Entête pour le module roi qui hérite de Piece. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


namespace gameObjects {
	class Roi : public Piece {
	public:
		Roi(bool isBlack, bool isTemp = false);
		virtual ~Roi();
		void playerMove() override;
	private:
		inline static int nRoisBlack = 0;
		inline static int nRoisWhite = 0;
		bool isTemp_ = false;
	};
}