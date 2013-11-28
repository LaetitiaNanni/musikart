#pragma once

/*
Bonus : un type, une position en X et une position en Y
Un constructeur
Un destructeur
Un getType
Un getX et un getY

Le type est un int entre 1 et 3
*/

class Bonus{

public: 	
	Bonus (float x, float y, int type);
	~Bonus();
	int getType();
	float getX();
	float getY();
private:
	int type; // 1 = ralentisseur, 2 = accelerateur, 3 = stock d'armes
	float x; // position en x
	float y; // position en y

};

int RandomType(); 
/*
Retourne un int random entre 1 et NB_BONUS, pour définir le type de Bonus
*/