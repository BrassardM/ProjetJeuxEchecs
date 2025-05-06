#include "Tile.h"
#include "Roi.h"
#include "Fou.h"
#include "Chevalier.h"

/**
* Module pour une case de l'échéquier. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/


using namespace gameObjects;

Tile::Tile(int xpos, int ypos) : xpos_(xpos), ypos_(ypos), currPiece_(nullptr), currentText_((QString)""), currentTextValid_((QString)"")
{
	
}

Tile::Tile(const Tile& other) : xpos_(other.xpos_), ypos_(other.ypos_), currPiece_(nullptr), currentText_(other.currentText_), currentTextValid_(other.currentTextValid_), valid_(other.valid_)
{
}

void Tile::movePiece(gameObjects::Piece* movePiece)
{
	assert(currPiece_ == nullptr);
	currPiece_ = movePiece;
	currentText_ = currPiece_->text;
	if (currPiece_->isBlack()) {
		currentText_ += (QString)" N";
	}
	currentTextValid_ = currentText_;
	currPiece_->movePos(xpos_, ypos_);
}

void Tile::removePiece()
{
	currPiece_ = nullptr;
	currentText_ = (QString)"";
	if (valid_) {
		currentTextValid_ = currentText_ + (QString)"[V]";
	}
	else {
		currentTextValid_ = currentText_;
	}
}

gameObjects::Piece* Tile::piece()
{
	return currPiece_;
}

bool Tile::isRoi()
{
	if (dynamic_cast<gameObjects::Roi*>(piece()) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void Tile::addValid()
{
	valid_ = true;

	currentTextValid_ = currentText_ + (QString)"[V]";
}

void Tile::removeValid()
{
	valid_ = false;
	currentTextValid_ = currentText_;
}

bool Tile::isValidMove() const
{
	return valid_;
}

QString Tile::operator*() const
{
	return currentTextValid_;
}