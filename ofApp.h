#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxCsv.h"
#include "ParticleSystem.h"

#define GRID_SZ 10
#define CELL_SZ 64

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void readMap(string, int[][GRID_SZ]);
        void mouseLocation();
        void rotate(int x, int y);
    
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
   
		
    ParticleSystem pSys;
//    int numOfParticles;
    int numLayers;
    int positionX, positionY;
    vector <ofImage> sprites;
    ofImage spritesheet, sprite;
    int firstLayer[GRID_SZ][GRID_SZ];
    int secondLayer[GRID_SZ][GRID_SZ];
    float angle[360][360];
    
};
