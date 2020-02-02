//
//  ParticleSystem.cpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#include "ParticleSystem.h"

void ParticleSystem::setup(ofxCsv _file, int x=100, int y=200){
    vec2 origin = vec2(x,y);
    ifile = _file;
    Particle p;
    p.setup(_file, origin);
    particles.push_back(p);
}

void ParticleSystem::update(){
    for(int i=0; i<particles.size(); i++){
        particles[i].update();
    }
}

void ParticleSystem::addParticle(vec2 pos){
    particles.push_back(Particle(ifile, pos));
}

void ParticleSystem::draw(){
    for(int i=0; i<particles.size(); i++){
        particles[i].draw();
    }
}

