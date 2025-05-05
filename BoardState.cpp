#include "BoardState.h"



gameObjects::BoardState::BoardState(std::set<std::tuple<int, int, QString>> pieces, bool isBlack, bool blackCanCastle, bool whiteCanCastle) : pieces_(pieces), isBlack_(isBlack), blackCanCastle_(blackCanCastle), whiteCanCastle_(whiteCanCastle)
{
}

bool gameObjects::BoardState::operator==(const BoardState& other)
{
    return ((pieces_ == other.pieces_) && (isBlack_ == other.isBlack_) && (blackCanCastle_ == other.blackCanCastle_) && (whiteCanCastle_ == other.whiteCanCastle_));
}