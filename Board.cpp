
#include "Board.h"
#include "Roi.h"
#include "Chevalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Tour.h"
#include "tooManyKings.h"
#include "Pion.h"

using namespace gameObjects;

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

Board::Board(const Board& other) : pieceMoving(other.pieceMoving), movingPos(other.movingPos), validMovingPosList(other.validMovingPosList), isBlackTurn(other.isBlackTurn), blackPieces(other.blackPieces), whitePieces(other.whitePieces), blackKingPos(other.blackKingPos), whiteKingPos(other.whiteKingPos)
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

bool Board::getBlackTurn() const
{
	return isBlackTurn;
}



void Board::resetAttributes(bool defaultreset)
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


void Board::updateBoard(int x, int y)
{
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
			isBlackTurn = not(isBlackTurn);
			tiles[x][y]->piece()->playerMove();
		}
		
		for (auto&& n : validMovingPosList) {
			tiles[n.first][n.second]->removeValid();
		}
		pieceMoving = false;
	}
	else {
		if (tiles[x][y]->piece() != nullptr) {
			if ((tiles[x][y]->piece()->isBlack() == isBlackTurn)) {
				std::vector<std::pair<int, int>> validBeforeCheck = checkValidMoves(x,y,isBlackTurn);
				std::vector<std::pair<int, int>> newValidMoves;

				for (auto&& n : validBeforeCheck) {
					if (miseEnEchec(x, y, n) == false) {
						newValidMoves.push_back(n);
						tiles[n.first][n.second]->addValid();
					}
				}
				if (!(newValidMoves.empty())) {
					pieceMoving = true;
					validMovingPosList = move(newValidMoves);
					movingPos = std::pair<int, int>(x, y);
				}
			}
		}
	}
}

void Board::displayPiece(int x, int y, gameObjects::Piece* piece) {
	if (piece != nullptr) {
		tiles[x][y]->movePiece(piece);
	}
}

void Board::addPiece(int x, int y, gameObjects::Piece* piece)
{
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
}

gameObjects::Piece* Board::stealPiece(int x, int y)
{
	gameObjects::Piece* outpiece = tiles[x][y]->piece();
	tiles[x][y]->removePiece();
	
	return outpiece;
}

bool Board::checkCheck(bool blackTurn) const
{
	bool found = false;
	if (blackTurn) {
		for (auto&& n : whitePieces) {
			auto validMoves = checkValidMoves(n.first, n.second, false);
			for (auto m : validMoves) {
				if (m == blackKingPos) {
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
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}
	}
	return found;
}

bool Board::ismoving() const
{
	return pieceMoving;
}

std::vector<std::pair<int, QString>> gameObjects::Board::operator*()
{
	std::vector<std::pair<int, QString>> outVect;
	for (int x{}; x < 8; x++) {
		for (int y{}; y < 8; y++) {
			outVect.push_back(std::pair<int, QString>{(x + y * 8), ** tiles[x][y]});
		}
	}
	return outVect;
}

bool gameObjects::Board::checkStalemate()
{
	bool stalemate = true;
	if (checkCheck(isBlackTurn) == false) {
		if (isBlackTurn) {
			for (auto&& n : blackPieces) {
				auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
				for (auto&& m : validMoves) {
					stalemate = stalemate && miseEnEchec(n.first, n.second, m);
				}
			}
		}
		else {
			for (auto&& n : whitePieces) {
				auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
				for (auto&& m : validMoves) {
					stalemate = stalemate && miseEnEchec(n.first, n.second, m);
				}
			}
		}
	}
	return stalemate;
}

bool gameObjects::Board::checkCheckmate()
{
	bool checkmate = true;
	if (checkCheck(isBlackTurn) == true) {
		if (isBlackTurn) {
			for (auto&& n : blackPieces) {
				auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
				for (auto&& m : validMoves) {
					checkmate = checkmate && miseEnEchec(n.first, n.second, m);
				}
			}
		}
		else {
			for (auto&& n : whitePieces) {
				auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
				for (auto&& m : validMoves) {
					checkmate = checkmate && miseEnEchec(n.first, n.second, m);
				}
			}
		}
	}
	return checkmate;
}

std::vector<std::pair<int, int>> Board::checkValidMoves(int x, int y, bool blackTurnLocal) const
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
	//is pawn
	else if (dynamic_cast<Pion*>(tiles[x][y]->piece()) != NULL) {
		for (auto&& n : possValidMoves) {
			if ((abs(n.first - x) - abs(n.second - y)) != 0) {
				if (tiles[n.first][n.second]->piece() == nullptr) {
					newValidMoves.push_back(n);
				}
			}
			else {
				if (tiles[n.first][n.second]->piece() != nullptr) {
					if (tiles[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
						newValidMoves.push_back(n);
					}
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

void Board::initDefaultBoard()
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

	gameObjects::Reine* qb = new gameObjects::Reine(true);
	gameObjects::Reine* qw = new gameObjects::Reine(false);

	gameObjects::Tour* t1b = new gameObjects::Tour(true);
	gameObjects::Tour* t2b = new gameObjects::Tour(true);
	gameObjects::Tour* t1w = new gameObjects::Tour(false);
	gameObjects::Tour* t2w = new gameObjects::Tour(false);

	gameObjects::Pion* p1b = new gameObjects::Pion(true);
	gameObjects::Pion* p2b = new gameObjects::Pion(true);
	gameObjects::Pion* p3b = new gameObjects::Pion(true);
	gameObjects::Pion* p4b = new gameObjects::Pion(true);
	gameObjects::Pion* p5b = new gameObjects::Pion(true);
	gameObjects::Pion* p6b = new gameObjects::Pion(true);
	gameObjects::Pion* p7b = new gameObjects::Pion(true);
	gameObjects::Pion* p8b = new gameObjects::Pion(true);

	gameObjects::Pion* p1w = new gameObjects::Pion(false);
	gameObjects::Pion* p2w = new gameObjects::Pion(false);
	gameObjects::Pion* p3w = new gameObjects::Pion(false);
	gameObjects::Pion* p4w = new gameObjects::Pion(false);
	gameObjects::Pion* p5w = new gameObjects::Pion(false);
	gameObjects::Pion* p6w = new gameObjects::Pion(false);
	gameObjects::Pion* p7w = new gameObjects::Pion(false);
	gameObjects::Pion* p8w = new gameObjects::Pion(false);


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

	addPiece(7, 3, qb);
	addPiece(0, 3, qw);

	addPiece(7, 7, t1b);
	addPiece(7, 0, t2b);
	addPiece(0, 7, t1w);
	addPiece(0, 0, t2w);

	addPiece(6, 7, p1b);
	addPiece(6, 6, p2b);
	addPiece(6, 5, p3b);
	addPiece(6, 4, p4b);
	addPiece(6, 3, p5b);
	addPiece(6, 2, p6b);
	addPiece(6, 1, p7b);
	addPiece(6, 0, p8b);
	addPiece(1, 7, p1w);
	addPiece(1, 6, p2w);
	addPiece(1, 5, p3w);
	addPiece(1, 4, p4w);
	addPiece(1, 3, p5w);
	addPiece(1, 2, p6w);
	addPiece(1, 1, p7w);
	addPiece(1, 0, p8w);
}

bool gameObjects::Board::miseEnEchec(int x, int y, std::pair<int, int> validMove)
{
	Piece* current = stealPiece(x, y);
	std::pair<int, int> blackKingPosBackup = blackKingPos;
	std::pair<int, int> whiteKingPosBackup = whiteKingPos;
	if (dynamic_cast<Roi*>(current) != NULL) {
		if (isBlackTurn) {
			blackKingPos = {validMove.first,validMove.second};
		}
		else {
			whiteKingPos = { validMove.first, validMove.second };
		}
	}
	Piece* replaced = nullptr;
	if (tiles[validMove.first][validMove.second]->piece() != nullptr) {
		replaced = stealPiece(validMove.first, validMove.second);
		if (isBlackTurn) {
			whitePieces.erase({ validMove.first,validMove.second });
		}
		else {
			blackPieces.erase({ validMove.first,validMove.second });
		}
	}
	displayPiece(validMove.first, validMove.second, current);
	bool miseEnEchec = checkCheck(isBlackTurn);
	displayPiece(x, y, current);
	tiles[validMove.first][validMove.second]->removePiece();
	if (replaced != nullptr) {
		if (isBlackTurn) {
			whitePieces.insert({ validMove.first,validMove.second });
		}
		else {
			blackPieces.insert({ validMove.first,validMove.second });
		}
		displayPiece(validMove.first, validMove.second, replaced);
	}
	blackKingPos = blackKingPosBackup;
	whiteKingPos = whiteKingPosBackup;
	return miseEnEchec;
}
