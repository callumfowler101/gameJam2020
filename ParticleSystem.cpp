//
//  ParticleSystem.cpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#include "ParticleSystem.h"

void ParticleSystem::setup(int x, int y){
    vec2 origin = vec2(x,y);
    numOfParticles = 100;
    for(int i=0; i<numOfParticles; i++){
        Particle p;
        p.setup(origin);
        particles.push_back(p);
    }
    
}

void ParticleSystem::update(){
    for(int i=0; i<numOfParticles; i++){
        vec2 gravity = vec2(0,0.06);
        particles[i].applyForce(gravity);
        particles[i].update();
    }
    
}

void ParticleSystem::draw(){
    for(int i=0; i<numOfParticles; i++){
        particles[i].draw();
    }
    
    
}
