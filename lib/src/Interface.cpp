#include "Interface.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Interface::Interface() {
  
}

Interface::~Interface() {  
  for(std::map<std::string,Texture>::iterator it = textures.begin(); it != textures.end(); ++it) {
	glDeleteTextures(1,(GLuint*) it->second.id);
  }
}

bool Interface::AddTexture(const std::string& file, glm::vec2 position, bool visible) {
	/* Création de l'image. */
	SDL_Surface* pTexture;
	pTexture = IMG_Load(file.c_str());
		
	if(!pTexture) {
		std::cerr << "IMG_Load: " << IMG_GetError() << std::endl;
		return false;
	}
	
	textures[file] = LoadTexture(pTexture, position, visible);

	return true;
}

bool Interface::AddText(const std::string& text, glm::vec2 position, bool visible, TTF_Font* font) {
	/* Création de l'image. */
	SDL_Surface* pTexture;
	pTexture = TTF_RenderText_Blended(font, text.c_str(), textColor);
		
	if(!pTexture) {
		std::cerr << "TTF_RenderText_Blended: Erreur lors du chargement du texte :" << text.c_str() << std::endl;
		return false;
	}
	
	textures[text] = LoadText(pTexture, position, visible);

	return true;
}

Texture Interface::LoadTexture(SDL_Surface* pTexture, glm::vec2 position, bool visible) {
	/* Génération de la texture */
    GLuint textureId;
    glGenTextures(1, &textureId);
	glActiveTexture(textureId);
	
	/* Création et chargement de la texture dans OpenGL */
	glBindTexture(GL_TEXTURE_2D, textureId);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pTexture->w, pTexture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, pTexture->pixels);
  
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(textureId);
	
	Texture texture(textureId, position, pTexture->w, pTexture->h, visible);
	
	/* On libère la mémoire. */
	SDL_FreeSurface(pTexture);
	pTexture = NULL;

	return texture;
}

Texture Interface::LoadText(SDL_Surface* pTexture, glm::vec2 position, bool visible) {
	/* Génération de la texture */
    GLuint textureId;
    glGenTextures(1, &textureId);
	glActiveTexture(textureId);
	
	/* Création et chargement de la texture dans OpenGL */
	glBindTexture(GL_TEXTURE_2D, textureId);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pTexture->w, pTexture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTexture->pixels);
  
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(textureId);
	
	Texture texture(textureId, position, pTexture->w, pTexture->h, visible);
	
	/* On libère la mémoire. */
	SDL_FreeSurface(pTexture);
	pTexture = NULL;

	return texture;
}

void Interface::Draw() {
	
	unsigned int i = 0;
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor3f(1, 1, 1);
	
	for(std::map<std::string,Texture>::iterator it = textures.begin(); it != textures.end(); ++it) {
	
	  if(it->second.visible) {
		glBindTexture(GL_TEXTURE_2D, it->second.id);
		
		  // Draw a textured quad
		  glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(-1 + 2.0f * it->second.position.x / WINDOW_WIDTH, -1 + 2.0f * it->second.position.y / WINDOW_HEIGHT);
			glTexCoord2f(0, 0); glVertex2f(-1 + 2.0f * it->second.position.x / WINDOW_WIDTH, -1 + 2.0f * (it->second.position.y+it->second.height) / WINDOW_HEIGHT);
			glTexCoord2f(1, 0); glVertex2f(-1 + 2.0f * (it->second.position.x+it->second.width) / WINDOW_WIDTH, -1 + 2.0f * (it->second.position.y+it->second.height) / WINDOW_HEIGHT);
			glTexCoord2f(1, 1); glVertex2f(-1 + 2.0f * (it->second.position.x+it->second.width) / WINDOW_WIDTH, -1 + 2.0f * it->second.position.y / WINDOW_HEIGHT);
		  glEnd();
		 
		glBindTexture(GL_TEXTURE_2D, 0);
	  }
	  i++;
	}
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

}

Texture* Interface::getTexture(const std::string& file) {
  return &textures[file];
}