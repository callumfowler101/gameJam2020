//
//  box2dParticleSystem.cpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#include "Box2dParticleSystem.h"

void Box2dParticleSystem::setup(){
    
    box2d.init();
    box2d.setGravity(0, 17);
    box2d.createBounds();
    box2d.enableEvents();
    
//    ofAddListener(box2d.contactStartEvents, this, &Box2dParticleSystem::contactStart);
//    ofAddListener(box2d.contactEndEvents, this, &Box2dParticleSystem::contactEnd);
    
    ofAddListener(box2d.contactPreSolve, this, &Box2dParticleSystem::contactPreSolve);
    
    origin1 = vec2(CELL_SZ*2+(CELL_SZ*0.5),CELL_SZ);
    origin2 = vec2(CELL_SZ*10+(CELL_SZ*0.5),CELL_SZ);
    origin3 = vec2(CELL_SZ*15+(CELL_SZ*0.5),CELL_SZ);

    numOfRise = 0;
    score = 0;
    
    for(int i=0; i<20; i++){
        auto circle = std::make_shared<ofxBox2dCircle>();
        int yOffset = ofRandom(50);
        circle->setPhysics(0.1, 0.5, 0);
        vec2 origin;
        int randomiser = floor(ofRandom(3));
        if(randomiser==0)origin = origin1;
        if(randomiser==1)origin = origin2;
        if(randomiser==2)origin = origin3;
        circle->setup(box2d.getWorld(), origin.x, origin.y-yOffset, 10); //getCanvas, startX, startY, radius
        circles.push_back(circle);
    }
    
    initDropletMovementMap();
    
//    box2d.setContactListener(ofxBox2dContactListener *listener)
}

void Box2dParticleSystem::update(){
    box2d.update();
    for(int i=0; i<circles.size(); i++){
        //        circles[i]->setLinearDamping(1);
//        vec2 vel = circles[i]->getVelocity();
        vec2 loc = circles[i]->getPosition();
        
        //look up position in cvs table
        
        if(loc.y>ofGetHeight()-100){
            circles[i]->setVelocity(0, 0);
            int randomiser = floor(ofRandom(3));
            vec2 origin;
            if(randomiser==0)origin = origin1;
            if(randomiser==1)origin = origin2;
            if(randomiser==2)origin = origin3;
            circles[i]->setPosition(origin);
            numOfRise++;
        }
        if(loc.x+10>CELL_SZ*18&&(loc.y+10>CELL_SZ*5&&loc.y+10<CELL_SZ*7)){
            circles[i]->setVelocity(0, 0);
            int randomiser = floor(ofRandom(3));
            vec2 origin;
            if(randomiser==0)origin = origin1;
            if(randomiser==1)origin = origin2;
            if(randomiser==2)origin = origin3;
            circles[i]->setPosition(origin);
            score++;
        }
    }
}

int Box2dParticleSystem::getRise(){
    return numOfRise;
}

int Box2dParticleSystem::getScore(){
    return score;
}

void Box2dParticleSystem::draw(){
    ofPushStyle();
    ofSetColor(70,160,200);
    for(int i=0; i<circles.size(); i++){
        circles[i].get()->draw();
    }
    ofPopStyle();
}

void Box2dParticleSystem::contactPreSolve(b2Contact*& c) {
    
    ofxBox2dContactArgs e;

    e.a = c->GetFixtureA();
    e.b = c->GetFixtureB();
    if(e.a != NULL && e.b != NULL) {
        
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_polygon) {
            ofxBox2dCircle* droplet = (ofxBox2dCircle*)e.a->GetBody();
            cout<<droplet->getVelocity()<<endl;
        }else if(e.b->GetType() == b2Shape::e_circle && e.a->GetType() == b2Shape::e_polygon){
            ofxBox2dCircle* droplet = (ofxBox2dCircle*)e.b->GetBody();
            ofxBox2dRect* rect = (ofxBox2dRect*)e.a->GetBody();
            ofVec2f rectPos = rect->getPosition();
            int rectX = rectPos.x / CELL_SZ, rectY = rectPos.y / CELL_SZ;
            
            ofVec2f dropVel = droplet->getVelocity();
            dropVel.normalize();
            
//            cout<< dropVel <<endl;
            
            int directionX, directionY;
            if(dropVel.y>0.5) directionY = 0; //down
            if(dropVel.y<=-0.5) directionY = 1; //up
            if(dropVel.x>0.5) directionX = 0; //right
            if(dropVel.x<=-0.5) directionX = 1; //left
            
            //            cout<<directionX<<" "<<directionY<<endl;
            
            int itemIdx = secondLayer[rectY][rectX];
            if(itemIdx==0){
                c->SetEnabled(false);
            }
            else if(itemIdx>-1 && dropletMovementMap.count(itemIdx)){
                vec2 force = dropletMovementMap[itemIdx];
                float forceVal=0.005;
                if(itemIdx==10&&directionX==0)
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force,forceVal);//applyforce;
                if(itemIdx==11&&directionY==0)
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force,forceVal);//applyforce;
                if(itemIdx==15&&directionY==1)
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force,forceVal);//applyforce;
                if(itemIdx==14&&directionX==1)
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force,forceVal);//applyforce;
                if(itemIdx==6&&directionY==0){
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force, forceVal);//applyforce;
                }
      
                if(itemIdx==9&&directionX==0)
                    c->SetEnabled(false);
                    droplet->addRepulsionForce(force,forceVal);//applyforce;
            }
//            cout<<itemIdx<<endl;
//            cout<<droplet->getVelocity()<<endl;
        }
    }
}

void Box2dParticleSystem::setItemsLayer(int arr[][GRID_SZX]){
//    memcpy(secondLayer, arr, GRID_SZX*GRID_SZY);
    
    for(int i = 0; i<GRID_SZY; i++){
        for(int j = 0; j<GRID_SZX; j++){
            secondLayer[i][j] = arr[i][j];
        }
    }
}

//--------------------------------------------------------------
void Box2dParticleSystem::initDropletMovementMap(){
    dropletMovementMap[10] = vec2(1,-1);    //RIGHT->UP
    dropletMovementMap[11] = vec2(-1,1);    //DOWN->LEFT
    dropletMovementMap[15] = vec2(1,-1);    //UP->RIGHT
    dropletMovementMap[14] = vec2(-1,1);    //LEFT->DOWN
    
    dropletMovementMap[6] = vec2(0,1);      //DOWN
    dropletMovementMap[9] = vec2(1,0);      //RIGHT
}


