#include "MouvementTemporaire.h"

/**
* Module pour le RAII. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


using namespace gameObjects;

MouvementTemporaire::MouvementTemporaire(std::pair<int, int> originalPos, std::pair<int, int> stealpos, Echequier* input) : originalPos_(originalPos), movePos_(stealpos), board_(input)
{
	stolen_ = board_->stealPiece(stealpos.first,stealpos.second);
	gameObjects::Piece* movePiece = board_->stealPiece(originalPos.first, originalPos.second);
	board_->displayPiece(stealpos.first,stealpos.second,movePiece);
}

MouvementTemporaire::~MouvementTemporaire()
{
	gameObjects::Piece* movePiece = board_->stealPiece(movePos_.first, movePos_.second);
	board_->displayPiece(originalPos_.first, originalPos_.second, movePiece);
	board_->displayPiece(movePos_.first, movePos_.second, stolen_);
}