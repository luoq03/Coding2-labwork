//
//  boidtwo.cpp
//  emptyExample
//
//  Created by Macbook Pro on 2023/2/6.
//

#include "boidtwo.hpp"

boidtwo::boidtwo()
{
    separationWeight = 1.9f;
    cohesionWeight = 1.2f;
    alignmentWeight = 0.2f;
    
    separationThreshold = 20;
    neighbourhoodSize = 100;
    
    position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
    velocity = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2));
}

void boidtwo::draw()
{
    ofSetColor(0, 0, 255);
    ofCircle(position.x, position.y, 20);
}
