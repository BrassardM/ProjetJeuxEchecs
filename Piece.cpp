#include "Piece.h"

using namespace gameObjects;

Piece::Piece() : pos_(0, 0), movesPattern_(), movesStraight_(0), isBlack_(false), text(){
}

Piece::Piece(Piece& other) : pos_(other.pos_), movesPattern_(other.movesPattern_),movesStraight_(other.movesStraight_), isBlack_(other.isBlack_), text(other.text) {}

Piece::Piece(std::vector<std::pair<int, int>> movesPattern, bool movesStraight, bool isBlack, QString textI) : movesPattern_(movesPattern), movesStraight_(movesStraight), isBlack_(isBlack), text(textI) {}

void Piece::movePos(int x, int y) {
	assert(x < 8);
	assert(x >= 0);
	assert(y < 8);
	assert(y >= 0);
	pos_ = { x, y };
}

bool gameObjects::Piece::isBlack()
{
	return isBlack_;
}

std::vector<std::pair<int, int>> Piece::operator*() const {
	std::vector<std::pair<int, int>> outVect;
	for (auto&& n : movesPattern_) {
		bool contained = false;
		if (!contained) {
			if (movesStraight_) {
				for (int j{}; j < 8; j++) {
					if ((unsigned)(n.first * j + pos_.first) < 8 && (unsigned)(n.second * j + pos_.second) < 8) {
						outVect.push_back({ n.first * j + pos_.first, n.second * j + pos_.second });
					}
					else {
						break;
					}
				}
			}
			else {
				if ((unsigned)(n.first + pos_.first) < 8 && (unsigned)(n.second + pos_.second) < 8) {
					outVect.push_back({ n.first + pos_.first, n.second + pos_.second });
				}
			}
		}
	}
	return outVect;
};

bool Piece::needsLOS() {
	return movesStraight_;
}

Piece::~Piece()
{
}