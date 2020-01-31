#pragma once

#include "ofMain.h"

class Particle {
public:
    void setup(int x, int y);
    void update();
    void draw();
    void keyPressed(int key);
    
    void applyForce(ofVec2f force);
    void edgeCheck();
    
    
    ofVec2f loc, acc, vel;
    float mass, maxSpeed;
    int ellipseSz, szMult;
    ofColor spriteColors;
};


