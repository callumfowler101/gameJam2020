#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    numLayers = 2;
    
    pSys.setup(CELL_SZ*2, CELL_SZ*1.5);
    
    string path = "/Users/Callum/Desktop/Programming/XCode Libraries/OF_ROOT/apps/myApps/gameJamDraft/bin/data/assets";
    readMap(path + "/level1_bkg.csv", firstLayer);
    readMap(path + "/level1_items.csv", secondLayer);
    

    spritesheet.load(path + "/sprite_sheets.png");
    
    int numSprites = spritesheet.getWidth() / CELL_SZ;
    
    for(int i=0; i<numSprites; i++){
        for(int j=0; j<numSprites; j++){
            sprite.allocate(CELL_SZ, CELL_SZ, OF_IMAGE_COLOR);
            sprite.cropFrom(spritesheet, j*CELL_SZ, i*CELL_SZ, CELL_SZ, CELL_SZ);
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
    pSys.update();
    mouseLocation();
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
                if(spriteIdx >= 0){
                    sprite = sprites[spriteIdx];
                    /*
                     run rotate() here;
                     */
                    sprite.draw(j*CELL_SZ, i*CELL_SZ, CELL_SZ, CELL_SZ);
                }
            }
        }
    }
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofDrawEllipse(positionX, positionY, 10, 10);
    ofPopStyle();
    
    pSys.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


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
    int localPositionX = (positionX/GRID_SZ);
    int localPositionY = (positionY/GRID_SZ);
    if(button == 0){
        rotate(localPositionX, localPositionY);
    }
//    if(button == 0){
//        for(int i=0; i<GRID_SZ; i++){
//            for(int j=0; j<GRID_SZ; j++){
//                secondLayer[localPositionX][localPositionY];
//                
//                
//            }
//        }
//    }
    
}

void ofApp::rotate(int x, int y){
    int spriteIdx = secondLayer[x][y];
    /*
     if we replace sprites we can say:
     spriteIdx = spriteIdx + 1;
     return spriteIdx;
     */
    
    /*
     if we rotate the sprite:
     ofPixels pixels
     
     pixels.allocate(128,128,RGB);
     
     */
}

void ofApp::mouseLocation(){
    float mouseXoffset = ofGetMouseX()%CELL_SZ;
    float mouseYoffset = ofGetMouseY()%CELL_SZ;
    
    int mouseXPos = ofGetMouseX() - mouseXoffset;
    mouseXPos += CELL_SZ*0.5;
    int mouseYPos = ofGetMouseY() - mouseYoffset;
    mouseYPos += CELL_SZ*0.5;
    
    positionX = mouseXPos;
    positionY = mouseYPos;
    
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
