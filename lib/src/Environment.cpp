#include "Environment.hpp"

Environment::Environment(glm::vec3 _position, glm::vec2 _dimensions, TriggerCallback* tcb) : position(_position), dimensions(_dimensions), callback(tcb)
{
	MVMatrix = glm::translate(glm::mat4(1), position);
	
	hitbox = new btBoxShape(btVector3(dimensions.x,3,dimensions.y));
	
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(position.x,position.y,position.z)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0,motionState,hitbox,btVector3(0,0,0));
	rigidBody = new btRigidBody(rigidBodyCI);
	
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

glm::vec3 Environment::getPosition() {
  return position;
}

glm::vec2 Environment::getDimensions() {
  return dimensions;
}

void Environment::setPosition(glm::vec3 _position) {
  position = _position;
}

void Environment::setDimensions(glm::vec2 _dimensions) {
  dimensions = _dimensions;
}