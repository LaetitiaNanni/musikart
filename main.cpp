#include "Circuit/circuit.hpp"
#include "Bonus/bonus.hpp"
#include "Fichier/fichier.hpp"
#include "Voiture/voiture.hpp"
#include "Voiture/microVoiture.hpp"
#include "Voiture/basseVoiture.hpp"
#include "Voiture/guitareVoiture.hpp"
#include "Voiture/batterieVoiture.hpp"

#include "VBO.hpp"
#include "VAO.hpp"
#include "Program.hpp"
#include "Freefly.hpp"
#include "Sphere.hpp"

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;


int main(int argc, char const *argv[]) {


	/****************** Initialisation SDL ************************/
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Unable to initialize SDL" << std::endl;
		return EXIT_FAILURE;
	}

	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_OPENGL)) {
		std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_WM_SetCaption("OpenGL4Imacs", NULL);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
	}

	/******************* Initialisation de nos objets ************************/

	//////////////// TEST ///////////////////

/*	glimac::Sphere sphere(1, 32, 16);


	// VBO
	glimac::VBO vbo;
	vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(glimac::ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW); //envoi des données à la CG
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Débind du VBO

	// VAO
	glimac::VAO vao;	// Création du vao	
	vao.bind();	// Binding du vao
	// Activation des attributs de vertex
	glEnableVertexAttribArray(0); // 0 car c'est le premier (indice 0)
	// Spécification du format des attributs de vertex
	glBindBuffer(GL_ARRAY_BUFFER, vbo.getGLId()); // on rebind le vbo
	
	// Coordonnées
	glVertexAttribPointer(
		0, // index: indice
		3, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,position)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, // index: indice
		3, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,normal)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2, // index: indice
		2, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,texCoords)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);


	glBindBuffer(GL_ARRAY_BUFFER, 0); // Débind du VBO
	glBindVertexArray(0); // debind du vao
*/

	// import du lit
	const aiScene* scene;
	const std::string refString = "../Model3D/Chair.dae";
	
	std::vector<glimac::ShapeVertex> vecteurDeVertex;
	vecteurDeVertex = DoTheImportThing(refString);


	// VBO
	glimac::VBO vbo;
	vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, vecteurDeVertex.size()*sizeof(glimac::ShapeVertex), &vecteurDeVertex[0], GL_STATIC_DRAW); //envoi des données à la CG
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Débind du VBO

	//VAO
	glimac::VAO vao;	// Création du vao	
	vao.bind();	// Binding du vao
	// Activation des attributs de vertex
	glEnableVertexAttribArray(0); // 0 car c'est le premier (indice 0)
	// Spécification du format des attributs de vertex
	glBindBuffer(GL_ARRAY_BUFFER, vbo.getGLId()); // on rebind le vbo
	
	// Coordonnées
	glVertexAttribPointer(
		0, // index: indice
		3, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,position)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);
	
	glEnableVertexAttribArray(1);
	
	// normales
	glVertexAttribPointer(
		1, // index: indice
		3, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,normal)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);

	glEnableVertexAttribArray(2);
	
	// coordonnées de textures
	glVertexAttribPointer(
		2, // index: indice
		2, // size : nombre de variables composant notre attribut
		GL_FLOAT, // type: type de nos variables
		GL_FALSE, // normalized : attributs normalisés (ramené entre 0 et 1) ou non
		sizeof(glimac::ShapeVertex), // stride : nb d'octets pour aller à la prochaine occurence de l'attribut
		(const GLvoid*) (offsetof(glimac::ShapeVertex,texCoords)) // pointer : offset (décalage) en octets de la première occurence de l'attribut dans le VBO
	);


	glBindBuffer(GL_ARRAY_BUFFER, 0); // Débind du VBO
	glBindVertexArray(0); // debind du vao


	// on charge les fichiers de shader
	glimac::Program shaderProgram;
	shaderProgram = glimac::loadProgram("../shaders/3D.vs.glsl","../shaders/normals.fs.glsl");
	shaderProgram.use();
	
	
	GLint uMVPMatrixLocation = glGetUniformLocation(shaderProgram.getGLId(), "uMVPMatrix");
	GLint uMVMatrixLocation = glGetUniformLocation(shaderProgram.getGLId(), "uMVMatrix");
	GLint uNormalMatrixLocation = glGetUniformLocation(shaderProgram.getGLId(), "uNormalMatrix");
	GLint uTextureLocation = glGetUniformLocation(shaderProgram.getGLId(), "uTexture");



	glEnable(GL_DEPTH_TEST); 


	glm::mat4 ProjMatrix, MVMatrix, ViewMatrix;

	ProjMatrix = glm::perspective(70.f, (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f);


	glimac::FreeflyCamera camera;
    int mouseLastX, mouseLastY;

	//////////////// FIN TEST ///////////////////



	/********************* boucle de rendu *************************/
	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();

		/******************Rendering code goes here***************************/
		
		// Nettoyage de la fenêtre
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	/*	ViewMatrix = camera.getViewMatrix();

		MVMatrix = glm::translate(ViewMatrix, glm::vec3(0.f,0.f,-15.f));
		MVMatrix = glm::rotate(MVMatrix, tStart * 0.05f, glm::vec3(0, 1, 0));

//		glBindTexture(GL_TEXTURE_2D, textures[0]);

		// Rendering code goes here
		glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
		glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(glm::transpose(MVMatrix))));
		glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniform1i(uTextureLocation, 0);

		vao.bind();

		glDrawArrays(
			GL_TRIANGLES, // mode
			0, // first : indice du premier sommet à dessiner (on n'est pas obligé de tout dessiner)
			sphere.getVertexCount() // count : combien de sommets à dessiner
		);


		glBindVertexArray(0); // debind du vao
*/



		ViewMatrix = camera.getViewMatrix();

		MVMatrix = glm::translate(ViewMatrix, glm::vec3(0.f,0.f,-50.f));
		MVMatrix = glm::rotate(MVMatrix, tStart * 0.05f, glm::vec3(0, 1, 0));
	


		//Bind de la texture
//		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
		glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(glm::transpose(MVMatrix))));
		glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniform1i(uTextureLocation, 0);


		// Bind du VAO
		vao.bind();

		// Dessin 
		glDrawArrays(
			GL_TRIANGLES, // mode
			0, // first : indice du premier sommet à dessiner (on n'est pas obligé de tout dessiner)
			vecteurDeVertex.size() // count : combien de sommets à dessiner
		);

//		glBindTexture(GL_TEXTURE_2D, 0); // debind de la texture
		glBindVertexArray(0); // debind du vao


		// Application code goes here




		// Gestion des évènements
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				default:
					break;
				case SDL_QUIT:
					done = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_RIGHT) {
                        mouseLastX = e.button.x;
                        mouseLastY = e.button.y;
                    }
			}
		}

		int mouseX, mouseY;
        if(SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            int dX = mouseX - mouseLastX, dY = mouseY - mouseLastY;
            camera.rotateLeft(-dX);
            camera.rotateUp(-dY);
            mouseLastX = mouseX;
            mouseLastY = mouseY;
        }

        if(SDL_GetKeyState(0)[SDLK_z]) {
            camera.moveFront(0.1);
        }

        if(SDL_GetKeyState(0)[SDLK_s]) {
            camera.moveFront(-0.1);
        }

        if(SDL_GetKeyState(0)[SDLK_q]) {
            camera.moveLeft(0.1);
        }

        if(SDL_GetKeyState(0)[SDLK_d]) {
            camera.moveLeft(-0.1);
        }


		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		SDL_GL_SwapBuffers();

		Uint32 tEnd = SDL_GetTicks();
		Uint32 d = tEnd - tStart;
		if(d < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - d);
		}
	}

//	glDeleteTextures(1, textures);
	SDL_Quit();

	


/*	int type = RandomType();
	Bonus ab = Bonus (1, -100.3, type);
	std::cout << ab.getType() << std::endl;
	
	std::cout << ab.getX() << std::endl;
	std::cout << ab.getY() << std::endl;
*/
	return EXIT_SUCCESS;
}
