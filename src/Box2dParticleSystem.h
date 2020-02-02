//
//  box2dParticleSystem.hpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#ifndef box2dParticleSystem_hpp
#define box2dParticleSystem_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

using namespace glm;

#define GRID_SZX 20
#define GRID_SZY 15
#define CELL_SZ 64

class Box2dParticleSystem{
public:
    void setup();
    void update();
    void draw();
    void contactPreSolve(b2Contact*&);
    void setItemsLayer(int[][GRID_SZX]);
    void initDropletMovementMap();
    
    int getRise();
    int getScore();
    
    ofxBox2d box2d;
    int secondLayer[GRID_SZY][GRID_SZX];
    
private:
    vector<shared_ptr<ofxBox2dCircle>> circles;
    vec2 origin1, origin2, origin3;
    int numOfRise;
    int score;
//    bool 
    
    map<int, vec2> dropletMovementMap;
};


#endif /* box2dParticleSystem_hpp */
