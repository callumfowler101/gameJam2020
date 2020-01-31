//
//  Element.cpp
//  flowfieldPools
//
//  Created by Callum Fowler on 26/12/2019.
//

#include "Particle.h"

void Particle::setup(int x, int y){
    loc = ofVec2f(x, y);
    vel = ofVec2f(0,0);
    acc = ofVec2f(0,0);
    mass = ofRandom(1,10);
    ellipseSz = mass;
    maxSpeed = ofMap(mass, 1, 10, 1, 0.5);
}
//--------------------------------------------------------------

void Particle::applyForce(ofVec2f force){
    ofVec2f f = force/mass;
    acc += f;
}
//--------------------------------------------------------------
void Particle::update(){
//    edgeCheck();
    vel += acc;
    loc += vel;
    acc *= 0;
}
//--------------------------------------------------------------
void Particle::edgeCheck(){
    if(loc.y > ofGetHeight()+ellipseSz);
}
//--------------------------------------------------------------
void Particle::draw(){
    ofSetColor(80,170,210);
    ofDrawEllipse(loc, ellipseSz, ellipseSz);
}





