#include "Item.hpp"
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <iostream>    /* cout */

#define NB_Item 3

// Constructeur
Item::Item(GLuint id, glm::vec3 _position) : position(_position), model(id,"../data/bloc_item.obj") {
  
  MVMatrix = glm::translate(glm::mat4(1),position);
  
  hitbox = new btBoxShape(btVector3(1.0,1.0,1.0));
  
  btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(position.x,position.y,position.z)));

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0,motionState,hitbox,btVector3(0,0,0));
  rigidBody = new btRigidBody(rigidBodyCI);
  
  rigidBody->setActivationState(DISABLE_DEACTIVATION);
  rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

////////////////////////////////////////////////////////////////////////////////
// Destructeur
Item::~Item(){

}
////////////////////////////////////////////////////////////////////////////////

void Item::Update() {
  // Récupération de la matrice de transformation.
  btTransform trans;
  rigidBody->getMotionState()->getWorldTransform(trans);
  
  MVMatrix = glm::rotate(glm::mat4(1), trans.getRotation().getAngle() * 180 / (float)M_PI, glm::vec3(trans.getRotation().getAxis().getX(), trans.getRotation().getAxis().getY(), trans.getRotation().getAxis().getZ()));
  
  MVMatrix = glm::rotate(MVMatrix,0.05f,glm::vec3(1.0,0.5,0.0));
  
  // On transmet la nouvelle matrice à Bullet.
  btTransform temp; 
  temp.setFromOpenGLMatrix(glm::value_ptr(MVMatrix));
  rigidBody->getMotionState()->setWorldTransform(temp);
  rigidBody->setMotionState(rigidBody->getMotionState());
  
  model.RenderModel();
}

// Récupérer la position
glm::vec3 Item::getPosition(){
	return position;
}

// Modifier la position
void Item::setPosition(const glm::vec3& pos){
	position = pos;
}

// génère un entier entre 1 et NB_Item (=3) (type de Item)
// /!\ cette fonction n'est pas définie dans la classe Item
int RandomType(){
	srand (time(NULL));
  	int randomType = rand() % NB_Item + 1;
  	return randomType;
}
