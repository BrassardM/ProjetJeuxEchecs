
#include "Board.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include "tooManyKings.h"

using namespace gameInterface;

Board::Board()
{
	for (int x{}; x < 8; x++) {
		for (int y{}; y < 8; y++) {
			Tile* newtile = new Tile(x, y);
			tiles[x][y] = newtile;
		}
	}
	//default reset
	initDefaultBoard();
}

Board::~Board()
{
	for (int i{}; i < 8; i++) {
		for (int j{}; j < 8; j++) {
			delete tiles[i][j]->piece();
			delete tiles[i][j];
		}
	}
}

gameInterface::Board::Board(const Board& other) : pieceMoving(other.pieceMoving), movingPos(other.movingPos), validMovingPosList(other.validMovingPosList), isBlackTurn(other.isBlackTurn), blackPieces(other.blackPieces), whitePieces(other.whitePieces), blackKingPos(other.blackKingPos), whiteKingPos(other.whiteKingPos)
{
	for (int x{}; x < 8; x++) {
		for (int y{}; y < 8; y++) {
			Tile* newtile = new Tile(*(other.tiles[x][y]));
			tiles[x][y] = newtile;
			if (other.tiles[x][y]->piece() != nullptr) {
				if (dynamic_cast<gameObjects::Roi*>(other.tiles[x][y]->piece()) != NULL) {
					gameObjects::Roi* roitemp = new gameObjects::Roi(other.tiles[x][y]->piece()->isBlack(), true);
					addPiece(x, y, roitemp);
				}
				else if (dynamic_cast<gameObjects::Chevalier*>(other.tiles[x][y]->piece()) != NULL) {
					gameObjects::Chevalier* chevtemp = new gameObjects::Chevalier(other.tiles[x][y]->piece()->isBlack());
					addPiece(x, y, chevtemp);
				}
				else if (dynamic_cast<gameObjects::Fou*>(other.tiles[x][y]->piece()) != NULL) {
					gameObjects::Fou* foutemp = new gameObjects::Fou(other.tiles[x][y]->piece()->isBlack());
					addPiece(x, y, foutemp);
				}
				//Ajouter tout les pieces quand elles vont être finies
			}
		}
	}
}

QString gameInterface::Board::displayTurn() const
{
	QString out;
	if (isBlackTurn) {
		out = (QString)"Tour des noirs";
	}
	else {
		out = (QString)"Tour des blancs";
	}
	return out;
}



void gameInterface::Board::resetAttributes(bool defaultreset)
{
	movingPos = {};
	pieceMoving = false;
	isBlackTurn = false;
	validMovingPosList = {};
	blackKingPos = {};
	whiteKingPos = {};
	blackPieces = {};
	whitePieces = {};


	for (int i{}; i < 8; i++) {
		for (int j{}; j < 8; j++) {
			if (tiles[i][j]->piece() != nullptr) {
				gameObjects::Piece* todelete = tiles[i][j]->piece();
				tiles[i][j]->removePiece();
				delete todelete;
			}
			tiles[i][j]->removeValid();
		}
	}
	if (defaultreset) {
		initDefaultBoard();
	}
}


std::vector<std::pair<int, QString>> gameInterface::Board::updateBoard(int x, int y)
{
	std::vector<std::pair<int, QString>> outVect;
	if (pieceMoving == true) {
		if (tiles[x][y]->isValidMove()) {
			if (tiles[x][y]->piece() != nullptr) {
				gameObjects::Piece* todelete = tiles[x][y]->piece();
				tiles[x][y]->removePiece();
				if (todelete->isBlack()) {
					blackPieces.erase(std::pair<int, int>(x, y));
				}
				else {
					whitePieces.erase(std::pair<int, int>(x, y));
				}
				delete todelete; //DELETING PIECES (CAN ADD TODELETE TO A LIST FOR)
			}
			tiles[x][y]->movePiece(tiles[movingPos.first][movingPos.second]->piece());
			tiles[movingPos.first][movingPos.second]->removePiece();
			outVect.push_back(std::pair<int, QString>{movingPos.first + movingPos.second * 8, ** tiles[movingPos.first][movingPos.second]});
			outVect.push_back(std::pair<int, QString>{(x + y * 8), ** tiles[x][y]});
			if (tiles[x][y]->piece()->isBlack()) {
				blackPieces.erase(std::pair<int, int>(movingPos.first, movingPos.second));
				blackPieces.insert(std::pair<int, int>(x, y));
				if (tiles[x][y]->isRoi()) {
					blackKingPos = std::pair<int, int>{ x,y };
				}
			}
			else {
				whitePieces.erase(std::pair<int, int>(movingPos.first, movingPos.second));
				whitePieces.insert(std::pair<int, int>(x, y));
				if (tiles[x][y]->isRoi()) {
					whiteKingPos = std::pair<int, int>{ x,y };
				}
			}
			isBlackTurn = (bool)(isBlackTurn ^ 1); //0 xor 1 -> 1 :: 1 xor 1 -> 0
		}
		
		for (auto&& n : validMovingPosList) {
			tiles[n.first][n.second]->removeValid();
			outVect.push_back(std::pair<int, QString>{n.first + n.second * 8, ** tiles[n.first][n.second]});
		}
		pieceMoving = false;
	}
	else {
		if (tiles[x][y]->piece() != nullptr) {
			if ((tiles[x][y]->piece()->isBlack() == isBlackTurn)) {
				std::vector<std::pair<int, int>> newValidMoves = checkValidMoves(x,y,isBlackTurn);
				
				for (auto&& n : newValidMoves) {
					tiles[n.first][n.second]->addValid();
					outVect.push_back(std::pair<int, QString>{(n.first + n.second * 8), ** tiles[n.first][n.second]});
				}
				if (!(newValidMoves.empty())) {
					pieceMoving = true;
					validMovingPosList = move(newValidMoves);
					movingPos = std::pair<int, int>(x, y);
				}
			}
		}
	}
	return outVect;
}

std::vector<std::pair<int, QString>> gameInterface::Board::updateBoard()
{
	std::vector<std::pair<int, QString>> outVect;
	for (int x{}; x < 8; x++) {
		for (int y{}; y < 8; y++) {
			outVect.push_back(std::pair<int, QString>{(x + y*8), **tiles[x][y]});
		}
	}
	return outVect;
}

void gameInterface::Board::displayPiece(int x, int y, gameObjects::Piece* piece) {
	if (piece != nullptr) {
		tiles[x][y]->movePiece(piece);
	}
}

std::vector<std::pair<int, QString>> gameInterface::Board::addPiece(int x, int y, gameObjects::Piece* piece)
{
	std::vector<std::pair<int, QString>> outVect;
	if (tiles[x][y]->piece() != nullptr) {
		gameObjects::Piece* todelete = tiles[x][y]->piece();
		tiles[x][y]->removePiece();
		if (todelete->isBlack()) {
			blackPieces.erase(std::pair<int,int>{ x,y });
		}
		else {
			whitePieces.erase(std::pair<int, int>{ x, y });
		}
		delete todelete;
	}
	if (piece != nullptr) {
		tiles[x][y]->movePiece(piece);
		if (piece->isBlack()) {
			blackPieces.insert(std::pair<int, int>{ x, y });
			if (tiles[x][y]->isRoi()) {
				blackKingPos = std::pair<int, int>{ x,y };
			}
		}
		else {
			whitePieces.insert(std::pair<int, int>{x, y});
			if (tiles[x][y]->isRoi()) {
				whiteKingPos = std::pair<int, int>{ x,y };
			}
		}
	}
	outVect.push_back(std::pair<int, QString>{(x + y * 8), ** tiles[x][y]});
	return outVect;
}

gameObjects::Piece* gameInterface::Board::stealPiece(int x, int y)
{
	gameObjects::Piece* outpiece = tiles[x][y]->piece();
	tiles[x][y]->removePiece();
	
	return outpiece;
}

QString gameInterface::Board::checkCheck() const
{
	QString out = (QString)"echec";
	bool found = false;
	if (isBlackTurn) {
		for (auto&& n : whitePieces) {
			auto validMoves = checkValidMoves(n.first, n.second, false);
			for (auto m : validMoves) {
				if (m == blackKingPos) {
					out = (QString)"Noir en " + out;
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
	else {
		for (auto&& n : blackPieces) {
			auto validMoves = checkValidMoves(n.first, n.second, true);
			for (auto m : validMoves) {
				if (m == whiteKingPos) {
					out = (QString)"Blanc en " + out;
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
	if (!found) {
		out = (QString)"Pas d'" + out;
	}
	return out;
}

bool gameInterface::Board::ismoving() const
{
	return pieceMoving;
}

std::vector<std::pair<int, int>> gameInterface::Board::checkValidMoves(int x, int y, bool blackTurnLocal) const
{
	std::vector<std::pair<int, int>> possValidMoves = **(tiles[x][y]->piece());
	std::vector<std::pair<int, int>> newValidMoves;
	//needs LOS
	if (tiles[x][y]->piece()->needsLOS()) {
		bool hasLOS = true;
		for (auto&& n : possValidMoves) {
			if (abs(x - n.first) <= 1 && abs(y - n.second) <= 1) {
				hasLOS = true;
			}
			if (hasLOS) {
				if (tiles[n.first][n.second]->piece() == nullptr) {
					newValidMoves.push_back(n);
				}
				else {
					if (tiles[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
						newValidMoves.push_back(n);

					}
					hasLOS = false;
				}
			}
		}
	}
	//no need LOS
	else {
		for (auto&& n : possValidMoves) {
			if (tiles[n.first][n.second]->piece() == nullptr) {
				newValidMoves.push_back(n);
			}
			else {
				if (tiles[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
					newValidMoves.push_back(n);
				}
			}
		}
	}
	return newValidMoves;
}

void gameInterface::Board::initDefaultBoard()
{
	//creation des pieces
	gameObjects::Roi* rb = new gameObjects::Roi(true);
	gameObjects::Roi* rw = new gameObjects::Roi(false);

	gameObjects::Fou* f1b = new gameObjects::Fou(true);
	gameObjects::Fou* f2b = new gameObjects::Fou(true);
	gameObjects::Fou* f1w = new gameObjects::Fou(false);
	gameObjects::Fou* f2w = new gameObjects::Fou(false);

	gameObjects::Chevalier* c1b = new gameObjects::Chevalier(true);
	gameObjects::Chevalier* c2b = new gameObjects::Chevalier(true);
	gameObjects::Chevalier* c1w = new gameObjects::Chevalier(false);
	gameObjects::Chevalier* c2w = new gameObjects::Chevalier(false);

	//placement des pieces
	addPiece(7, 4, rb);
	addPiece(0, 4, rw);

	addPiece(7, 5, f1b);
	addPiece(7, 2, f2b);
	addPiece(0, 5, f1w);
	addPiece(0, 2, f2w);

	addPiece(7, 6, c1b);
	addPiece(7, 1, c2b);
	addPiece(0, 6, c1w);
	addPiece(0, 1, c2w);
}
