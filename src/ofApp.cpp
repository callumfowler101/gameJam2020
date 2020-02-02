#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    numLayers = 2;
    risingWater.setup();
    b2dPsys.setup();
    initSpriteRotationMap();
    
    myFont.load("Iron.ttf",90);
    myFontSmall.load("Iron.ttf",30);
    
    counter = 0;
    currentScore = 0;
    
    path = "/Users/Callum/Desktop/Programming/XCode Libraries/OF_ROOT/apps/myApps/gameJamDraft/bin/data/assets/dan";
    readMap(path + "/v2_Tile Layer 1.csv", firstLayer);
    readMap(path + "/v2_Tile Layer 2.csv", secondLayer);
    b2dPsys.setItemsLayer(secondLayer);

    spritesheet.load(path + "/sprite_sheets.png");
    
    int numSprites = spritesheet.getWidth() / CELL_SZ;
    
    for(int i=0; i<numSprites; i++){
        for(int j=0; j<numSprites; j++){
            sprite.allocate(CELL_SZ, CELL_SZ, OF_IMAGE_COLOR);
            sprite.cropFrom(spritesheet, j*CELL_SZ, i*CELL_SZ, CELL_SZ, CELL_SZ);
            sprites.push_back(sprite);
        }
    }
    ofxCsv file;
    file.load("/Users/Callum/Desktop/Programming/XCode Libraries/OF_ROOT/apps/myApps/gameJamDraft/bin/data/assets/dan/v2_Tile Layer 2.csv");
    
    polygons();
}

void ofApp::readMap(string path, int layer[][GRID_SZX]){
    
    ofxCsv ifile;
    ifile.load(path);
    
    for(int i = 0; i<GRID_SZY; i++){
        ofxCsvRow row = ifile.getRow(i);
        for(int j = 0; j<GRID_SZX; j++){
            int cell = row.getInt(j);
            layer[i][j] = row.getInt(j);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    leKinector.update();
    b2dPsys.update();
    risingWater.update(b2dPsys.getRise());
//    mouseLocation();
    
}

//--------------------------------------------------------------
void ofApp::polygons(){
    for(int i = 0; i<GRID_SZY; i++){
        for(int j = 0; j<GRID_SZX; j++){
            if (secondLayer[i][j]!=-1){
                auto rect = std::make_shared<ofxBox2dRect>();
                rect->setPhysics(0,0.5,0.1);
                float offset = CELL_SZ*0.5;
                ofRectangle rectangle = ofRectangle(j*CELL_SZ+offset,i*CELL_SZ+offset,CELL_SZ,CELL_SZ);
                cout<< j*CELL_SZ << " " << i*CELL_SZ<<endl;
                rect->setup(b2dPsys.box2d.getWorld(), rectangle);
                rects.push_back(rect);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int l = 0; l<numLayers; l++){
        for(int i = 0; i<GRID_SZY; i++){
            for(int j = 0; j<GRID_SZX; j++){
                int spriteIdx;
                switch (l) {
                    case 0:
                        spriteIdx = firstLayer[i][j];
                        break;
                    case 1:
                        spriteIdx = secondLayer[i][j];
                        if(secondLayer[i][j]!=-1){
                            if(counter%(i*j+100) == 0)
                                rotate(j, i);
                        }
                        break;
                    default:
                        spriteIdx = 0;
                        break;
                }
                if(spriteIdx >= 0){
                    sprite = sprites[spriteIdx];
                    sprite.draw(j*CELL_SZ, i*CELL_SZ, CELL_SZ, CELL_SZ);
                }
            }
        }
    }
//    ofPushStyle();
//    ofSetColor(255, 0, 0);
//    ofDrawEllipse(positionX, positionY, 10, 10);
//    ofPopStyle();
    
    

    b2dPsys.draw();
    risingWater.draw();
    leKinector.draw(b2dPsys.box2d);
    
//    for(int i=0; i<rects.size(); i++){
//        rects[i].get()->draw();
//        
//    }
    
    if(b2dPsys.getRise()>=20){
        endGame(currentScore);
    } else {
    string score = "SCORE "+ofToString(b2dPsys.getScore());
    myFontSmall.drawString(score, 10,50);
    currentScore = b2dPsys.getScore();
    }
    cout<<currentScore<<endl;
    
    
    
    
    if(counter<80){
    string ready = "READY?";
    string set = "SET";
    string go = "GO!";
        
    string filler;
    if (counter> 20) filler = ready;
    if (counter > 40) filler = set;
    if (counter > 60) filler = go;
    
    if (filler == ready) {
        myFont.drawString(filler, ofGetWidth() / 2 - 150, ofGetHeight() / 2);
    }else
        myFont.drawString(filler, ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    }
    
    
    
    
    counter++;
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::rotate(int x, int y){
    int mX = x;
    int mY = y;

    if(spriteRotationMap.count(secondLayer[mY][mX]))
        secondLayer[mY][mX] = spriteRotationMap[secondLayer[mY][mX]];
    b2dPsys.setItemsLayer(secondLayer);
}

void ofApp::initSpriteRotationMap(){
    spriteRotationMap[10] = 11;
    spriteRotationMap[11] = 15;
    spriteRotationMap[15] = 14;
    spriteRotationMap[14] = 10;
    
    spriteRotationMap[6] = 9;
    spriteRotationMap[9] = 6;
}

//void ofApp::mouseLocation(){
//    float mouseXoffset = ofGetMouseX()%CELL_SZ;
//    float mouseYoffset = ofGetMouseY()%CELL_SZ;
//
//    int mouseXPos = ofGetMouseX() - mouseXoffset;
//    mouseXPos += CELL_SZ*0.5;
//    int mouseYPos = ofGetMouseY() - mouseYoffset;
//    mouseYPos += CELL_SZ*0.5;
//
//    positionX = mouseXPos;
//    positionY = mouseYPos;
//}

void ofApp::keyPressed(int key){
    leKinector.keyPressed(key);
}

void ofApp::exit(){
    leKinector.exit();
}

void ofApp::endGame(int _currentScore){
    string gameOver = "GAME OVER!";
    string fScore = "SCORE "+ofToString(_currentScore);

    myFont.drawString(gameOver, ofGetWidth() / 2 - 250, 300);
    myFont.drawString(fScore, ofGetWidth() / 2 - 200, 400);
}

