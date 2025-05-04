#include "Tile.h"
#include "Roi.h"
#include "Fou.h"
#include "Chevalier.h"

using namespace gameObjects;

Tile::Tile(int xpos, int ypos) : xpos_(xpos), ypos_(ypos), currPiece(nullptr), currentText((QString)""), currentTextValid((QString)"")
{
	
}

Tile::Tile(const Tile& other) : xpos_(other.xpos_), ypos_(other.ypos_), currPiece(nullptr), currentText(other.currentText), currentTextValid(other.currentTextValid), valid_(other.valid_)
{
}

void Tile::movePiece(gameObjects::Piece* movePiece)
{
	assert(currPiece == nullptr);
	currPiece = movePiece;
	currentText = currPiece->text;
	if (currPiece->isBlack()) {
		currentText += (QString)" N";
	}
	currentTextValid = currentText;
	currPiece->movePos(xpos_, ypos_);
}

void Tile::removePiece()
{
	currPiece = nullptr;
	currentText = (QString)"";
	if (valid_) {
		currentTextValid = currentText + (QString)"[V]";
	}
	else {
		currentTextValid = currentText;
	}
}

gameObjects::Piece* Tile::piece()
{
	return currPiece;
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

	currentTextValid = currentText + (QString)"[V]";
}

void Tile::removeValid()
{
	valid_ = false;
	currentTextValid = currentText;
}

bool Tile::isValidMove() const
{
	return valid_;
}

QString Tile::operator*() const
{
	return currentTextValid;
}