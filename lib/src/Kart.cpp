#include "Kart.hpp"

Gearbox::Gearbox(const float& _maxValue, const float& _acceleration) :
maxValue(_maxValue), acceleration(_acceleration)
{
  maxValue = _maxValue;
  acceleration = _acceleration;
  
  currentValue = 0;
  direction = 0;
  isActive = false;
}

void Gearbox::MoveUp() {
	if(direction == 1 && currentValue > 0) {
	  currentValue -= acceleration*3;
	} else {
	  if(currentValue < 0) currentValue = 0;
	  else if(currentValue < maxValue) currentValue += acceleration;
	  direction = -1;
	}
	isActive = true;
}

void Gearbox::MoveDown() {
	if(direction == -1 && currentValue > 0) {
	  currentValue -= acceleration*3;
	} else {
	  if(currentValue < 0) currentValue = 0;
	  else if(currentValue < maxValue) currentValue += acceleration;
	  direction = 1;
	}
	isActive = true;
}

void Gearbox::Update() {
  if(currentValue > maxValue) currentValue -= acceleration;
  if(!isActive) {
	currentValue -= acceleration;
	if(currentValue <= 0) currentValue = 0;
  }
  isActive = false;
}

GPS::GPS(std::vector<glm::vec2>* _coords, unsigned int _nbLaps) {
  coords = _coords;
  nbLaps = _nbLaps;
  currentDestination = 0;
}

///////////////////
// Constructeurs
///////////////////
Kart::Kart(GLuint id, const std::string& file, Texture* _vignette) :
model(id,file), vignette(_vignette)
{
	float speed;
	glm::vec3 pos;
	float acc;
	float turn;
	float weight;

	if(file == "../data/sid.obj") {
	  speed = 0.45;
	  pos = glm::vec3(0,0,0);
	  acc = 0.005;
	  turn = 2.5;
	  weight = 5;
	  range = 10;
	  hitbox = new btBoxShape(btVector3(1,1.35,2.25));
	} else if(file == "../data/franky.obj") {
	  speed = 0.36;
	  pos = glm::vec3(5,0,0);
	  acc = 0.025;
	  turn = 3.5;
	  weight = 10;
	  range = 10;
	  hitbox = new btBoxShape(btVector3(1.5,1.70,1.75));
	} else if(file == "../data/mike.obj") {
	  speed = 0.4;
	  pos = glm::vec3(5,0,5);
	  acc = 0.01;
	  turn = 3;
	  weight = 8;
	  range = 10;
	  hitbox = new btBoxShape(btVector3(0.8,1.18,1.8));
	} else {
	  speed = 0.38;
	  pos = glm::vec3(0,0,5);
	  acc = 0.015;
	  turn = 4;
	  weight = 6;
	  range = 10;
	  hitbox = new btBoxShape(btVector3(1.05,1.15,2.5));
	}
	
	speedBox = Gearbox(speed, acc);
	turnBox = Gearbox(turn, turn / 15.0f);
	
	MVMatrix = glm::translate(glm::mat4(1), pos);
	
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(pos.x,pos.y,pos.z)));
	btScalar mass = weight;
	btVector3 fallInertia(0,0,0);
	hitbox->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,hitbox,fallInertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
	rigidBody->setAngularFactor(btVector3(0,1,0));
	
	start = false;
	rank = 0;
}

/*Kart::Kart(const Kart& other) :
model(other.model), vitesse(other.vitesse), position(other.position), puissance(other.puissance), virage(other.virage),poids(other.poids), rayon(other.rayon)
{}*/


//Destructeur
Kart::~Kart() {
	delete rigidBody->getMotionState();
	delete rigidBody;
	
	delete hitbox;
}

/* Méthodes */
void Kart::Update() {
  // Récupération de la matrice de transformation.
  btTransform trans;
  rigidBody->getMotionState()->getWorldTransform(trans);
  
  // On replace le kart là où il était.
  MVMatrix = glm::translate(glm::mat4(1), glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
  if(isStarted()) MVMatrix = glm::rotate(MVMatrix, trans.getRotation().getAngle() * 180 / (float)M_PI, glm::vec3(trans.getRotation().getAxis().getX(), trans.getRotation().getAxis().getY(), trans.getRotation().getAxis().getZ()));
  
  // On déplace le kart avec les nouvelles coordonnées.
  MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, speedBox.direction * speedBox.currentValue));
  MVMatrix = glm::rotate(MVMatrix, turnBox.direction * turnBox.currentValue, glm::vec3(0.0f, 1.0f, 0.0f));
  
  // On transmet la nouvelle matrice à Bullet.
  UpdateMatrix();
  
  model.RenderModel();
}

void Kart::UpdateMatrix() {
  btTransform temp; 
  temp.setFromOpenGLMatrix(glm::value_ptr(MVMatrix));
  rigidBody->getMotionState()->setWorldTransform(temp);
  rigidBody->setMotionState(rigidBody->getMotionState());
}

void Kart::Start(bool state) {
  start = state;
}

bool Kart::isStarted() {
  return start;
}

///////////////////
// Getteurs
///////////////////
Gearbox& Kart::getSpeedBox() {
  return speedBox;
}
Gearbox& Kart::getTurnBox() {
  return turnBox;
}
float Kart::getRange(){
	return range;
}
GPS& Kart::getGPS() {
  return gps;
}


///////////////////
// Setteurs
///////////////////
void Kart::setRange(float ray){
	range = ray;
}

void Kart::setGPS(std::vector<glm::vec2>* _gps, unsigned int _nbLaps) {
  gps.coords = _gps;
  gps.nbLaps = _nbLaps;
  gps.currentDestination = 0;
}