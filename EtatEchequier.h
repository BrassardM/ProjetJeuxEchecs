#include "Piece.h"
#include <utility>
#include <set>
#pragma once

/**
* Ent�te pour le module de l'�tat de l'�ch�quier, qui donne un r�sum� de l'�tat d'un �ch�quier pour sauvegarder. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

namespace gameObjects {
	class EtatEchequier {
	public:
		EtatEchequier(std::set<std::tuple<int, int, QString>> pieces, bool isBlack, bool blackCanCastle, bool whiteCanCastle);
		bool operator==(const EtatEchequier& other);
	private:
		bool isBlack_;
		std::set<std::tuple<int, int, QString>> pieces_;
		bool blackCanCastle_;
		bool whiteCanCastle_;
	};
}