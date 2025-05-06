#include "Piece.h"
#include <utility>
#include <set>
#pragma once

/**
* Entête pour le module de l'état de l'échéquier, qui donne un résumé de l'état d'un échéquier pour sauvegarder. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
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