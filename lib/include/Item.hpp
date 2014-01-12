#pragma once

#include "string"

#include "AssimpModel.hpp"

#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "btBulletDynamicsCommon.h"

class Item{

public: 	
	// /!\ Appeler RandomType pour définir le type avant de construire le Item
	Item (GLuint id, glm::vec3 _position);

	~Item();
	
	void Update();
	
	btBoxShape* hitbox;
	btRigidBody* rigidBody;
	btDefaultMotionState myMotionState;

	// gestion position
	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);
	void setPosition(float x, float y, float z);

private:
	int type; // 1 = ralentisseur, 2 = accelerateur, 3 = stock d'armes
	glm::vec3 position;
	AssimpModel model;
	glm::mat4 MVMatrix;

};

int RandomType(); 
/*
Retourne un int random entre 1 et NB_Item, pour définir le type de Item
*/