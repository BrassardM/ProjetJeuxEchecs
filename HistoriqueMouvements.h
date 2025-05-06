#include <utility>
#include <vector>
#include <QString>

/**
* Entête pour le module qui contient l'historique des mouvements d'une partie d'échecs. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
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