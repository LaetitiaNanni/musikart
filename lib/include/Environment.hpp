#pragma once

#include "Kart.hpp"
#include <vector>

#include "btBulletDynamicsCommon.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class TriggerCallback : public btCollisionWorld::ContactResultCallback {
	public :
	  std::vector<Kart*>* karts;
	  unsigned int index;
	  
	  TriggerCallback(std::vector<Kart*>* k) : karts(k), index(0), btCollisionWorld::ContactResultCallback() {}

	  virtual bool needsCollision(btBroadphaseProxy* proxy) const {
		  if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
			  return false;
		  return false;
	  }

	  virtual btScalar addSingleResult(btManifoldPoint& cp,
		  const btCollisionObjectWrapper* colObj0,int partId0,int index0,
		  const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	  {
		  return 0;
	  }
};

class TriggerAcceleratorCallback : public TriggerCallback {
  public :
	TriggerAcceleratorCallback(std::vector<Kart*>* k) : TriggerCallback(k) {}

	virtual btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObj0,int partId0,int index0,
		const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	{
		(*karts)[index]->getSpeedBox().currentValue += 0.05;
		if((*karts)[index]->getSpeedBox().currentValue > 0.7f) (*karts)[index]->getSpeedBox().currentValue = 0.7;
		return 0;
	}
};

class TriggerDeceleratorCallback : public TriggerCallback {
  public :
	TriggerDeceleratorCallback(std::vector<Kart*>* k) : TriggerCallback(k) {}

	virtual btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObj0,int partId0,int index0,
		const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	{
		if((*karts)[index]->getSpeedBox().currentValue > 0.2f) (*karts)[index]->getSpeedBox().currentValue -= (*karts)[index]->getSpeedBox().acceleration;
		return 0;
	}
};

class Environment {
	private :
	  glm::vec3 position;
	  glm::vec2 dimensions;

	public :
	  Environment(glm::vec3 _position, glm::vec2 _dimensions, TriggerCallback* tcb);
	  
	  glm::mat4 MVMatrix;
	  btCollisionShape* hitbox;
	  btRigidBody* rigidBody;
	  btDefaultMotionState myMotionState;
	  TriggerCallback* callback;
	  
	  glm::vec3 getPosition();
	  glm::vec2 getDimensions();
	  
	  void setPosition(glm::vec3 _position);
	  void setDimensions(glm::vec2 _dimensions);
};