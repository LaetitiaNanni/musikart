#pragma once
#include "../Voiture/voiture.hpp"

/* 
Dans l'UML : voiture:int -> c'est normal?

Rechercher comment scanner les positions des joueurs
--> créer une liste chaînée (ou tableau) de positions des participants. 
	Chaque participant scanne en permanence (chaque tour de boucle) le tableau et regarde 
	si les coordonnées des autres participants sont comprises dans sa zone de tir ou non.
	Retourne un booléen si dans zone de tir
	--> Adversaire : si dans zone de tir - epsilon, il tire (epsilon à déterminer)
	--> Joueur : si dans zone de tir, avertissement graphique


Définir zone de tir
--> + petite pour les adversaires que pour le joueur? (évite de définir / gérer epsilon)

*/


/*Classe participant*/
/*
Attribut:
	Une liste de bonus
	Une voiture 

Méthode:
	Un destructeur
	Retourne le premier bonus de sa liste de bonus
	Retourne la voiture 
	Modifie la voiture
	Scanne la position des autres participants : Retourne un booléen 
	si un participant est dans la zone de tir

*/

class Participant {
	public:
		virtual ~Participant(){}
		virtual int retournerPremierBonus() const = 0;
		virtual Voiture getVoiture()const;
		virtual Voiture setVoiture();

	private:
		virtual int* listeBonus;
		virtual Voiture voiture;
		virtual int scannePositionAutreParticipant();
};