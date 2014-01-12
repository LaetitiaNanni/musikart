#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Matrix {
  GLint uMVPMatrixLocation;
  GLint uMVMatrixLocation;
  GLint uNormalMatrixLocation;
  GLint uTextureLocation;
  glm::mat4 ProjMatrix;
  
  Matrix(GLuint GLId, unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT) {
	uMVPMatrixLocation = glGetUniformLocation(GLId, "uMVPMatrix");
	uMVMatrixLocation = glGetUniformLocation(GLId, "uMVMatrix");
	uNormalMatrixLocation = glGetUniformLocation(GLId, "uNormalMatrix");
	uTextureLocation = glGetUniformLocation(GLId, "uTexture");
	
	ProjMatrix = glm::perspective(70.f, (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f);
  }
  
  void UpdateMatrix(glm::mat4 MVMatrix) {
	glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
	glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::inverse(glm::transpose(MVMatrix))));
	glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniform1i(uTextureLocation, 0);
  }
};
