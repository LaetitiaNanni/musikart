#pragma once

#include <string>
#include <vector>
#include <map>
#include "AssimpModel.hpp"
#include "Kart.hpp"
#include "Environment.hpp"

#include <GL/glew.h>

#include "btBulletDynamicsCommon.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Circuit {
	private:
		std::vector<Kart*>* karts;
		std::vector<glm::vec2>* gps; // Chemin prédéfini pour les ennemis
		unsigned int nbLaps;
		AssimpModel model;
		AssimpModel skybox;
		unsigned int finalRank;
		
	public:
		// Constructeurs
		Circuit(GLuint id, const std::string& file, std::vector<Kart*>* k, unsigned int _nbLaps, const std::string& skyboxFile, glm::vec3 position, std::vector<glm::vec2>* gps);
		//Destructeur
		~Circuit();
		
		glm::mat4 MVMatrix;
		btBvhTriangleMeshShape* hitbox;
		btRigidBody* rigidBody;
		std::vector<unsigned int> rank;
		
		void Update();
		void Rank();
		
		std::vector<glm::vec2>* getGPS();
		unsigned int getNbLaps();
};