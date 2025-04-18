#include "Tile.h"
#include "Roi.h"
#include "Fou.h"
#include "Chevalier.h"

gameInterface::Tile::Tile(int xpos, int ypos) : xpos_(xpos), ypos_(ypos), currPiece(nullptr), currentText((QString)""), currentTextValid((QString)"")
{
	
}

gameInterface::Tile::Tile(const Tile& other) : xpos_(other.xpos_), ypos_(other.ypos_), currPiece(nullptr), currentText(other.currentText), currentTextValid(other.currentTextValid), valid_(other.valid_)
{
}

void gameInterface::Tile::movePiece(gameObjects::Piece* movePiece)
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

void gameInterface::Tile::removePiece()
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

gameObjects::Piece* gameInterface::Tile::piece()
{
	return currPiece;
}

bool gameInterface::Tile::isRoi()
{
	if (dynamic_cast<gameObjects::Roi*>(piece()) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void gameInterface::Tile::addValid()
{
	valid_ = true;

	currentTextValid = currentText + (QString)"[V]";
}

void gameInterface::Tile::removeValid()
{
	valid_ = false;
	currentTextValid = currentText;
}

bool gameInterface::Tile::isValidMove() const
{
	return valid_;
}

QString gameInterface::Tile::operator*() const
{
	return currentTextValid;
}