#include "LogMoves.h"
#include <tuple>

LogMoves::LogMoves()
{
	
}

LogMoves::LogMoves(LogMoves& other): 
sequence_(other.sequence_)
{
}

void LogMoves::operator+=(std::tuple<int, int, int, int> sequence)
{
	sequence_.push_back(sequence);
}

QString LogMoves::operator*()
{
	QString out;
	out = "gameObjects::Board b;\nb.playSequence(std::vector<std::tuple<int,int,int,int>>{";
	int i{};
	for (auto&& n : sequence_) {
		out += (QString)"\n{" + QString::number(get<0>(n)) + (QString)", " + QString::number(get<1>(n)) + ", " + QString::number(get<2>(n)) + ", " + QString::number(get<3>(n)) + "}";
		if (i < ((int)sequence_.size() - 1)) {
			out += ", ";
		}
		i++;
	}
	out += "});";
	return out;
}
