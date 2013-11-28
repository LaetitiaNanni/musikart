#include "bonus.hpp"
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */

#define NB_BONUS 3

// Constructeur : on met le type à 0 par défaut (ne correspond à rien)
Bonus::Bonus(float x, float y, int type) : 
	x(x), y(y), type(type) {
}

// Destructeur
Bonus::~Bonus(){

}

// Récupérer X
float Bonus::getX(){
	return (this->x);
}

// Récupérer Y
float Bonus::getY(){
	return (this->y);
}

// Récupéré le type 
int Bonus::getType(){
	return (this->type);
}

// génère un entier entre 1 et NB_BONUS (=3) (type de bonus)
// /!\ cette fonction n'est pas définie dans la classe Bonus
int RandomType(){
	srand (time(NULL));
  	int randomType = rand() % NB_BONUS + 1;
  	return randomType;
}
