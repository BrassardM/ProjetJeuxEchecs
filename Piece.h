#pragma once
#include <utility>
#include <vector>
#include <QString>

namespace gameObjects {
	class Piece
	{
	public:
		Piece();
		Piece(Piece& other);
		Piece(std::vector<std::pair<int, int>> movesPattern, bool movesStraight, bool isBlack, QString textI);
		void movePos(int x, int y);
		bool isBlack();
		bool needsLOS();
		virtual ~Piece();
		std::vector<std::pair<int, int>> operator*() const;
		const QString text;
	private :
		std::pair<int, int> pos_ = {0,0};
		std::vector<std::pair<int, int>> movesPattern_;
		bool movesStraight_ = 0;
		const bool isBlack_;
	};
}