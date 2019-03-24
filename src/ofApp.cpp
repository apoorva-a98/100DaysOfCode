#include "ofApp.h"
#include "VectorHead.h"
#include "iostream"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    agent = VectorHead();
    meal = Food();
	pill = Poison();
	rock = Obstacle();
}

//--------------------------------------------------------------
void ofApp::update(){
    agent.update();
    agent.arriveAtFood(meal);
	//agent.arriveAtPoison(pill);
	agent.energy = agent.energy - 5;
}

//--------------------------------------------------------------
void ofApp::draw(){
	meal.display();
	pill.display();
    agent.display();
	rock.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //Target.x = x;
    //Target.y = y;
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
