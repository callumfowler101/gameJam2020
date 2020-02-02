//
//  KinectCV.hpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#ifndef KinectCV_hpp
#define KinectCV_hpp

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxBox2D.h"
#include <stdio.h>

class KinectCV {

public:
    
    KinectCV();
    void update();
    void draw(ofxBox2d&);
    void drawInstructions();
    void exit();
    void keyPressed(int);
    
    template <typename T>
    static vector<size_t> sort_indexes(const vector<T> &v){
        // initialize original index locations
        vector<size_t> idx(v.size());
        iota(idx.begin(), idx.end(), 0);
        
        // sort indexes based on comparing values in v
        // using std::stable_sort instead of std::sort
        // to avoid unnecessary index re-orderings
        // when v contains elements of equal values
        stable_sort(idx.begin(), idx.end(),
                    [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
        
        return idx;
    }
    
    ofxKinect kinect;

    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage mask;
    ofPixels pixMask;
    
    ofxCvContourFinder contourFinder;
    
    int nearThreshold;
    int farThreshold;
    int angle;
    
    int blobMin, blobMax;
    bool bThreshWithOpenCV;
    bool kinectCamera;
    
    //boxball
    ofxBox2dEdge edgeOne;
    ofxBox2dEdge edgeTwo;
};

#endif /* KinectCV_hpp */
