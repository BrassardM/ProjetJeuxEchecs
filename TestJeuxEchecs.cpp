// Fichier de test pour le projet Jeux d'�checs
// Ce fichier contient les tests unitaires pour le projet Jeux d'�checs.
// Pour le moment, il y a seulement des tests d'exemple.
// Vous devez ajouter vos propres tests pour v�rifier le bon fonctionnement de votre code.
// 
// 
//
// Include ici les headers de votre partie de code � tester

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#include "Board.h"
#endif
#ifdef TEST

TEST(Test, exempleDeTest)
{
	EXPECT_EQ(1, 1);
}

TEST(Test, exempleDeTest2)
{
	EXPECT_FALSE(1 == 2);
}

TEST(Test, capture) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 4, 3, 0, 0 }});
	EXPECT_TRUE(b.nPieces() == 31);
}

TEST(Test, echec) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 2, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 0, 3, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 5, 0, 0 }});
	EXPECT_TRUE(b.checkInCheck());
}

TEST(Test, enPassantTest) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 5, 5, 0, 0 }});
	EXPECT_TRUE(b.nPieces() == 31); 
}

TEST(Test, checkMate1) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 0, 3, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 0, 5, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 7, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 4, 1, 0, 0 }});
	EXPECT_TRUE(b.checkCheckmate());
}

TEST(Test, checkMate2) { //test si en passant a march�
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{0, 1, 0, 0},
		{ 2, 2, 0, 0 },
		{ 7, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 0, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 4, 6, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 4, 6, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 0, 5, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 7, 6, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 2, 6, 0, 0 }});
	EXPECT_TRUE(b.checkCheckmate());
}

TEST(Test, checkmate3) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 7, 5, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 7, 3, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 1, 5, 0, 0 }});
	EXPECT_TRUE(b.checkCheckmate());
}

TEST(Test, threefoldRepetition) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 4, 0, 0 }});
	EXPECT_TRUE(b.checkStalemate());
}

TEST(Test, fiftyMoveRule) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 0, 0, 0},
		{ 3, 0, 0, 0 },
		{ 6, 0, 0, 0 },
		{ 4, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 3, 6, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 4, 6, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 7, 0, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 7, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 7, 0, 0, 0 },
		{ 6, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 6, 0, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 6, 0, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 2, 6, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 2, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 3, 0, 0 }});
	EXPECT_TRUE(b.checkStalemate());
}

TEST(Test, insufficentMaterial) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 7, 1, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 0, 3, 0, 0 },
		{ 7, 3, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 7, 3, 0, 0 },
		{ 0, 2, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 0, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 1, 2, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 5, 7, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 2, 7, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 5, 2, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 7, 3, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 1, 6, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 0, 7, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 6, 0, 0, 0 },
		{ 4, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 4, 0, 0, 0 },
		{ 3, 0, 0, 0 },
		{ 2, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 3, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 1, 7, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 7, 2, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 3, 7, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 7, 6, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 7, 5, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 1, 5, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 7, 0, 0, 0 },
		{ 7, 6, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 4, 2, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 1, 4, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 7, 6, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 4, 7, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 6, 7, 0, 0 },
		{ 3, 2, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 2, 2, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 3, 5, 0, 0 },
		{ 4, 6, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 4, 6, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 5, 6, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 7, 7, 0, 0 },
		{ 6, 6, 0, 0 },
		{ 1, 0, 1, 3 },
		{ 0, 0, 1, 3 }, // roi + fou vs. roi + pion 
		{ 6, 6, 1, 3 },
		{ 6, 5, 1, 3 },
		{ 3, 4, 1, 3 },
		{ 4, 4, 1, 3 },
		{ 6, 7, 1, 3 },
		{ 7, 7, 1, 3 }}); //roi + fou vs. roi + chevalier (impossible de gagner)
		EXPECT_TRUE(b.checkStalemate());
}

TEST(Test, testPromotion) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 3, 4, 0, 0 },
		{ 6, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 6, 5, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 4, 5, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 4, 3, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 5, 3, 0, 0 },
		{ 6, 2, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 0, 2, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 2, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 3, 0, 0 },
		{ 3, 1, 0, 0 },
		{ 1, 0, 3, 3 },
		{ 0, 1, 3, 3 },
		{ 3, 1, 3, 0 },
		{ 4, 2, 3, 0 },
		{ 0, 1, 3, 0 },
		{ 2, 0, 3, 0 },
		{ 6, 4, 3, 0 },
		{ 7, 5, 3, 0 }});
	EXPECT_TRUE(b.checkCheckmate());
}

TEST(Test, towering) {
	gameObjects::Board b;
	b.playSequence(std::vector<std::tuple<int, int, int, int>>{
		{1, 4, 0, 0},
		{ 2, 4, 0, 0 },
		{ 6, 4, 0, 0 },
		{ 5, 4, 0, 0 },
		{ 0, 5, 0, 0 },
		{ 4, 1, 0, 0 },
		{ 7, 3, 0, 0 },
		{ 5, 5, 0, 0 },
		{ 0, 6, 0, 0 },
		{ 2, 5, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 5, 1, 0, 0 },
		{ 0, 4, 0, 0 },
		{ 0, 6, 0, 0 }, // tower
		{ 7, 2, 0, 0 },
		{ 6, 1, 0, 0 },
		{ 2, 4, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 7, 1, 0, 0 },
		{ 5, 0, 0, 0 },
		{ 3, 4, 0, 0 },
		{ 4, 4, 0, 0 },
		{ 7, 4, 0, 0 },
		{ 7, 2, 0, 0 }}); // tower
	EXPECT_TRUE(b.checkKingPos(0, 6) && b.checkKingPos(7, 2));
}

#endif