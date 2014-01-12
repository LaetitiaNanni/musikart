#include "Menu.hpp"
#include "Interface.hpp"
#include "Circuit.hpp"
#include "Item.hpp"
#include "AssimpModel.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "Environment.hpp"

#include "TrackballCamera.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Program.hpp"
#include "Matrix.hpp"
#include "GLDebugDrawer.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "btBulletDynamicsCommon.h"

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;

int main(int argc, char const *argv[]) {
  Menu mainMenu;
		mainMenu.menu();

	/****************** Initialisation SDL ************************/
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Unable to initialize SDL" << std::endl;
		return EXIT_FAILURE;
	}
	 
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_OPENGL)){
		std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_WM_SetCaption("Musikart", NULL);
	
	TTF_Init();

	if(TTF_Init() == -1){
		printf("Unable to initialize TTF_Init : \n");
	}

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
	}
	
	/******************* Initialisation de nos objets ************************/

	/******************* INTERFACE *********************/
	
	Interface iface;
		// Chargement des polices 
		TTF_Font* font_small = TTF_OpenFont("../font/Sansation_Bold.ttf", 30);
		if (font_small == NULL){
			printf ("Erreur : police non trouvée \n");
		}
		TTF_Font* font_big = TTF_OpenFont("../font/Sansation_Bold.ttf", 100);
		if (font_big == NULL){
			printf ("Erreur : police non trouvée \n");
		}
		
		
        // Classement
        std::string sid = "../images/sid.jpg";
        std::string cherry = "../images/cherry.jpg";
        std::string franky = "../images/franky.jpg";
        std::string mike = "../images/mike.jpg";
		
		iface.AddTexture(sid,glm::vec2(10.f,50.f),true);
		iface.AddTexture(cherry,glm::vec2(10.f,180.f),true);
		iface.AddTexture(franky,glm::vec2(10.f,310.f),true);
		iface.AddTexture(mike,glm::vec2(10.f,440.f),true);
		iface.AddText("4th",glm::vec2(5.f,125.f),true,font_small);
		iface.AddText("3rd",glm::vec2(5.f,255.f),true,font_small);
		iface.AddText("2nd",glm::vec2(5.f,385.f),true,font_small);
		iface.AddText("1st",glm::vec2(5.f,515.f),true,font_small);
		iface.AddText("3",glm::vec2(WINDOW_WIDTH*0.5-20,WINDOW_HEIGHT*0.5-10),false,font_big);
		iface.AddText("2",glm::vec2(WINDOW_WIDTH*0.5-20,WINDOW_HEIGHT*0.5-10),false,font_big);
		iface.AddText("1",glm::vec2(WINDOW_WIDTH*0.5-20,WINDOW_HEIGHT*0.5-10),false,font_big);
		iface.AddText("GO!",glm::vec2(WINDOW_WIDTH*0.5-70,WINDOW_HEIGHT*0.5-10),false,font_big);
		iface.AddText("YOU WON!",glm::vec2(WINDOW_WIDTH*0.5-150,WINDOW_HEIGHT*0.5-10),false,font_big);
		iface.AddText("You lose...",glm::vec2(WINDOW_WIDTH*0.5-200,WINDOW_HEIGHT*0.5-10),false,font_big);
		
		 // Bonus
        /*std::string bonusAvancer = "../images/avancer_bonus.jpg";
        std::string bonusReculer = "../images/reculer_bonus.jpg";
        std::string bonusArme = "../images/bonus_arme.jpg";
        std::string bonusVide = "../images/bonus_vide.jpg";
		
		iface.AddTexture(bonusAvancer,glm::vec2((WINDOW_WIDTH - 80) - 20.0f,10.f),false);
		iface.AddTexture(bonusReculer,glm::vec2((WINDOW_WIDTH - 80) - 20.0f,10.f),false);
		iface.AddTexture(bonusArme,glm::vec2((WINDOW_WIDTH - 80) - 20.0f,10.f),false);
		iface.AddTexture(bonusVide,glm::vec2((WINDOW_WIDTH - 80) - 20.0f,10.f),true);*/
		
		TTF_CloseFont(font_small);
		TTF_CloseFont(font_big);
		
	// on charge les fichiers de shader
	glimac::Program shaderProgram;
	shaderProgram = glimac::loadProgram("../shaders/3D.vs.glsl","../shaders/3D.fs.glsl");
	shaderProgram.use();
	
	// Création des personnages
	const std::string sidURL = "../data/sid.obj";
	const std::string frankyURL = "../data/franky.obj";
	const std::string mikeURL = "../data/mike.obj";
	const std::string cherryURL = "../data/cherry.obj";
	
	Player* player;
	
	Bot* bot1;
	Bot* bot2;
	Bot* bot3;
	
	if(mainMenu.numeroKart == 1) {		
		bot1 = new Bot(shaderProgram.getGLId(),sidURL,iface.getTexture(sid));
		bot2 = new Bot(shaderProgram.getGLId(),mikeURL,iface.getTexture(mike));
		player = new Player(shaderProgram.getGLId(),cherryURL,iface.getTexture(cherry));
		bot3 = new Bot(shaderProgram.getGLId(),frankyURL,iface.getTexture(franky));
		
	} else if(mainMenu.numeroKart == 2) {
		player = new Player(shaderProgram.getGLId(),sidURL,iface.getTexture(sid));
		
		bot1 = new Bot(shaderProgram.getGLId(),mikeURL,iface.getTexture(mike));
		bot2 = new Bot(shaderProgram.getGLId(),cherryURL,iface.getTexture(cherry));
		bot3 = new Bot(shaderProgram.getGLId(),frankyURL,iface.getTexture(franky));
	  
	} else if(mainMenu.numeroKart == 3) {
		bot1 = new Bot(shaderProgram.getGLId(),sidURL,iface.getTexture(sid));
		bot2 = new Bot(shaderProgram.getGLId(),cherryURL,iface.getTexture(cherry));
		bot3 = new Bot(shaderProgram.getGLId(),mikeURL,iface.getTexture(mike));
		player = new Player(shaderProgram.getGLId(),frankyURL,iface.getTexture(franky));

	} else if(mainMenu.numeroKart == 4) {
		bot1 = new Bot(shaderProgram.getGLId(),sidURL,iface.getTexture(sid));
		bot2 = new Bot(shaderProgram.getGLId(),cherryURL,iface.getTexture(cherry));
		player = new Player(shaderProgram.getGLId(),mikeURL,iface.getTexture(mike));
		bot3 = new Bot(shaderProgram.getGLId(),frankyURL,iface.getTexture(franky));
	  
	}
	
	TrackballCamera camera(player);
	
	
	// Création du circuit
	std::vector<Kart*> karts;
	karts.push_back(player);
	karts.push_back(bot1);
	karts.push_back(bot2);
	karts.push_back(bot3);
	
	std::vector<glm::vec2> gps;
	std::vector<Environment*> environments;
	
	std::string mapURL;
	std::string skyboxURL;
	
	 TriggerAcceleratorCallback tac(&karts);
	 TriggerDeceleratorCallback tdc(&karts);
	 Environment* acc1;
	 Environment* dec1;
	 Environment* dec2;
	 
	 glm::vec3 positionKarts;
	
	if(mainMenu.numeroCircuit == 1) {
	  
	  mapURL.append("../data/circuit1.obj");
	  skyboxURL.append("../data/skybox.obj");
	  
	  positionKarts = glm::vec3(38,-5,25);
	  
	  gps.push_back(glm::vec2(39.5,10.5));
	  gps.push_back(glm::vec2(28,3));
	  gps.push_back(glm::vec2(42,-12.5));
	  gps.push_back(glm::vec2(40,-34));
	  gps.push_back(glm::vec2(32,-44));
	  gps.push_back(glm::vec2(17,-42));
	  gps.push_back(glm::vec2(9,-24.5));
	  gps.push_back(glm::vec2(2,0.5));
	  gps.push_back(glm::vec2(-2,23));
	  gps.push_back(glm::vec2(-17,20));
	  gps.push_back(glm::vec2(-21,2.5));
	  gps.push_back(glm::vec2(-19,-20));
	  gps.push_back(glm::vec2(-7,-31.5));
	  gps.push_back(glm::vec2(-10.5,-46));
	  gps.push_back(glm::vec2(-25.5,-44.5));
	  gps.push_back(glm::vec2(-43,-37.5));
	  gps.push_back(glm::vec2(-44.5,-20));
	  gps.push_back(glm::vec2(-43.5,20));
	  gps.push_back(glm::vec2(-41.5,43));
	  gps.push_back(glm::vec2(-17,46));
	  gps.push_back(glm::vec2(-8,45));
	  gps.push_back(glm::vec2(9,44.5));
	  gps.push_back(glm::vec2(30.5,41.5));
	  gps.push_back(glm::vec2(40,30.5));
	  gps.push_back(glm::vec2(41,10));
	  
	  acc1 = new Environment(glm::vec3(-44.5,-8,-7),glm::vec2(2.0,23.5),&tac);
	  dec1 = new Environment(glm::vec3(-20,-7,32),glm::vec2(18,8),&tdc);
	  dec2 = new Environment(glm::vec3(6,-5,-14),glm::vec2(7.5,20),&tdc);
	  
	  environments.push_back(acc1);
	  environments.push_back(dec1);
	  environments.push_back(dec2);
	} 
	else if(mainMenu.numeroCircuit == 2) {
	  
	  mapURL.append("../data/circuit2.obj");
	  skyboxURL.append("../data/skybox2.obj");
	  
	  positionKarts = glm::vec3(-67,-47,-11.2);
	  
	  gps.push_back(glm::vec2(-69,-15));
	  gps.push_back(glm::vec2(-63,-31));
	  gps.push_back(glm::vec2(-48.2,-44.2));
	  gps.push_back(glm::vec2(-30.7,-35.5));
	  gps.push_back(glm::vec2(-9.5,-36));
	  gps.push_back(glm::vec2(4,-28));
	  gps.push_back(glm::vec2(25.5,-15.6));
	  gps.push_back(glm::vec2(48.8,-19.7));
	  gps.push_back(glm::vec2(65.7,-18.9));
	  gps.push_back(glm::vec2(74.8,-6.7));
	  gps.push_back(glm::vec2(68.5,6.5));
	  gps.push_back(glm::vec2(48.8,5));
	  gps.push_back(glm::vec2(9.7,-0.3));
	  gps.push_back(glm::vec2(-0.7,16.5));
	  gps.push_back(glm::vec2(-23,16));
	  gps.push_back(glm::vec2(-35.5,24));
	  gps.push_back(glm::vec2(-52.8,23));
	  
	  acc1 = new Environment(glm::vec3(27,-49,2),glm::vec2(13.5,2),&tac);
	  dec1 = new Environment(glm::vec3(-40.7,-49,-41.1),glm::vec2(9,5.5),&tdc);
	  dec2 = new Environment(glm::vec3(30,-49,-20),glm::vec2(13.5,3),&tdc);
	  
	  environments.push_back(acc1);
	  environments.push_back(dec1);
	  environments.push_back(dec2);
	}
	
	Circuit map(shaderProgram.getGLId(), mapURL, &karts, 3, skyboxURL, positionKarts, &gps);
	
	for(unsigned int j = 0; j < karts.size(); ++j)
	{
	  karts[j]->setGPS(map.getGPS(),map.getNbLaps());
	}
	
	/*Item item(shaderProgram.getGLId(),glm::vec3(-30,-3,20));
	
	std::vector<Item*> items;
	items.push_back(&item);*/
	
	struct Matrix m(shaderProgram.getGLId(), WINDOW_WIDTH, WINDOW_HEIGHT);
	
	glEnable(GL_DEPTH_TEST);

    int x, y;
	
	// Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // The world.
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
	
    // Do_everything_else_here
	dynamicsWorld->addRigidBody(map.rigidBody);
	for(unsigned int i = 0; i < karts.size(); ++i)
	{
	  dynamicsWorld->addRigidBody(karts[i]->rigidBody);
	}
	
	for(unsigned int j = 0; j < environments.size(); ++j)
	{
	  dynamicsWorld->addRigidBody(environments[j]->rigidBody);
	}
	
	/*for(unsigned int k = 0; k < items.size(); ++k)
	{
	  dynamicsWorld->addRigidBody(items[k]->rigidBody);
	}*/
	
	// Debugger
	/*GLDebugDrawer debugDrawer;
	dynamicsWorld->setDebugDrawer(&debugDrawer);
	dynamicsWorld->getDebugDrawer()->setDebugMode(0);*/ // BUG à 1 faisant crasher le jeu (nombre de vertices à calculer trop élevé à cause de la map).
	
	SDL_EnableKeyRepeat(FRAME_DURATION/2, FRAME_DURATION/2);
	
	int framesBeforeStart = 6*FPS;
	/********************* boucle de rendu *************************/
	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();

		/******************Rendering code goes here***************************/
		
		// Nettoyage de la fenêtre
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Lancement de la simulation pour les collisions et la physique
		dynamicsWorld->stepSimulation(1.f/FPS,10);
		// Affichage du debugger
		//dynamicsWorld->debugDrawWorld(); 
		
		if(player->rank == 1) {
		  iface.getTexture("YOU WON!")->visible = true;
		} else {
		  bool lose = false;
			for(unsigned int j = 0; j < karts.size(); ++j)
			{
			  if(karts[j]->rank == 0) {
				lose = false; 
				break;
			  }
			  else lose = true;
			}
			if(lose || player->rank > 1) iface.getTexture("You lose...")->visible = true;
		}
			
			if(framesBeforeStart == FPS*3)
			{
			  iface.getTexture("1")->visible = false;
			  iface.getTexture("GO!")->visible = true;
			  
			  for(unsigned int i = 0; i < karts.size(); ++i)
			  {
				karts[i]->Start(true);
			  }
			  
			  framesBeforeStart--;
			} else if (framesBeforeStart != 0) {
			  framesBeforeStart--;
			  
			  switch ((int)(framesBeforeStart/FPS)) {
				case 5:
				  iface.getTexture("3")->visible = true;
				  break;
				case 4:
				  iface.getTexture("3")->visible = false;
				  iface.getTexture("2")->visible = true;
				  break;
				case 3:
				  iface.getTexture("2")->visible = false;
				  iface.getTexture("1")->visible = true;
				  break;
				case 0:
				  iface.getTexture("GO!")->visible = false;
				  break;
			  }
			}
			
			for(unsigned int j = 0; j < karts.size(); ++j)
			{
				for(unsigned int i = 0; i < environments.size(); ++i)
				{
				  environments[i]->callback->index = j;
				  dynamicsWorld->contactPairTest(environments[i]->rigidBody,karts[j]->rigidBody,(*environments[i]->callback));
				}
				m.UpdateMatrix(camera.getViewMatrix() * karts[j]->MVMatrix);
				karts[j]->Update();
				
				if(karts[j]->rank > 0) karts[j]->vignette->position.y = 50 + (4-karts[j]->rank) * 130;
				else karts[j]->vignette->position.y = 50 + (4-map.rank[j]) * 130;
			}
			
			/*for(unsigned int i = 0; i < items.size(); ++i)
			{
			  m.UpdateMatrix(camera.getViewMatrix() * items[i]->MVMatrix);
			  items[i]->Update();
			}*/
		
		m.UpdateMatrix(camera.getViewMatrix() * map.MVMatrix);
		map.Update();
		
		
		/******************* CLASSEMENT - Affichage *********************/
		shaderProgram.stop();
		  iface.Draw();
		shaderProgram.use();
		
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
                    /*if ( e.button.button == SDL_BUTTON_WHEELUP )
                    { 
					  camera.moveFront(-e.button.y/1000.);
				    } else if ( e.button.button == SDL_BUTTON_WHEELDOWN )
                    { 
					  camera.moveFront(e.button.y/1000.);
				    }*/
				    break;
			}
		}

		/*if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(3)) {
            camera.rotateUp((float) (x - WINDOW_WIDTH/2.) / (WINDOW_WIDTH/2.));
            camera.rotateLeft((float) (y - WINDOW_HEIGHT/2.) / (WINDOW_HEIGHT/2.));
        }*/


		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		SDL_GL_SwapBuffers();

		Uint32 tEnd = SDL_GetTicks();
		Uint32 d = tEnd - tStart;
		if(d < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - d);
		}
	}
	
	for(unsigned int i = 0; i < karts.size(); ++i)
	{
	  dynamicsWorld->removeRigidBody(karts[i]->rigidBody);
	}
	/*for(unsigned int i = 0; i < items.size(); ++i)
	{
	  dynamicsWorld->removeRigidBody(items[i]->rigidBody);
	}*/
	dynamicsWorld->removeRigidBody(map.rigidBody);
	
	// Clean up behind ourselves like good little programmers
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
	
	delete player;
	delete bot1;
	delete bot2;
	delete bot3;
	delete acc1;
	delete dec1;
	delete dec2;
	
	SDL_Quit();

	return EXIT_SUCCESS;
}