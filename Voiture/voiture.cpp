#include "voiture.hpp"

#include "../Bonus/bonus.hpp"


///////////////////
// Constructeurs
///////////////////
Voiture::Voiture(int vitesse, Point3D position, int puissance, int virage, int poids, int rayon) :
vitesse(vitesse), position(position), puissance(puissance), virage(virage),poids(poids), rayon(rayon)
{}

Voiture::Voiture(const Voiture& other) :
vitesse(other.vitesse), position(other.position), puissance(other.puissance), virage(other.virage),poids(other.poids), rayon(other.rayon)
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
int Voiture::getRayon(){
	return rayon;
}


///////////////////
// Setteurs
///////////////////
void Voiture::setVitesse(int vit) {
	vitesse = vit;
}

void Voiture::setPosition(const Point3D pos){
	position= pos;
}
void Voiture::setPosition(float x, float y, float z){
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

void Voiture::setRayon(int ray){
	rayon=ray;
}

bool Voiture::ScannerVoiture(Voiture voitureAScanner){ // formule à vérifier
	Point3D positionVoiture = voitureAScanner.getPosition();
	int d2 = (position.x-positionVoiture.x)*(position.x-positionVoiture.x) + 
			 (position.y-positionVoiture.y)*(position.y-positionVoiture.y) + 
			 (position.z-positionVoiture.z)*(position.z-positionVoiture.z);
	if (d2 > (rayon + voitureAScanner.getRayon())*(rayon + voitureAScanner.getRayon()))
    	return false;
	else
    	return true;
}

bool Voiture::ScannerBonus(Bonus bonusAScanner){ // formule à vérifier
	/*Point3D positionBonus = bonusAScanner.getPosition();
	int d2 = (position.x-positionBonus.x)*(position.x-positionBonus.x) + 
			 (position.y-positionBonus.y)*(position.y-positionBonus.y) + 
			 (position.z-positionBonus.z)*(position.z-positionBonus.z);
	/*if (d2 > (rayon)*(rayon)); 
    	return false;
	else*/
    	return true;
}