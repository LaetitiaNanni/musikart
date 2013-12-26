#pragma once
#include "Point3D.hpp"
#include <iostream>
#include <vector>

/*
Bonus : un type, une position en X et une position en Y
Un constructeur
Un destructeur
Un getType
Un getPosition

Le type est un int entre 1 et 3
*/

class Bonus{

public: 	
	// /!\ Appeler RandomType pour définir le type avant de construire le bonus
	Bonus (float x, float y, float z); // on construit les positions en x, y,z
	Bonus (const Point3D& pos); // on construit avec le Point3D
	Bonus (const Bonus& other);

	~Bonus();

	// gestion type
	int getType();
	void setType(int type);

	// gestion position
	Point3D getPosition();
	void setPosition(const Point3D& position);
	void setPosition(float x, float y, float z);

	// gestion estPris
	bool getEstPris();
	void setEstPris(bool nouveauEstPris);


private:
	int type; // 1 = ralentisseur, 2 = accelerateur, 3 = stock d'armes
	Point3D position; 
	bool estPris; // = false par défaut. Booléen qui indique si le bonus a été attrapé par un participant ou non

};

int RandomType(); 
/*
Retourne un int random entre 1 et NB_BONUS, pour définir le type de Bonus
*/

std::vector<Bonus> creerTableauBonus(std::vector<Point3D> tableauDePosition);
/*
Fonction appelée dans Circuit
Retourne un tableau de bonus
*/
