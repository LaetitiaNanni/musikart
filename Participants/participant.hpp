#pragma once
#include "../Voiture/voiture.hpp"

struct Participant {
	public:
		virtual ~Participant(){}
		virtual int retournerPremierBonus() const = 0;
		virtual Voiture getVoiture()const;
		virtual Voiture setVoiture()const;

	private:
		int* listeBonus;
		Voiture voiture;
};