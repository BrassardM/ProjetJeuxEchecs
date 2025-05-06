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
	logBoardState();
}

Board::~Board()
{
	for (int i{}; i < 8; i++) {
		for (int j{}; j < 8; j++) {
			delete tiles[i][j]->piece();
			delete tiles[i][j];
		}
	}
	for (auto&& n : boardStateLog) {
		delete n;
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

void gameObjects::Board::playSequence(const std::vector<std::tuple<int, int, int, int>>& sequence)
{
	resetAttributes(true);
	int blackPromBack = blackProm;
	int whitePromBack = whiteProm;
	for (auto&& n : sequence) {
		blackProm = get<2>(n);
		whiteProm = get<3>(n);
		updateBoard(std::get<0>(n), std::get<1>(n));
	}
	blackProm = blackPromBack;
	whiteProm = whitePromBack;
}

LogMoves& gameObjects::Board::returnSequence()
{
	return logMoves;
}

int gameObjects::Board::nPieces() const
{
	return (int)blackPieces.size() + (int)whitePieces.size();
}

bool gameObjects::Board::checkCheckmate() const
{
	return checkCheck(isBlackTurn) && gameover;
}

bool gameObjects::Board::checkStalemate() const
{
	return !checkCheck(isBlackTurn) && gameover;
}

bool gameObjects::Board::checkInCheck() const
{
	return checkCheck(isBlackTurn);
}

bool gameObjects::Board::checkKingPos(int x, int y)
{
	return (std::pair<int,int>(x,y) == blackKingPos || std::pair<int, int>(x, y) == whiteKingPos);
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
	blackKingPos = {-1,-1};
	whiteKingPos = {-1,-1};
	nextEnPassant = { -1,-1 };
	blackPieces = {};
	whitePieces = {};
	gameover = false;
	sincelasttaken = 0;
	logMoves = {};

	for (auto&& n : boardStateLog) {
		delete n;
	}
	boardStateLog = {};

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
	logBoardState();
}

void Board::updateBoard(int x, int y)
{
	if (!gameover){
		if (pieceMoving == true) {
			if (tiles[x][y]->isValidMove()) {
				if (tiles[x][y]->piece() != nullptr) {
					sincelasttaken = -1;
					gameObjects::Piece* todelete = tiles[x][y]->piece();
					tiles[x][y]->removePiece();
					if (todelete->isBlack()) {
						blackPieces.erase(std::pair<int, int>(x, y));
					}
					else {
						whitePieces.erase(std::pair<int, int>(x, y));
					}
					delete todelete; //DELETING PIECES
				}
				// en passant
				else if ((dynamic_cast<Pion*>(tiles[movingPos.first][movingPos.second]->piece()) != NULL) && (abs(movingPos.first - x) - abs(movingPos.second - y) == 0)){
					sincelasttaken = -1;
					gameObjects::Piece* todelete = tiles[x- (1 - 2 * isBlackTurn)][y]->piece();
					tiles[x- (1 - 2 * isBlackTurn)][y]->removePiece();
					if (todelete->isBlack()) {
						blackPieces.erase(std::pair<int, int>(x- (1 - 2 * isBlackTurn), y));
					}
					else {
						whitePieces.erase(std::pair<int, int>(x- (1 - 2 * isBlackTurn), y));
					}
					delete todelete; //DELETING PIECES
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

				//castling
				if ((movingPos.second - y == -2) && dynamic_cast<Roi*>(tiles[x][y]->piece()) != NULL) {
					tiles[x][y - 1]->movePiece(tiles[x][y + 1]->piece());
					tiles[x][y + 1]->removePiece();
					if (isBlackTurn) {
						blackPieces.erase(std::pair<int, int>{x, y + 1});
						blackPieces.insert(std::pair<int, int>{x, y - 1});
					}
					else {
						whitePieces.erase(std::pair<int, int>{x, y + 1});
						whitePieces.insert(std::pair<int, int>{x, y - 1});
					}
				}
				else if ((movingPos.second - y == 2) && dynamic_cast<Roi*>(tiles[x][y]->piece()) != NULL) {
					tiles[x][y + 1]->movePiece(tiles[x][y - 2]->piece());
					tiles[x][y - 2]->removePiece();
					if (isBlackTurn) {
						blackPieces.erase(std::pair<int, int>{x, y - 2});
						blackPieces.insert(std::pair<int, int>{x, y + 1});
					}
					else {
						whitePieces.erase(std::pair<int, int>{x, y - 2});
						whitePieces.insert(std::pair<int, int>{x, y + 1});
					}
				}
 
				//promoting
				if ((x == 7 || x == 0) && dynamic_cast<Pion*>(tiles[x][y]->piece()) != NULL) {
					promote(x, y);
				}
				//next en passant
				if (dynamic_cast<Pion*>(tiles[x][y]->piece()) != NULL && (abs(movingPos.first - x) == 2)) {
					nextEnPassant = std::pair<int, int>{movingPos.first + (1-2*isBlackTurn),y};
				}
				else {
					nextEnPassant = std::pair<int, int>{ -1,-1 };
				}
				
				isBlackTurn = not(isBlackTurn);
				tiles[x][y]->piece()->playerMove();
				sincelasttaken++;
				logBoardState();
				checkGame();
				
				//pour faire les tests
				std::tuple<int, int, int, int> log = { movingPos.first, movingPos.second, blackProm, whiteProm};
				logMoves += log;
				std::tuple<int, int, int, int> log2 = { x, y, blackProm, whiteProm };
				logMoves += log2;
			}

			for (auto&& n : validMovingPosList) {
				tiles[n.first][n.second]->removeValid();
			}
			pieceMoving = false;
		}
		else {
			if (tiles[x][y]->piece() != nullptr) {
				if ((tiles[x][y]->piece()->isBlack() == isBlackTurn)) {
					std::vector<std::pair<int, int>> validBeforeCheck = checkValidMoves(x, y, isBlackTurn, true);
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

bool gameObjects::Board::getState() const {
	return gameover;
};

void gameObjects::Board::checkGame()
{
	gameover = true;

	if (blackKingPos != std::pair<int,int>{-1,-1} || whiteKingPos != std::pair<int, int>{-1, -1}) {
		if (!threeSameStates()) {
			if (!insufficientmaterial()) {
				if (sincelasttaken < 100) { //50 move rule
					if (isBlackTurn) {
						for (auto&& n : blackPieces) {
							auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
							for (auto&& m : validMoves) {
								gameover = gameover && miseEnEchec(n.first, n.second, m);
							}
						}
					}
					else {
						for (auto&& n : whitePieces) {
							auto validMoves = checkValidMoves(n.first, n.second, isBlackTurn);
							for (auto&& m : validMoves) {
								gameover = gameover && miseEnEchec(n.first, n.second, m);
							}
						}
					}
				}
			}
		}
	}
}

void gameObjects::Board::logBoardState(bool sameTurn)
{
	std::set<std::tuple<int, int, QString>> setPieces;
	for (auto&& n : blackPieces) {
		setPieces.insert(std::tuple<int, int, QString>{n.first, n.second, tiles[n.first][n.second]->operator*() });
	}
	for (auto&& n : whitePieces) {
		setPieces.insert(std::tuple<int, int, QString>{n.first, n.second, tiles[n.first][n.second]->operator*() });
	}
	BoardState* b;
	if (blackKingPos == std::pair<int,int>(-1,-1) || whiteKingPos == std::pair<int, int>(-1, -1)) {
		b = new BoardState(setPieces, isBlackTurn, false, false);
	}
	else {
		b = new BoardState(setPieces, isBlackTurn, !(tiles[blackKingPos.first][blackKingPos.second]->piece()->getHasMoved()), !(tiles[whiteKingPos.first][whiteKingPos.second]->piece()->getHasMoved()));
	}
	if (sameTurn) {
		boardStateLog.pop_back();
		boardStateLog.push_back(b);
	}
	else {
		boardStateLog.push_back(b);
	}
}

void gameObjects::Board::changePromotionPiece(int x, bool isBlack)
{
	if (isBlack) {
		blackProm = x;
	}
	else {
		whiteProm = x;
	}
}

std::vector<std::pair<int, int>> Board::checkValidMoves(int x, int y, bool blackTurnLocal, bool canCastle) const
{
	std::vector<std::pair<int, int>> possValidMoves = (tiles[x][y]->piece()->returnMoves());
	std::vector<std::pair<int, int>> newValidMoves;
	//movesStraight
	if (tiles[x][y]->piece()->getStraight()) {
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
				else if (n == nextEnPassant) {
					newValidMoves.push_back(n);
				}
			}
		}
	}
	//is king that can castle
	else if (canCastle && (dynamic_cast<Roi*>(tiles[x][y]->piece()) != NULL) && (tiles[x][y]->piece()->getHasMoved() == false)) {
		for (auto&& n : possValidMoves) {
			if ((n.second - y) == 2) {
				if ((y + 3) <= 7) {
					if ((dynamic_cast<Tour*>(tiles[x][y + 3]->piece()) != NULL) && (tiles[x][y + 3]->piece()->isBlack() == tiles[x][y]->piece()->isBlack()) && tiles[x][y + 3]->piece()->getHasMoved() == false && (tiles[x][y + 1]->piece() == nullptr) && (tiles[x][y + 2]->piece() == nullptr) && !checkCheck(isBlackTurn)) {
						newValidMoves.push_back(n);
					}
				}
			}
			else if ((n.second - y) == -2) {
				if ((y - 4) >= 0) {
					if ((dynamic_cast<Tour*>(tiles[x][y - 4]->piece()) != NULL) && (tiles[x][y - 4]->piece()->isBlack() == tiles[x][y]->piece()->isBlack()) && tiles[x][y - 4]->piece()->getHasMoved() == false && (tiles[x][y - 1]->piece() == nullptr) && (tiles[x][y - 2]->piece() == nullptr) && (tiles[x][y - 3]->piece() == nullptr) && !checkCheck(isBlackTurn)) {
						newValidMoves.push_back(n);
					}
				}
			}
			else if (tiles[n.first][n.second]->piece() == nullptr) {
				newValidMoves.push_back(n);
			}
			else {
				if (tiles[n.first][n.second]->piece()->isBlack() != blackTurnLocal) {
					newValidMoves.push_back(n);
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

bool gameObjects::Board::insufficientmaterial()
{
	int nP{};

	bool insufficientMatN = true;
	for (auto&& n : blackPieces) {
		if (dynamic_cast<Reine*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Tour*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Pion*>(tiles[n.first][n.second]->piece()) != NULL) {
			insufficientMatN = false;
			break;
		}
		else if (dynamic_cast<Fou*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Chevalier*>(tiles[n.first][n.second]->piece()) != NULL) {
			nP++;
			if (nP > 1) {
				insufficientMatN = false;
			}
		}
	}

	bool insufficientMatB = true;
	nP = {};
	for (auto&& n : whitePieces) {
		if (dynamic_cast<Reine*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Tour*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Pion*>(tiles[n.first][n.second]->piece()) != NULL) {
			insufficientMatB = false;
			break;
		}
		else if (dynamic_cast<Fou*>(tiles[n.first][n.second]->piece()) != NULL || dynamic_cast<Chevalier*>(tiles[n.first][n.second]->piece()) != NULL) {
			nP++;
			if (nP > 1) {
				insufficientMatB = false;
				break;
			}
		}
	}
	return (insufficientMatN && insufficientMatB);
}

bool gameObjects::Board::threeSameStates()
{
	int equalsCounter = 0;
	BoardState b = *(boardStateLog.back());
	for (auto it = boardStateLog.begin(); it != (boardStateLog.end() - 1); it++) {
		BoardState a = **it;
		if (a.operator==(b)) {
			equalsCounter++;
		}
	}
	return (equalsCounter > 1);
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

void gameObjects::Board::promote(int x, int y)
{
	gameObjects::Piece* todelete = tiles[x][y]->piece();
	tiles[x][y]->removePiece();
	delete todelete;
	if (isBlackTurn) {
		if (blackProm == 0) {
			Reine* q = new Reine(isBlackTurn);
			addPiece(x, y, q);
		}
		else if (blackProm == 1) {
			Fou* f = new Fou(isBlackTurn);
			addPiece(x, y, f);
		}
		else if (blackProm == 2) {
			Tour* t = new Tour(isBlackTurn);
			addPiece(x, y, t);
		}
		else {
			Chevalier* c = new Chevalier(isBlackTurn);
			addPiece(x, y, c);
		}
	}
	else {
		if (whiteProm == 0) {
			Reine* q = new Reine(isBlackTurn);
			addPiece(x, y, q);
		}
		else if (whiteProm == 1) {
			Fou* f = new Fou(isBlackTurn);
			addPiece(x, y, f);
		}
		else if (whiteProm == 2) {
			Tour* t = new Tour(isBlackTurn);
			addPiece(x, y, t);
		}
		else {
			Chevalier* c = new Chevalier(isBlackTurn);
			addPiece(x, y, c);
		}
	}
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