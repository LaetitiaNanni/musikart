#pragma once

#include "Kart.hpp"

class TrackballCamera {

    private :
        float m_fDistance; 
        float m_fAngleX;
        float m_fAngleY;
		Kart* target;
        
    public : 
        TrackballCamera(Kart* k);
        
        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        
        glm::mat4 getViewMatrix() const;

};
