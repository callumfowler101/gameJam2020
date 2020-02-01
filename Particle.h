#pragma once

#include "ofMain.h"

using namespace glm;

class Particle {
public:
    void setup(vec2 _origin);
    void update();
    void draw();
    void keyPressed(int key);
    
    void applyForce(vec2 force);
    void edgeCheck();
    
private:
    vec2 loc, acc, vel, origin;
    float mass, maxSpeed;
    int ellipseSz, szMult;
    ofColor spriteColors;
};


