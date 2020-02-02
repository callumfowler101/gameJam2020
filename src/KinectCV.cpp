//
//  KinectCV.cpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#include "KinectCV.h"


KinectCV::KinectCV(){
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init(false, false); // disable video image (faster fps)
    kinect.open();        // opens first available kinect
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    grayImage.allocate(kinect.width*2, kinect.height*2);
    mask.allocate(kinect.width*2, kinect.height*2);
    pixMask.allocate(kinect.width*2, kinect.height*2, OF_PIXELS_GRAY); // allocate mask pixel of kinect image
    
    nearThreshold = 200;
    farThreshold = 160;
    
    blobMin = 512;
    blobMax = 16000;
    
    bThreshWithOpenCV = true;
    kinectCamera = false;
        
    // zero the tilt on startup
    angle = 10;
    kinect.setCameraTiltAngle(angle);
}

void KinectCV::update(){
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        ofPixels depthPix;
        depthPix.allocate(kinect.width, kinect.height, OF_PIXELS_GRAY);
        
        ofPixels pix = kinect.getDepthPixels();
        for(int i = 0; i<pix.size(); i++){
            depthPix[i] = pix[i];
        }
        
//        for(int i = 0; i<kinect.height; i++){
//            for(int j = 0; j<kinect.width; j++){
//                depthPix[i*kinect.width+j] = pix[i*kinect.width+j];
//            }
//        }
        
        depthPix.resize(kinect.width*2, kinect.height*2);
        grayImage.setFromPixels(depthPix);
        grayImage.mirror(false, true);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            ofxCvGrayscaleImage grayThreshNear = grayImage;
            ofxCvGrayscaleImage grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        }
        for(int i = 0; i<depthPix.size(); i++)
            pixMask[i] = depthPix[i] < nearThreshold && farThreshold < depthPix[i] ? 255:0;
        
        // update the cv images
        grayImage.flagImageChanged();
        mask.setFromPixels(pixMask);
        mask.mirror(false, true);
        contourFinder.findContours(mask, blobMin, blobMax, 4, false); // manipulate for pixel(Minimum, maximum, number of blobs)
    }
    
}

void KinectCV::draw(ofxBox2d& box2d){
    vector<float>xpos;
    if(kinectCamera)
        grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPushStyle();
    for(int i = 0; i < contourFinder.nBlobs; i++) {
        ofSetColor(0, 255, 0);
        ofDrawEllipse(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 30, 30);
        xpos.push_back(contourFinder.blobs[i].centroid.x);
    }
    ofPopStyle();
    if(contourFinder.nBlobs >= 4){
        
        ofPushStyle();
        ofSetLineWidth(5); // line width
        ofSetColor(7,157,224);
        
        vector<size_t> xIdx = KinectCV::sort_indexes(xpos);
        
        ofxCvBlob blob_11 = contourFinder.blobs[xIdx[0]]; // find first blob
        ofxCvBlob blob_12 = contourFinder.blobs[xIdx[1]]; // find second blob
        //
        ofxCvBlob blob_21 = contourFinder.blobs[xIdx[2]]; // find first blob
        ofxCvBlob blob_22 = contourFinder.blobs[xIdx[3]]; // find second blob
        
        edgeOne.clear();
        edgeOne.addVertex(blob_11.centroid.x, blob_11.centroid.y);
        edgeOne.addVertex(blob_12.centroid.x, blob_12.centroid.y);
        
        edgeOne.setPhysics(0, 0.5, 0.5);
        edgeOne.create(box2d.getWorld());
        edgeOne.draw();
        
        
        edgeTwo.clear();
        edgeTwo.addVertex(blob_21.centroid.x, blob_21.centroid.y);
        edgeTwo.addVertex(blob_22.centroid.x, blob_22.centroid.y);


        ofDrawEllipse(blob_11.centroid.x, blob_11.centroid.y, 30, 30);
        ofDrawEllipse(blob_12.centroid.x, blob_12.centroid.y, 30, 30);
        ofPopStyle();
        
        ofPushStyle();
        ofSetColor(255,0,0);
        edgeTwo.setPhysics(0, 0.5, 0.5);
        edgeTwo.create(box2d.getWorld());
        edgeTwo.draw();
        ofDrawEllipse(blob_21.centroid.x, blob_21.centroid.y, 30, 30);
        ofDrawEllipse(blob_22.centroid.x, blob_22.centroid.y, 30, 30);
        ofPopStyle();
    }
//    drawInstructions();
}

void KinectCV::drawInstructions(){
    // draw instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    if(kinect.hasAccelControl()) {
        reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
        << ofToString(kinect.getMksAccel().y, 2) << " / "
        << ofToString(kinect.getMksAccel().z, 2) << endl;
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
    << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    << ", fps: " << ofGetFrameRate() << endl
    << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected()
    << "blob min = " << blobMin << " " << " blob max = " << blobMax <<
    endl;
    
    if(kinect.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
        << "press 1-5 & 0 to change the led mode" << endl;
    }
    
    ofDrawBitmapString(reportStream.str(), 0, 0);
}



//--------------------------------------------------------------
void KinectCV::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
}

//--------------------------------------------------------------
void KinectCV::keyPressed (int key) {
    
    //
    switch (key) {
        case ' ':
//            bThreshWithOpenCV = !bThreshWithOpenCV;
            kinectCamera = !kinectCamera;
            break;
            
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
            
        case 'w':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
            
        case 'o':
            kinect.setCameraTiltAngle(angle); // go back to prev tilt
            kinect.open();
            break;
            
        case '1':
            kinect.setLed(ofxKinect::LED_GREEN);
            break;
            
        case '2':
            kinect.setLed(ofxKinect::LED_YELLOW);
            break;
            
        case '3':
            kinect.setLed(ofxKinect::LED_RED);
            break;
            
        case '4':
            kinect.setLed(ofxKinect::LED_BLINK_GREEN);
            break;
            
        case '5':
            kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
            break;
            
        case '0':
            kinect.setLed(ofxKinect::LED_OFF);
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_RIGHT:
            blobMin -= 16;
            break;
            
        case OF_KEY_LEFT:
            blobMin += 16;
            break;
            
        case 'z':
            blobMax -= 16;
            break;
            
        case 'x':
            blobMax += 16;
            break;
    }
}
