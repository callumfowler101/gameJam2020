//
//  ParticleSystem.hpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#ifndef ParticleSystem_h
#define ParticleSystem_h

#include <stdio.h>
#include "ofMain.h"
#include "Particle.h"
#include "ofxCsv.h"

using namespace glm;

class ParticleSystem{
public:
    
    void setup(ofxCsv _file, int x, int y);
    void update();
    void draw();
    vec2 pipeType(int spriteIdx);
    
    void collisionWalls();
    void addParticle(vec2);
    
private:
    vector<Particle> particles;
    int numOfParticles;
    vec2 force;
    ofxCsv ifile;
};




#endif /* ParticleSystem_hpp */
