#pragma once

#include "Point3D.hpp"
#include "../Bonus/bonus.hpp"

class Voiture {
	private:
		int vitesse;
		Point3D position;
		int puissance;
		int virage;
		int poids;
		int rayon; // rayon autour de la voiture dans lequel on pourra envoyer à un adversaire un bonus par exemple
	public:
		// Constructeurs
		Voiture(int vitesse, Point3D position, int puissance, int virage, int poids, int rayon);
		//Voiture(); //par défaut -> pas de sens ici je pense
		Voiture(const Voiture& other); // constructeur par copie

		//Destructeur
		//~Voiture();

		// Getteur
		int getVitesse();
		Point3D getPosition();
		int getPuissance();
		int getVirage();
		int getPoids();
		int getRayon();

		// Setteur
		void setVitesse(int vit);
		void setPosition(const Point3D pos);
		void setPosition(float x, float y, float z);
		void setPuissance(int pui);
		void setVirage(int vir);
		void setPoids(int poi);
		void setRayon(int ray);

		// Scanner : dans un rayon autour de lui il vérfie s'il y a l'autre objet passé en paramètre
		bool ScannerVoiture(Voiture voitureAScanner);
		bool ScannerBonus(Bonus bonusAScanner);
};