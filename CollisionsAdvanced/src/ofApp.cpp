#include "ofApp.h"
#include "Examples/UnionPolygonExample.h"
#include "Examples/BitmaskExample.h"
#include "Examples/AABBRotationExample.h"
#include "Examples/CollisionsExample.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/*TODO ALUNO: modifique esta variável para inicializar o exemplo*/
	screen = new AABBRotationExample();
	screen->init();
}

//--------------------------------------------------------------
void ofApp::update(){
	try {
		auto next = screen->nextScreen();

		if (next == nullptr) {
			screen->close();
			delete screen;
			std::exit(0);
		} else if (next != screen) {
			screen->close();
			delete screen;

			screen = next;
			screen->init();
		}

		screen->update();
	}
	catch (exception& e) {
		cerr << "Exception: " << e.what() << endl;
		std::exit(1);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0, 0, 0);
	screen->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	EventManager::lastKeyPressed = tolower(key);
	EventManager::keyOn[EventManager::lastKeyPressed] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	EventManager::keyOn[tolower(key)] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
