#include "circuit.hpp"

// Constructeur
Circuit::Circuit(){

	std::cout << "pouet circuit" <<std::endl;

	// on crée zoneDeBonus
	this->zoneDeBonus = recupererPositionZoneDeBonus();

	// on crée tableauDeBonus
	std::vector<Point3D> zoneDeBonusDuCircuit = this->getZoneDeBonus();
	std::vector<Bonus> tabBonus = creerTableauBonus(zoneDeBonusDuCircuit);

	this->tableauDeBonus = tabBonus;

}

// Destructeur
Circuit::~Circuit(){
}



// Scanne l'état des bonus 
std::vector<int> Circuit::scannerEtatBonus(){

	std::cout << "scanneBonus" << std::endl;

	std::vector<int> idDeBooleenPris;

	for (int i = 0; i < tableauDeBonus.size() ; ++i){

		std::cout << tableauDeBonus[i].getEstPris() << std::endl;
		
		if (tableauDeBonus[i].getEstPris() == true){
			std::cout << "Le bonus " << i << "est manquant" << std::endl;		
			idDeBooleenPris.push_back(i);
		}
	}

	return idDeBooleenPris;
}



// Créer le vector zoneDeBonus
std::vector<Point3D> Circuit::recupererPositionZoneDeBonus(){

	std::vector<Point3D> zones;
	for (int i = 0; i < NB_ZONE_BONUS; ++i)
	{
		Point3D point = Point3D(i, i+1, i+2);
		zones.push_back(point);
//		std::cout << zones[i] << std::endl;
	}



	return zones;
}



// Créer le vector du script de parcours
std::vector<Point3D>  Circuit::recupererCoordonneesParcoursScript(){

}



// Récupérer le vector zoneDeBonus
std::vector<Point3D> Circuit::getZoneDeBonus(){
	return  this->zoneDeBonus;
}


std::vector<Bonus> Circuit::getTableauDeBonus(){
	return this->tableauDeBonus;
}



// Crée les Bonus manquants
void Circuit::creerBonusManquant(){

	std::vector<int> idDeBooleenPris = scannerEtatBonus();

	// on parcourt le tableau d'ID
	for (int i = 0; i < idDeBooleenPris.size(); ++i){
		std::cout << "Le bonus " << i << "est manquant" << std::endl;
		// on recrée un Bonus correspond à la case vide
		Point3D zoneManquante = zoneDeBonus[idDeBooleenPris[i]]	;

		Bonus nouveauBonus = Bonus(zoneManquante);
		tableauDeBonus[idDeBooleenPris[i]] = nouveauBonus;
	}

}
