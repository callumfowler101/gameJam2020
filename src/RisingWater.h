//
//  RisingWater.hpp
//  gameJamDraft
//
//  Created by Callum Fowler on 01/02/2020.
//

#ifndef RisingWater_h
#define RisingWater_h
#include "ofMain.h"
#include "ParticleSystem.h"
#include "math.h"

#include <stdio.h>

class RisingWater{
public:
    void setup();
    void update(int _rise);
    void draw();
    
private:
    float waterLevel;
    float waveOffset;
    float noiseVal;
};


#endif /* RisingWater_hpp */
