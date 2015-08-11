//
//  rtAgent.h
//  exampleSimpleXOR
//
//  Created by Davy Smith on 14/04/2015.
//
//

#pragma once

#include "ofMain.h"

#define AGENT_SIZE 10.0
#define MAXIMUM_VELOCTY 10.0
#define VELOCITY_FALL_OFF 0.99

class rtAgent
{
    
    public:
    
    void setup();
    void update();
    void draw();
    
    void updateVelocity(float x_vel, float y_vel);
    
    private:
    
    ofVec2f position;
    ofVec2f velocity;
    
};