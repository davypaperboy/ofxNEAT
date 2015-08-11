//
//  rtAgent.cpp
//  exampleSimpleXOR
//
//  Created by Davy Smith on 14/04/2015.
//
//

#include "rtAgent.h"


void rtAgent::setup() {
    position.set(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
    velocity.limit(MAXIMUM_VELOCTY);
}

void rtAgent::update() {
    velocity *= VELOCITY_FALL_OFF;
    position += velocity;
}

void rtAgent::updateVelocity(float x_vel, float y_vel) {
    velocity.set(velocity.x + x_vel, velocity.y + y_vel);
}

void rtAgent::draw() {
    
}
