#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    numOfParticles = 0;
    numLayers = 2;
    
    string path = "/Users/Callum/Desktop/Programming/XCode Libraries/OF_ROOT/apps/myApps/gameJamDraft/bin/data/levels";
    readMap(path + "/level1_bkg.csv", firstLayer);
    readMap(path + "/level1_items.csv", secondLayer);

//    spritesheet = ofImage();
    spritesheet.load(path + "/sprite_sheets.png");
    
    int numSprites = spritesheet.getWidth() / CELL_SZ;
    
    
    for(int i=0; i<numSprites; i++){
        for(int j=0; j<numSprites; j++){
//            ofImage sprite;
            sprite.allocate(cellSize, cellSize, OF_IMAGE_COLOR);
            sprite.cropFrom(spritesheet, i*cellSize, j*cellSize, cellSize, cellSize);
            
            sprites.push_back(sprite);
        }
    }
    
}

void ofApp::readMap(string path, int layer[][GRID_SZ]){
    
    ofxCsv ifile;
    ifile.load(path);
    
    for(int i = 0; i<GRID_SZ; i++){
        ofxCsvRow row = ifile.getRow(i);
        for(int j = 0; j<GRID_SZ; j++){
            int cell = row.getInt(j);
            layer[i][j] = row.getInt(j);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0; i<numOfParticles; i++){
        ofVec2f gravity = ofVec2f(0,0.2);
        particles[i].applyForce(gravity);
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(120);
//    ofDrawRectangle(0, 100, 100, 50);
//    ofDrawRectangle(ofGetWidth(), 200, -100, 50);
    
    for(int l = 0; l<numLayers; l++){
        for(int i = 0; i<GRID_SZ; i++){
            for(int j = 0; j<GRID_SZ; j++){
                int spriteIdx;
                switch (l) {
                    case 0:
                        spriteIdx = firstLayer[i][j];
                        break;
                    case 1:
                        spriteIdx = secondLayer[i][j];
                        break;
                    default:
                        spriteIdx = 0;
                        break;
                }
                if(spriteIdx > 0){
                    sprite = sprites[spriteIdx];
                    sprite.draw(i*cellSize, j*cellSize, cellSize, cellSize);
                }
            }
        }
    }

    
    for(int i=0; i<numOfParticles; i++){
        particles[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c'){
        Particle p;
        p.setup(100,125);
        particles.push_back(p);
        numOfParticles++;
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
