#pragma once
#include "participant.hpp"


/*
Hérite de la classe Participant

En plus :
Un script qui lui permet d'avoir un parcours prédéfini

///// A vérifier 
--> le script sera un tableau de point2D ou de x y z par lequel l'adversaire va passer


*/


class AdversaireParticipant : public Participant {
	public:
		AdversaireParticipant();
		virtual ~AdversaireParticipant();
		virtual int retournerPremierBonus() const = 0;
		virtual Voiture getVoiture()const;
		virtual Voiture setVoiture();
	private:
		virtual int* listeBonus;
		virtual Voiture voiture;
		Point2D* script;
};
		
