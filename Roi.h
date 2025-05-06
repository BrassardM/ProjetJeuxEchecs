#pragma once
#include "Piece.h"
#include "TropDeRois.h"

/**
* Ent�te pour le module roi qui h�rite de Piece. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
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