#include "bonus.hpp"
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <iostream>    /* cout */

#define NB_BONUS 3

// Constructeur
Bonus::Bonus(float xBonus, float yBonus, float zBonus){

	int typeBonus = RandomType();

	position.x = xBonus;
	position.y = yBonus;
	position.z = zBonus; 

	// si le type est incorrect, on le met à 1
	this->type = typeBonus;
	
	estPris = false;

}

Bonus::Bonus (const Point3D& pos): 
	position(pos), type(RandomType()), estPris(false){
}

Bonus::Bonus (const Bonus& other) :
	position(other.position), type(other.type), estPris(false){
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


// Récupérer estpris
bool Bonus::getEstPris(){
	return (this->estPris);
}

// Modifier estPris
void Bonus::setEstPris(bool nouveauEstPris){
	estPris = nouveauEstPris;
}


// génère un entier entre 1 et NB_BONUS (=3) (type de bonus)
// /!\ cette fonction n'est pas définie dans la classe Bonus
int RandomType(){
	srand (time(NULL));
  	int randomType = rand() % NB_BONUS + 1;
  	return randomType;
}


std::vector<Bonus> creerTableauBonus(std::vector<Point3D> tableauDePosition){
	if (tableauDePosition.size() < 0 ){
		std::cout <<" Erreur, tableau de position vide "<< std::endl;
	}
	std::vector<Bonus> tableau;
	for (int i = 0; i < tableauDePosition.size(); ++i){
		Bonus nouveauBonus = Bonus(tableauDePosition[i]);
		tableau.push_back(nouveauBonus);
	}

	return tableau;
}