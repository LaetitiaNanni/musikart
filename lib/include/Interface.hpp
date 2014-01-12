#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>

#include "glm/glm.hpp"

struct Texture {
  Texture() {}
  Texture(GLuint _id, glm::vec2 _position, float _width, float _height, bool _visible) :
  id(_id), position(_position), width(_width), height(_height), visible(_visible) {}

  GLuint id;
  glm::vec2 position;
  float width;
  float height;
  bool visible;
};

class Interface {
  public :
	Interface();
	~Interface();
	
	bool AddTexture(const std::string& file, glm::vec2 position, bool visible);
	bool AddText(const std::string& file, glm::vec2 position, bool visible, TTF_Font* font);
	
	Texture LoadTexture(SDL_Surface* pTexture, glm::vec2 position, bool visible);
	Texture LoadText(SDL_Surface* pTexture, glm::vec2 position, bool visible);
	
	void Draw();
	void GenVerticesObjects();
	
	Texture* getTexture(const std::string& file);
	
  private :
	std::map<std::string,Texture> textures;
	
	SDL_Color textColor = {255, 255, 255};
};