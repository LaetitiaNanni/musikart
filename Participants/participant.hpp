#pragma once

#include "../Voiture/voiture.hpp"

class Participant {
	private:
		Voiture voiture; // voiture du participant
		//int* listeBonus; // liste des bonus que possède le participant

	public:
		// constructeurs	
		//Participant(Voiture voiture, int* listeBonus);
		//Participant(const Participant& other); // constructeur par copie


		// desctructeur
		//~Participant();

		// getteur
		//Voiture getVoiture();

		// setteur
		void setVoiture(Voiture voit);

		// LISTE BONUS
		// ajout bonus à la liste

		// retourner le 1er bonus de la liste
		//int retournerPremierBonus() const = 0;
		// enlever bonus de la liste

		// fonction qui vérifie si liste est vide


		// TIR 
		// fonction qui tir (prend en paramètre la position à laquelle il doit tirer)
			// enleve le bonus de la liste
			// ... 

};

/* 

Rechercher comment scanner les positions des joueurs
--> créer une liste chaînée (ou tableau) de positions des participants. 
// COM // -> Pour moi chacun des participants possède une voiture qui connait elle même sa position donc on n'a pas besoin de faire un tableau avec toutes les positions

	Chaque participant scanne en permanence (chaque tour de boucle) le tableau et regarde 
	si les coordonnées des autres participants sont comprises dans sa zone de tir ou non.
	Retourne un booléen si dans zone de tir
// COM // -> j'ai mis dans voiture une fonction scannerVoiture autour qui verifie si dans son rayon il n'y a pas d'autres voiture 
il suffira de s'en servir de la facon suivante (je pense)
Voiture voitureDuJoueur;
Voiture voitureAdversaire;
voitureDuJoueur.scannerVoiture(voitureAdversaire.position);
-> c'est une idée car ça va être un peu plus complexe que ça car la voiture est dans participant

	
	--> Adversaire : si dans zone de tir - epsilon, il tire (epsilon à déterminer)
// COM // -> si le booléen retourné par scannerVoiture est égal à vrai il tire

	--> Joueur : si dans zone de tir, avertissement graphique
// COM // -> si le booléen retourné par scannerVoiture est égal à vrai on proposera au joueur de tirer

// COM // -> du coup faut faire une fonction tir mais je ne sais pas trop à quoi il va ressembler et où le mettre


Définir zone de tir
	--> + petite pour les adversaires que pour le joueur? (éviter de définir / gérer epsilon)
// COM // ->la zone de tir je l'ai défini dans voiture je l'ai appelé rayon ou alors c'est un autre ?

*/