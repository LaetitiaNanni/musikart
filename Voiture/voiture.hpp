#pragma once

#include "../lib/include/Point3D.hpp"

class Voiture {
	private:
		int vitesse;
		Point3D position;
		int puissance;
		int virage;
		int poids;
	public:
		// Constructeurs
		Voiture(int vitesse, Point3D position, int puissance, int virage, int poids);
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

		// Setteur
		void setVitesse(int vit);
		void setPosition(Point3D pos);
		void setPosition(int x, int y, int z);
		void setPuissance(int pui);
		void setVirage(int vir);
		void setPoids(int poi);

		// Scanner : dans un rayon autour de lui il vérfie s'il y a l'autre objet passé en paramètre
};