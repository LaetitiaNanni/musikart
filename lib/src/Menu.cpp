#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <iostream>
#include <SDL/SDL_image.h>
#include "Menu.hpp"



int Menu::menu()
{
	static const Uint32 FPS = 30;
	static const Uint32 FRAME_DURATION = 1000.f / FPS;
    const Uint32 WINDOW_WIDTH = 800;
    const Uint32 WINDOW_HEIGHT = 600;
    
    /************ INITIALISATION **************/
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        std::cerr << "Unable to initialize SDL" << std::endl;
        return -1;
    }

    SDL_Surface *ecran = NULL; 
    ecran = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE);
    if(SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE) == NULL){
        std::cerr << "Unable to open the window" << std::endl;
        return -1;
    }


    SDL_WM_SetCaption("Menu", NULL);


    SDL_Init(SDL_INIT_VIDEO);

    
    /******************* MENU *********************/


    // Allocation de la surface
    SDL_Surface *imageAffichee;
    SDL_Surface *background = NULL;
    SDL_Surface *boutonChoisir = NULL;
    SDL_Surface *flecheGauche = NULL;
    SDL_Surface *flecheDroite = NULL;


    SDL_Rect positionImage, positionTitre, positionBouton, positionGauche, positionDroite, positionBg;


    imageAffichee = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 300, 32, 0, 0, 0, 0);
    boutonChoisir = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
    flecheGauche = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 300, 32, 0, 0, 0, 0);
    flecheDroite = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 300, 32, 0, 0, 0, 0);
    background = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 300, 32, 0, 0, 0, 0);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    

    positionImage.x = (WINDOW_WIDTH / 2) - (520/2) ; 
    positionImage.y = 120;

    positionTitre.x =  (WINDOW_WIDTH / 2) - (400/2);
    positionTitre.y =  20;


    positionBouton.x =  (WINDOW_WIDTH / 2) - (323/2);
    positionBouton.y =  500;

    positionGauche.x =  50;
    positionGauche.y = 120;

    positionDroite.x =  650;
    positionDroite.y =  120;
    
    positionBg.x =  0;
    positionBg.y =  0;

    int page = 1;
    numeroKart = 1;
    numeroCircuit = 1;

    int framerate = 1;


    /************ BOUCLE PRINCIPALE ************/

    bool page2chargee = false; // gérer la fermeture du menu

    bool done = false;
    while(!done){
        Uint32 tStart = SDL_GetTicks();


        /****** CODE DE RENDU ******/

        if (page == 1){ 
           
           // Remplissage de la surface

            if (numeroKart == 1){
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
                imageAffichee= IMG_Load("../images/kart_cherry.png");
            }
            else if (numeroKart == 2){
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,17, 206, 112));
                imageAffichee= IMG_Load("../images/kart_sid.png");

            }
            else if (numeroKart == 3){
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
                imageAffichee= IMG_Load("../images/kart_franky.png");
            }
            else  if (numeroKart == 4){
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
                imageAffichee= IMG_Load("../images/kart_mike.png");
            }
            else {
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
                imageAffichee= IMG_Load("../images/kart_cherry.png");
                numeroKart = 1;
            }

            background= IMG_Load("../images/musikart_bg.png");
            SDL_BlitSurface(background, NULL, ecran, &positionBg); // Collage de la surface sur l'écran


            SDL_BlitSurface(imageAffichee, NULL, ecran, &positionImage); // Collage de la surface sur l'écran

            //SDL_BlitSurface(titre, NULL, ecran, &positionTitre); // Collage de la surface sur l'écran*

             // Remplissage de la surface 
            boutonChoisir= IMG_Load("../images/choisirinstru.png");   
            SDL_BlitSurface(boutonChoisir, NULL, ecran, &positionBouton); // Collage de la surface sur l'écran
            

              // Remplissage de la surface
            flecheGauche= IMG_Load("../images/flechegauche.png");
            SDL_BlitSurface(flecheGauche, NULL, ecran, &positionGauche); // Collage de la surface sur l'écran

              // Remplissage de la surface
            flecheDroite= IMG_Load("../images/flechedroite.png");
            SDL_BlitSurface(flecheDroite, NULL, ecran, &positionDroite); // Collage de la surface sur l'écran
       
            SDL_Flip(ecran); // Mise à jour de l'écran
        }

        else if (page == 2){

            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

            if (numeroCircuit == 1){
                imageAffichee= IMG_Load("../images/circuit1.jpg");

            }
            else if (numeroCircuit == 2){
                imageAffichee= IMG_Load("../images/circuit2.jpg");
            }
            else {
                imageAffichee= IMG_Load("../images/circuit1.jpg");

                numeroCircuit = 1;
            }

            background= IMG_Load("../images/musikart_bg.png");
            SDL_BlitSurface(background, NULL, ecran, &positionBg); // Collage de la surface sur l'écran


            SDL_BlitSurface(imageAffichee, NULL, ecran, &positionImage); // Collage de la surface sur l'écran

            boutonChoisir= IMG_Load("../images/choisircircuit.png");        
            SDL_BlitSurface(boutonChoisir, NULL, ecran, &positionBouton); // Collage de la surface sur l'écran

            flecheGauche= IMG_Load("../images/flechegauche.png");
            SDL_BlitSurface(flecheGauche, NULL, ecran, &positionGauche); // Collage de la surface sur l'écran

            flecheDroite= IMG_Load("../images/flechedroite.png");
            SDL_BlitSurface(flecheDroite, NULL, ecran, &positionDroite); // Collage de la surface sur l'écran

     
            SDL_Flip(ecran); // Mise à jour de l'écran

            page2chargee = true;
        }

            
  
       


        /****** CODE METIER ******/
        

        /****** BOUCLE EVENEMENTIELLE ******/
        SDL_Event event;
        while(SDL_PollEvent(&event)){
		  
            switch(event.type){
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    /********************** PAGE 1 ************************/
                    // choisir
                    if ( page == 1 && event.button.x >= ((WINDOW_WIDTH / 2) - (400/2)) && event.button.x <=  ((WINDOW_WIDTH / 2) - (400/2) + 400) && event.button.y >= 450 && event.button.y <= (450 + 100)){
                           
//                            /*** Entrer choix du kart ***/

                            page = 2;
                    }
                    // fleche gauche
                     if ( page == 1 && event.button.x >= 50 && event.button.x <=  50 + 100 && event.button.y >= 120 && event.button.y <= (120 + 300)){
                               

                        numeroKart --;
                        if (numeroKart == 0){
                            numeroKart = 4;
                        }                      
                    }

                    // fleche droite
                     if (  page == 1 && event.button.x >= 650 && event.button.x <= (650 + 100) && event.button.y >= 120 && event.button.y <= (120 + 300)){
                        numeroKart ++;
                       
                        if (numeroKart == 5){
                            numeroKart = 1;
                        }

                    }


                           /********************** PAGE 2 ************************/
                    // choisir
                    if ( page == 2 && event.button.x >= ((WINDOW_WIDTH / 2) - (400/2)) && event.button.x <=  ((WINDOW_WIDTH / 2) - (400/2) + 400) && event.button.y >= 450 && event.button.y <= (450 + 100)){


//                        /*** Entrer choix du circuit ***/



                        if (page2chargee == true){
                       /*     SDL_FreeSurface(boutonChoisir);
                            SDL_FreeSurface(imageAffichee);
                            SDL_FreeSurface(flecheGauche);
                            SDL_FreeSurface(flecheDroite); 
                       */  
                             done = true;
                        }
                    }

                    // fleche gauche
                     if ( page == 2 && event.button.x >= 50 && event.button.x <=  50 + 100 && event.button.y >= 120 && event.button.y <= (120 + 300)){
                      
                        numeroCircuit --;
                        if (numeroCircuit == 0){
                            numeroCircuit = 2;
                        }                        
                    }

                    // fleche droite
                     if (  page == 2 && event.button.x >= 650 && event.button.x <= (650 + 100) && event.button.y >= 120 && event.button.y <= (120 + 300)){
                        numeroCircuit ++;
                        
                        if (numeroCircuit == 3){
                            numeroCircuit = 1;
                        }

                    }
                    break;

                case SDL_KEYUP:
                
                    break;

                default:
                    break;
            }
        }



        Uint32 tEnd = SDL_GetTicks();
		Uint32 d = tEnd - tStart;
		if(d < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - d);
		}
        
    }


/*   SDL_FreeSurface(boutonChoisir);
   SDL_FreeSurface(imageAffichee);
   SDL_FreeSurface(flecheGauche);
   SDL_FreeSurface(flecheDroite);
    SDL_Quit();


    SDL_Quit();
*/


    return 0;
}
