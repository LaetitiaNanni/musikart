#pragma once
#include "Point3D.hpp"
#include "../Bonus/bonus.hpp"

#define NB_ZONE_BONUS 10


#include <iostream>
#include <vector>

/*****************

BONUS :
Le circuit comporte NB_ZONE_BONUS zones de bonus. 
zones de bonus = Point3D
Dans ces zones de bonus des bonus apparaissent. (il n'apparaissent qu'à ces endroits)
NB : ces "zones" ne sont pas indiquées à l'utilisateur, elles sont juste là pour le code

Les zones de bonus sont rangés dans un tableau (de taille NB_ZONE_BONUS)

On construit des bonus sur ces zones de bonus.

Un autre tableau liste les bonus (pointeurs vers les bonus créés)

Chaque fois qu'un bonus est attrapé, on recrée un bonus



CREATION DES SCRIPTS DE PARCOURS:




********************/




class Circuit{
public:
	Circuit(char* nom="circuit1"); // constructeur, de nom "circuit1" par défaut
	/*
	Appelle recupererPositionZoneDeBonus() pour construire zoneDeBonus
	Appelle creerTableauBonus() (fonction de la classe Bonus) pour construire tableauDeBonus
	*/

	~Circuit(); // destructeur

	std::vector<Point3D> getZoneDeBonus(); // récupère zoneDeBonus

	std::vector<Bonus> getTableauDeBonus(); // récupère tableauDeBonus
	

	void setNom(char* nouveauNom); // change le nom du parcours
	char* getNom();


	// BONUS
	std::vector<int> scannerEtatBonus(); // regarde quels bonus ont été pris (estPris = true)
	/*
	Fonction appelée dans creerBonusManquant
	Retourne un vector contenant les ID des bonus manquants dans tableauDeBonus
	*/



	////////////////////////////////////////////////////////////////////////////////////////
	/* ATTENTION : A MODIFIER */
	std::vector<Point3D> creerPositionZoneDeBonus(); // position des zones de bonus 
	/*
	Génère les zones de bonus depuis le circuit
	*/
	////////////////////////////////////////////////////////////////////////////////////////




	void creerBonusManquant(); // créer les bonus manquants au fur et à mesure
	/*
	Appelle scannerEtatBonus() pour regarder quels bonus sont manquants.
	Construit un bonus aux zoneDeBonus vide.
	Met les nouveaux bonus aux endroits correspondants dans tableauDeBonus
	*/




	////////////////////////////////////////////////////////////////////////////////////////
	/* ATTENTION : A MODIFIER */
	// SCRIPT DE PARCOURS

	void creerScriptParcours1(); // coordonnées de parcours1 des adversaires
	void creerScriptParcours2(); // coordonnées de parcours2 des adversaires
	void creerScriptParcours3(); // coordonnées de parcours3 des adversaires

	/////////////////////////////////////////////////////////////////////////////////////

private:

	char* nom; // circuit 1 ou circuit 2 selon 

	std::vector<Point3D> zoneDeBonus; // tableau de zone de bonus
	std::vector<Bonus> tableauDeBonus; //tableau de bonus

	std::vector<Point3D> parcours1;
	std::vector<Point3D> parcours2;
	std::vector<Point3D> parcours3;

};

