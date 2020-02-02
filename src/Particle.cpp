//
//  Element.cpp
//  flowfieldPools
//
//  Created by Callum Fowler on 26/12/2019.
//

#include "Particle.h"


Particle::Particle(ofxCsv _file, vec2 _origin){
    origin = _origin;
    loc = vec2(origin);
    vel = vec2(0,0);
    acc = vec2(0,0);
    mass = 10;
    gravity = vec2(0, 0.2);
    bounce = vec2(0, -0.7);
    ellipseSz = mass;
    maxSpeed = ofMap(mass, 5, 10, 1, 1.5);
    file = _file;
    counter = 0;
}

void Particle::setup(ofxCsv _file, vec2 _origin){
    origin = _origin;
//    origin = vec2(ofG, 200);
    loc = vec2(origin);
    vel = vec2(0.01,0);
    acc = vec2(0,0);
    mass = 10;//ofRandom(1,10);
    gravity = vec2(0.0, 0.06);
    bounce = vec2(0, -0.7);
    ellipseSz = mass;
    maxSpeed = ofMap(mass, 5, 10, 1, 1.5);
    
    file = _file;
//    path = "/Users/Callum/Desktop/Programming/XCode Libraries/OF_ROOT/apps/myApps/gameJamDraft/bin/data/assets/level1_items.csv";
//    file.load(path);
//
   
}

void Particle::applyForce(vec2 _force){
    vec2 f = _force/mass;
    acc = f;
    cout<<f<<endl;
//    if(_force == gravity) dir = 1; // right
}

void Particle::update(){
    edgeCheck();
    applyForce(forceType(currentSpriteIdx));

    if(counter > 20){
        counter = 0;
    }
//    normalize(vel);
//    vel *=maxSpeed;
    loc += vel;
    vel += acc;
    counter ++;

//    acc *= 0;
}

vec2 Particle::forceType(int _spriteIdx){
//    cout<< _spriteIdx << endl;
    if(_spriteIdx>-1){
        vel = vel * (-(gravity+vec2(1.2,.5)));
//        cout<< wallCheck(_spriteIdx) << endl;
//        if(wallCheck(_spriteIdx)){
//            if(_spriteIdx == 12){
//                return vec2(0.06, 0);
//            } else if (_spriteIdx == 14){
//                return vec2(0.003, 0.003);
//            } else {
//                return bounce;
//            }
    } else {
        return gravity;
    }
}

int Particle::gridSpriteIdx(){
    float gridXOffset = int(loc.x)%CELL_SZ;
    float gridYOffset = int(loc.y)%CELL_SZ;
    
    int partLocX = loc.x - gridXOffset;
    partLocX += CELL_SZ*0.5;
    int partLocY = loc.y - gridYOffset;
    partLocY += CELL_SZ*0.5;
    
    if(abs(loc.x-partLocX) < 16 && abs(loc.y-partLocY) < 16){
        partLocX /= CELL_SZ;
        partLocY /= CELL_SZ;
        
        position = vec2(partLocX, partLocY);
        return cell(position);
    }
    
    return -1;

}

int Particle::cell(vec2 _pos){
    int x = _pos.x;
    int y = _pos.y;
    
    int cell;
    if(y<10 && x<10){
        ofxCsvRow row = file.getRow(y);
        cell = row.getInt(x);
    } else {
        cell = -1;
    }
    return cell;
}

//bool Particle::wallCheck(int _spriteIdx){
//    bool check;
//    vec2 nXPos = vec2(position.x + CELL_SZ,position.y);
//    vec2 nYPos = vec2(position.x,position.y + CELL_SZ);
//    if(dir == 1 && (cell(nXPos)==12||cell(nXPos)==13)){
//        check = true;
//    }
//    else check = false;
//
//    return check;
//    cout << check << endl;
//
//}

void Particle::edgeCheck(){
    if(loc.y > ofGetHeight()+ellipseSz){
        loc = origin;
    }
    if(loc.x > ofGetWidth()+ellipseSz){
        loc = origin;
    }
}

void Particle::draw(){
    ofPushStyle();
    ofSetColor(80,170,210);
    ofDrawEllipse(loc, ellipseSz, ellipseSz);
    ofPopStyle();
    currentSpriteIdx = gridSpriteIdx();
}





