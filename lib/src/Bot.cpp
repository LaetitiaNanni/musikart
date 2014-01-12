#include "Bot.hpp"

void Bot::Update() {
  if(isStarted()) Move();
  Kart::Update();
  getSpeedBox().Update();
  getTurnBox().Update();
}

void Bot::Move() {
  if(getGPS().nbLaps > 0) {
	  glm::vec2 current = (*getGPS().coords)[getGPS().currentDestination];

	  btTransform trans;
	  rigidBody->getMotionState()->getWorldTransform(trans);
	  glm::vec2 pos(trans.getOrigin().getX(),trans.getOrigin().getZ());
	  glm::quat rot(trans.getRotation().getX(),trans.getRotation().getY(),trans.getRotation().getZ(),trans.getRotation().getW());
	  float orientation = trans.getRotation().getAngle() * 180.0f / (float) M_PI;
	  
	  float distance = glm::distance(current, pos);
	  glm::vec2 posToDest = current - pos;
	  glm::vec3 posToWorld = glm::rotate(rot, glm::normalize(glm::vec3(0,0,-1)));
	  float angle = glm::orientedAngle(glm::normalize(posToDest),glm::normalize(glm::vec2(posToWorld.x,posToWorld.z)));
	   
	  if(distance < 7.0f) {
		++(getGPS().currentDestination);
		if(getGPS().currentDestination == getGPS().coords->size()) {
		  getGPS().currentDestination = 0;
		  --(getGPS().nbLaps);
		}
	  } else {
		  if(angle > distance || angle < -distance) {
			if(angle > distance) getTurnBox().MoveDown();
			else getTurnBox().MoveUp();

		  } getSpeedBox().MoveUp();
	  }
	  
  } else {
	// Défaite
  }
}

// getteur
/*Voiture Bot::getVoiture(){
	return voiture;
}
*/
// setteur
/*void Bot::setKart(Kart* k){
	kart=k;
}*/