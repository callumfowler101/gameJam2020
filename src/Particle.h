#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#define GRID_SZX 20
#define GRID_SZY 15
#define CELL_SZ 64


using namespace glm;

class Particle {
public:
    Particle(){};
    Particle(ofxCsv, vec2);
    void setup(ofxCsv _file, vec2 _origin);
    void update();
    void draw();
    void keyPressed(int key);
    
    void applyForce(vec2 _force);
    void edgeCheck();
    int gridSpriteIdx();
    
    bool wallCheck(int _spriteIdx);
    
    vec2 forceType(int _spriteIdx);
    
    int cell(vec2 _pos);
    
private:
    vec2 loc, acc, vel, origin,position;
    vec2 gravity, bounce;
    float mass, maxSpeed;
    int ellipseSz, szMult;
    int dir;
    ofColor spriteColors;
    string path;
    ofxCsv file;
    int currentSpriteIdx;
    int counter;
};


