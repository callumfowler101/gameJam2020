#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "RisingWater.h"
#include "Box2dParticleSystem.h"
#include "KinectCV.h"

#define GRID_SZX 20
#define GRID_SZY 15
#define CELL_SZ 64

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void readMap(string, int[][GRID_SZX]);
        void mouseLocation();
        void rotate(int x, int y);
        void mousePressed(int x, int y, int button);
        void exit();
        void polygons();
        void keyPressed(int);
    void initSpriteRotationMap();
    void endGame(int);
    
    KinectCV leKinector;
    Box2dParticleSystem b2dPsys;
//    ParticleSystem pSys;
    RisingWater risingWater;
//    int numOfParticles;
    int numLayers;
    int positionX, positionY;
    vector <ofImage> sprites;
    ofImage spritesheet, sprite;
    int firstLayer[GRID_SZY][GRID_SZX];
    int secondLayer[GRID_SZY][GRID_SZX];
    int counter, currentScore;
    string path;
    
    ofTrueTypeFont myFont, myFontSmall;
    
    map<int, int> spriteRotationMap;
//    vector<ofxBox2dRect> rects;
    vector<shared_ptr<ofxBox2dRect>> rects;
};
