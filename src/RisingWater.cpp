//
//  RisingWater.cpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#include "RisingWater.h"

void RisingWater::setup(){
    waterLevel = 100;
    waveOffset = 0;
    noiseVal = 0;
}

void RisingWater::update(int _rise){
    waterLevel += _rise * 0.035;
    waveOffset+=0.5;
    if(waveOffset>ofGetWidth()) waveOffset;
    noiseVal += 0.1;
}

void RisingWater::draw(){
    ofPushStyle();
    ofSetColor(70,160,200);
    
    ofBeginShape();
    ofVertex(ofGetWidth(), ofGetHeight());
    ofVertex(0, ofGetHeight());
    
    for(int i=0; i<ofGetWidth(); i++){
        float amp = ofNoise(sin(((i*2+noiseVal)*PI)/180)) * 30;
        float offset = ofNoise(sin(((i+waveOffset)*PI)/180)) * amp;
        ofVertex(i, ofGetHeight()-waterLevel+offset);
    }
    ofEndShape();
    ofPopStyle();
}
