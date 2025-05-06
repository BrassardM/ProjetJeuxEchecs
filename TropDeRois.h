#include <stdexcept>
#pragma once

/**
* Module d'erreur si jamais l'utilisateur essaie d'avoir plus que 2 rois. Fait partie du modèle.
*
* \file   Echequier.h
* \author Jiaqi Zhao et Matthew Brassard
* \date   6 mai 2025
* Créé le 10 avril 2025
*/

namespace errors {
	class TropDeRois : public std::logic_error {
	public:
		using logic_error::logic_error;
	};
}