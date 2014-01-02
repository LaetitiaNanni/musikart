#pragma once

#include "voiture.hpp"

class BatterieVoiture: public Voiture{
	private:
		int nbBaguette;
	
	public:
		int getBaguette();
		void setBaguette(int bag);
};