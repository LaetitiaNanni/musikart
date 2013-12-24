#pragma once
#include "Point3D.hpp"

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
	Bonus (float x, float y, float z, int type); // on construit les positions en x, y,z
	Bonus (const Point3D& pos, int type); // on construit avec le Point3D
	Bonus (const Bonus& other);

	~Bonus();

	int getType();
	void setType(int type);

	Point3D getPosition();
	void setPosition(const Point3D& position);
	void setPosition(float x, float y, float z);

private:
	int type; // 1 = ralentisseur, 2 = accelerateur, 3 = stock d'armes
	Point3D position; 

};

int RandomType(); 
/*
Retourne un int random entre 1 et NB_BONUS, pour définir le type de Bonus
*/