#include "TrackballCamera.hpp"
#include "glm/gtc/matrix_transform.hpp"

TrackballCamera::TrackballCamera(Kart* k) : m_fDistance(6.0f), m_fAngleX(20.0f), m_fAngleY(0.0f) {
  target = k;
}

void TrackballCamera::moveFront(float delta) {
    m_fDistance += delta;
	m_fDistance = glm::max(0.1f, m_fDistance);
}

void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleX += degrees;
}

void TrackballCamera::rotateUp(float degrees) {
    m_fAngleY += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 ViewMatrix = glm::translate(glm::mat4(1), glm::vec3(0, -1.5, -m_fDistance + target->getSpeedBox().direction * target->getSpeedBox().currentValue*2/target->getSpeedBox().maxValue));
    ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
    ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
    
    return ViewMatrix * glm::inverse(glm::rotate(target->MVMatrix,target->getTurnBox().direction * target->getTurnBox().currentValue * 45.0f / target->getTurnBox().maxValue,glm::vec3(0,1,0)));
}
