#include "Player.hpp"
#include <cmath>

// constructeurs
/*Player::Player(GLuint GLId, const std::string& file)
{
  Kart(GLId, file);
}*/

void Player::Update() {
  if(isStarted() && rank == 0) Move();
  
  Kart::Update();
  
  if(getGPS().nbLaps > 0) {
	  glm::vec2 current = (*getGPS().coords)[getGPS().currentDestination];

	  btTransform trans;
	  rigidBody->getMotionState()->getWorldTransform(trans);
	  
	  glm::vec2 pos(trans.getOrigin().getX(),trans.getOrigin().getZ());
	  float distance = glm::distance(current, pos);
	  
	  if(distance < 10.0f) {
		++(getGPS().currentDestination);
		if(getGPS().currentDestination == getGPS().coords->size()) {
		  getGPS().currentDestination = 0;
		  --(getGPS().nbLaps);
		}
	  } 
  }
  
  getSpeedBox().Update();
  getTurnBox().Update();
}

void Player::Move() {
	  
  if(keystate[SDLK_z] || keystate[SDLK_UP]) {
	  getSpeedBox().MoveUp();
  } else if(keystate[SDLK_s] || keystate[SDLK_DOWN]) {
	  getSpeedBox().MoveDown();
  } 
  
  if(keystate[SDLK_q] || keystate[SDLK_LEFT]) {
	  getTurnBox().MoveDown();
  } else if(keystate[SDLK_d] || keystate[SDLK_RIGHT]) {
	  getTurnBox().MoveUp();
  }
}

// getteur
/*Voiture Player::getVoiture(){
	return voiture;
}
*/
// setteur
/*void Player::setKart(Kart* k){
	kart=k;
}*/