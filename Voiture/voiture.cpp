#include "voiture.hpp"


///////////////////
// Constructeurs
///////////////////
Voiture::Voiture(int vitesse, Point3D position, int puissance, int virage, int poids) :
vitesse(vitesse), position(position), puissance(puissance), virage(virage),poids(poids)
{}

Voiture::Voiture(const Voiture& other) :
vitesse(other.vitesse), position(other.position), puissance(other.puissance), virage(other.virage),poids(other.poids)
{}


//Destructeur
//Voiture::~Voiture();


///////////////////
// Getteurs
///////////////////
int Voiture::getVitesse(){
	return vitesse;
}
Point3D Voiture::getPosition(){
	return position;
}
int Voiture::getPuissance(){
	return puissance;
}
int Voiture::getVirage(){
	return virage;
}
int Voiture::getPoids(){
	return poids;
}


///////////////////
// Setteurs
///////////////////
void Voiture::setVitesse(int vit) {
	vitesse = vit;
}

void Voiture::setPosition(Point3D pos){
	position= pos;
}
void Voiture::setPosition(int x, int y, int z){
	position.x=x;
	position.y=y;
	position.z=z;	
}
void Voiture::setPuissance(int pui){
	puissance = pui;
}
void Voiture::setVirage(int vir){
	virage= vir;
}
void Voiture::setPoids(int poi){
	poids= poi;
}