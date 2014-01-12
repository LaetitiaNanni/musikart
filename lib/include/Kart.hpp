#pragma once

#include <string>
#include "AssimpModel.hpp"

#include "Item.hpp"
#include "Interface.hpp"

#include <GL/glew.h>

#include "btBulletDynamicsCommon.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Gearbox {
  Gearbox() {}
  Gearbox(const float& _maxValue, const float& _acceleration);
  float currentValue;
  short direction;
  bool isActive;
  
  float maxValue;
  float acceleration;
  
  void MoveUp();
  void MoveDown();
  void Update();
};

struct GPS {
  GPS() {}
  GPS(std::vector<glm::vec2>* _gps, unsigned int _nbLaps);
  
  std::vector<glm::vec2>* coords; // Coordonnées de la route.
  unsigned int currentDestination; // Etape courante.
  unsigned int nbLaps; // Nombre de tours dans la course.
};

class Kart {
	private:
		float range; // Rayon autour du kart dans lequel on pourra envoyer à un adversaire un bonus par exemple
		
		Gearbox speedBox; // Sert à contrôler la vitesse du kart avec plus de réalisme.
		Gearbox turnBox; // Sert à tourner de manière plus réaliste.
		
		GPS gps; // Faut bien savoir où on va...
		
		bool start;

	public:
		// Constructeurs
		Kart() {}
		Kart(GLuint id, const std::string& file, Texture* _vignette);
		
		AssimpModel model;
		glm::mat4 MVMatrix;
		btCollisionShape* hitbox;
		btRigidBody* rigidBody;
		btDefaultMotionState myMotionState;
		Texture* vignette;
		
		unsigned int rank;
		
		virtual void Update();
		virtual void Move() = 0;
		void UpdateMatrix();

		//Destructeur
		~Kart();
		
		void Start(bool state);
		bool isStarted();

		// Getteur
		Gearbox& getSpeedBox();
		Gearbox& getTurnBox();
		float getRange();
		GPS& getGPS();

		// Setteur
		void setRange(float ray);
		void setGPS(std::vector<glm::vec2>* _coords, unsigned int _nbLaps);
		void setGPS(GPS _gps);
};