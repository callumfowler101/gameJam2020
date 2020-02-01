//
//  Element.cpp
//  flowfieldPools
//
//  Created by Callum Fowler on 26/12/2019.
//

#include "Particle.h"

void Particle::setup(vec2 _origin){
    origin = _origin;
    loc = vec2(origin);
    vel = vec2(0,0);
    acc = vec2(0,0);
    mass = ofRandom(1,10);
    ellipseSz = mass;
    maxSpeed = ofMap(mass, 1, 10, 1, 3);
}
//--------------------------------------------------------------

void Particle::applyForce(vec2 force){
    vec2 f = force/mass;
    acc += f;
}
//--------------------------------------------------------------
void Particle::update(){
    edgeCheck();
    vel += acc;
    loc += vel;
    normalize(vel);
    vel*maxSpeed;
    acc *= 0;
}
//--------------------------------------------------------------
void Particle::edgeCheck(){
    if(loc.y > ofGetHeight()+ellipseSz){
        loc = origin;
    }
    
}
//--------------------------------------------------------------
void Particle::draw(){
    ofPushStyle();
    ofSetColor(80,170,210);
    ofDrawEllipse(loc, ellipseSz, ellipseSz);
    ofPopStyle();
}





