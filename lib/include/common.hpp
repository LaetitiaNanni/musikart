#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace glimac {

static const float PI = 3.14159265358979323846;
	
	struct Material {
		glm::vec4 diffuse;
		glm::vec4 ambient;
		glm::vec4 specular;
		glm::vec4 emissive;
		float shininess;
		int texCount;
	};

	struct ShapeVertex {
	    glm::vec3 position;
	    glm::vec3 normal;
	    glm::vec2 texCoords;
		GLuint texId;
		struct Material material;
	};

}
