#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glimac {

class FreeflyCamera {
	void computeDirectionVectors() {
		float PIoverTwo = M_PI * 0.5f;
		float cTheta = cos(m_fTheta);
		m_FrontVector = glm::vec3(cTheta * sin(m_fPhi), sin(m_fTheta), cTheta * cos(m_fPhi));
		m_LeftVector = glm::vec3(sin(m_fPhi + PIoverTwo), 0, cos(m_fPhi + PIoverTwo));
		m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
	}

public:
	FreeflyCamera(): m_Position(0.f), m_fPhi(M_PI), m_fTheta(0.f) {
		computeDirectionVectors();
	}

	void moveFront(float delta) {
		m_Position += m_FrontVector * delta;
	}

	void moveLeft(float delta) {
		m_Position += m_LeftVector * delta;
	}

	void rotateLeft(float degrees) {
		m_fPhi += glm::radians(degrees);
		computeDirectionVectors();
	}

	void rotateUp(float degrees) {
		m_fTheta += glm::radians(degrees);
		computeDirectionVectors();
	}

	glm::mat4 getViewMatrix() const {
		return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
	}

private:
	glm::vec3 m_Position;
	float m_fPhi, m_fTheta;
	glm::vec3 m_FrontVector;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;
};

}