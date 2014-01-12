#include "Circuit.hpp"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

Circuit::Circuit(GLuint id, const std::string& file, std::vector<Kart*>* k, unsigned int _nbLaps, const std::string& skyboxFile, glm::vec3 position, std::vector<glm::vec2>* _gps) : model(id,file), nbLaps(_nbLaps), skybox(id,skyboxFile), gps(_gps)
{	
	karts = k;
	MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	
	std::vector<glm::vec3> vertices;
	
	std::vector<unsigned int> indices;
	for(unsigned int i = 0; i < model.vertices.size(); ++i) {
	  vertices.push_back(glm::vec3(model.vertices[i].position.x,model.vertices[i].position.y,model.vertices[i].position.z));
	  indices.push_back(i);
	}
	
	btTriangleIndexVertexArray* va = new btTriangleIndexVertexArray(indices.size()/3,
			(int*) &(indices)[0],
			sizeof(unsigned int)*3,
			vertices.size(),(btScalar*) &(vertices)[0],sizeof(glm::vec3));
	
	hitbox = new btBvhTriangleMeshShape(va, true);
	
	//hitbox = new btStaticPlaneShape(btVector3(0,1,0),0);
  
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0,motionState,hitbox,btVector3(0,0,0));
	rigidBody = new btRigidBody(rigidBodyCI);
	
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
	
	for(unsigned int i = 0; i < karts->size(); ++i) {
	  (*karts)[i]->MVMatrix = glm::translate((*karts)[i]->MVMatrix,position);
	  (*karts)[i]->UpdateMatrix();
	  rank.push_back(i);
	}
	
	finalRank = 0;
}

//Destructeur
Circuit::~Circuit() {
	delete rigidBody->getMotionState();
	delete rigidBody;
	
	delete hitbox;
}

void Circuit::Update() {
  Rank();
  
  model.RenderModel();
  skybox.RenderModel();
}

void Circuit::Rank() {
  unsigned int indice,maxPosition = 0,currentRank = 1;
  
  std::multimap<unsigned int,unsigned int> position;
  
  for (unsigned int i = 0; i < karts->size(); ++i) {
	indice = (*karts)[i]->getGPS().currentDestination + ((nbLaps+1) - (*karts)[i]->getGPS().nbLaps) * (*karts)[i]->getGPS().coords->size();
	if(indice == (nbLaps+1) * (*karts)[i]->getGPS().coords->size() && (*karts)[i]->rank == 0) (*karts)[i]->rank = ++finalRank;
	position.insert ( std::pair<unsigned int,unsigned int>(indice,i) );
  }
  
  std::multimap<unsigned int,unsigned int>::reverse_iterator rit;
  for (rit=position.rbegin(); rit!=position.rend(); ++rit) {
	rank[rit->second] = currentRank++;
  }
  
  position.clear();
}

std::vector<glm::vec2>* Circuit::getGPS() {
  return gps;
}

unsigned int Circuit::getNbLaps() {
  return nbLaps;
}