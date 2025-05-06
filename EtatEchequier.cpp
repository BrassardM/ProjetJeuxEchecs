#include "EtatEchequier.h"

/**
* Module pour l'�tat d'un �ch�quier. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/


gameObjects::EtatEchequier::EtatEchequier(std::set<std::tuple<int, int, QString>> pieces, bool isBlack, bool blackCanCastle, bool whiteCanCastle) : pieces_(pieces), isBlack_(isBlack), blackCanCastle_(blackCanCastle), whiteCanCastle_(whiteCanCastle)
{
}

bool gameObjects::EtatEchequier::operator==(const EtatEchequier& other)
{
    return ((pieces_ == other.pieces_) && (isBlack_ == other.isBlack_) && (blackCanCastle_ == other.blackCanCastle_) && (whiteCanCastle_ == other.whiteCanCastle_));
}