#include "bonus.hpp"
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <iostream>    /* cout */

#define NB_BONUS 3

// Constructeur
Bonus::Bonus(float xBonus, float yBonus, float zBonus, int typeBonus){
	position.x = xBonus;
	position.y = yBonus;
	position.z = zBonus; 

	// si le type est incorrect, on le met à 1
	if (typeBonus >=1 && typeBonus <= NB_BONUS){
		this->type = typeBonus;
	}
	else{
		this->type = 1;
	}

}

Bonus::Bonus (const Point3D& pos, int type): 
	position(pos), type(type){
}

Bonus::Bonus (const Bonus& other) :
	position(other.position), type(other.type){
}

////////////////////////////////////////////////////////////////////////////////
// Destructeur
Bonus::~Bonus(){

}
////////////////////////////////////////////////////////////////////////////////

// Récupérer la position
Point3D Bonus::getPosition(){
	return (this->position);
}


// Modifier la position
void Bonus::setPosition(const Point3D& pos){
	position = pos;
}

void Bonus::setPosition(float x, float y, float z){
	position.x=x;
	position.y=y;
	position.z=z;	
}


// Récupérer le type 
int Bonus::getType(){
	return (this->type);
}

// Modifier le type
void Bonus::setType(int typeBonus){
	if (typeBonus >=1 && typeBonus <= NB_BONUS){
		this->type = typeBonus;
	}
	else{
		std::cout << "Type incorrect" << std::endl;
	}
}

// génère un entier entre 1 et NB_BONUS (=3) (type de bonus)
// /!\ cette fonction n'est pas définie dans la classe Bonus
int RandomType(){
	srand (time(NULL));
  	int randomType = rand() % NB_BONUS + 1;
  	return randomType;
}
