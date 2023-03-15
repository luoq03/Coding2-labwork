#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //int maxBoxes = 500;
    ofSetBackgroundColor(0, 0, 0);
    ofSetVerticalSync(false);
    #ifdef USE_CUBE_MAP
    cubeMap.load("background.jpg", 512, true );
    #endif
//    img.load("background.jpg");
//    ofSetLineWidth(2);
    hue = 0;
    int maxSpheres = 200;
    spaceRange = 100;
    ofEnableDepthTest();
    //ofSetBackgroundColor(0);
    ofSetColor(255);
    light.setPosition(-500, 500, 500);
    light.enable();
    animal.load("animal.jpg");
  //animal.getTexture().setTextureWrap(GL_REPEAT,GL_REPEAT);
    
//    for (int i = 0; i < maxBoxes; i ++){
//        ofBoxPrimitive newSphere;
//        newSphere.set(ofRandom(20.150),10);
//        newSphere.mapTexCoordsFromTexture(animal.getTexture());
//        newSphere.setPosition( ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange));
//
//
//        spheres.push_back(newSphere);
//    }
//    }

    
for (int i = 0; i < maxSpheres; i ++){
    ofSpherePrimitive newSphere;
    newSphere.set(ofRandom(20.150),10);
    newSphere.mapTexCoordsFromTexture(animal.getTexture());
    newSphere.setPosition( ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange));

   
    spheres.push_back(newSphere);
}
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }

    
//    boxes[ofRandom( boxes.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
//                       ofRandom(-spaceRange, spaceRange),
//                       ofRandom(-spaceRange, spaceRange));
    
    spheres[ofRandom( spheres.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
                         ofRandom(-spaceRange, spaceRange),
                         ofRandom(-spaceRange, spaceRange));
    glm::vec3 animalOrientation(ofRandom(360),ofRandom(360),ofRandom(360));
    spheres[ofRandom(spheres.size())].setOrientation(animalOrientation);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
//    ofBackground(ofColor::black);
//
//    // draw the original image
//    ofSetColor(ofColor::white);
//    img.draw(0, 0);
    
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
    }

    float time = ofGetSystemTimeMillis()/100.0;
    cam.begin();
    animal.getTexture().bind();
    ofPushMatrix();
    ofRotateDeg(time);
    
//    for (int i = 0; i <boxes.size(); i++){
//        boxes[i].draw();
//    }
//
    for (int i = 0; i <spheres.size(); i++){
        animal.getTexture().bind();
        spheres[i].draw();
        animal.getTexture().unbind();
    }
    
    ofPopMatrix();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
            
        case OF_KEY_UP:
            spaceRange +=20;
            break;
            
        case OF_KEY_DOWN:
            spaceRange -=20;
            break;
            
        default:
            break;
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
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters
    particle newParticle( mouseX, mouseY , hue );
    // push the new particle we just made onto the back of the vector 'particles'
    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     hue = ofRandom( 255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int hue){
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    position = glm::vec2(startX, startY);
    force = glm::vec2(0, 0.02);
    direction = glm::vec2( ofRandom( -2.0, 2.0), ofRandom( -2.0, 2.0) );
    size = 30;
    color.setHsb(hue,  255,  255, 200);
}
//--------------------------------------------------------------

particle::~particle(){
    // destructor
}
//--------------------------------------------------------------

void particle::update(){
    // update the particle x,y position by incrementing each by the velocity vx and vy
    position += direction ;
    direction +=  force;
        if (size > 1){
            size -=0.07;
        }
        float brightness = color.getBrightness();
        float myHue = color.getHue();
    
        if (brightness >20){
           // color.setBrightness( brightness -=0.5 );
            color.setHue( myHue -=0.5 );
    
        }
}

//--------------------------------------------------------------

void particle::draw(){
    ofSetColor(color);
    ofDrawCircle(position, size);
}

