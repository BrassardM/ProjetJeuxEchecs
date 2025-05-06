#include <utility>
#include <vector>
#include <QString>

/**
* Ent�te pour le module qui contient l'historique des mouvements d'une partie d'�checs. Fait partie du mod�le.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Cr�� le 10 avril 2025
*/

#pragma once
class HistoriqueMouvements {
public:
	HistoriqueMouvements();
	HistoriqueMouvements(HistoriqueMouvements& other);
	void operator+=(std::tuple<int,int,int,int> sequence);
	QString operator*();
private:
	std::vector<std::tuple<int,int,int,int>> sequence_; //pos 1 : x pos 2 : y pos 3 : blackpromopiece pos 4 : whitepromopiece
};