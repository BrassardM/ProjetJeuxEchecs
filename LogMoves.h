#include <utility>
#include <vector>
#include <QString>

#pragma once
class LogMoves {
public:
	LogMoves();
	LogMoves(LogMoves& other);
	void operator+=(std::tuple<int,int,int,int> sequence);
	QString operator*();
private:
	std::vector<std::tuple<int,int,int,int>> sequence_; //pos 1 : x pos 2 : y pos 3 : blackpromopiece pos 4 : whitepromopiece
};