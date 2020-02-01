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

using namespace glm;

class ParticleSystem{
public:
    void setup(int x, int y);
    void update();
    void draw();
    
private:
    vector<Particle> particles;
    int numOfParticles;
};




#endif /* ParticleSystem_hpp */
