#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.loadMovie("goat.mp4");
	video.play(); 

	fbo.allocate(videoWidth, videoHeight);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();

	for (int y = 0; y<H; y++) {
		for (int x = 0; x<W; x++) {
			mesh.addVertex(ofPoint((x - W / 2) * meshSize, (y - H / 2) * meshSize, 0)); 
			mesh.addTexCoord(ofPoint(x * (videoWidth / W), y * (videoHeight / H)));
			mesh.addColor(ofColor(255, 255, 255));
		}
	}

	for (int y = 0; y<H - 1; y++) {
		for (int x = 0; x<W - 1; x++) {
			int i1 = x + W * y;
			int i2 = x + 1 + W * y;
			int i3 = x + W * (y + 1);
			int i4 = x + 1 + W * (y + 1);
			mesh.addTriangle(i1, i2, i3);
			mesh.addTriangle(i2, i4, i3);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();
	
	if (video.isFrameNew()) {
		fbo.begin();

		int alpha = 20;
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, alpha);

		video.draw(0, 0);
		ofDisableAlphaBlending();
		fbo.end();
	}

	for (int y = 0; y<H; y++) {
		for (int x = 0; x<W; x++) {
			int i = x + W * y;
			ofPoint p = mesh.getVertex(i);

			p.z = ofNoise(x * 0.05, y * 0.05, ofGetElapsedTimef() * 0.5) * 100;
			mesh.setVertex(i, p);

			mesh.setColor(i, ofColor(255, 255, 255));
		}
	}

	fbo.readToPixels(fboPixels);
	image.setFromPixels(fboPixels);

	//Change vertices
	for (int y = 0; y<H; y++) {
		for (int x = 0; x<W; x++) {

			//Vertex index
			int i = x + W * y;
			ofPoint p = mesh.getVertex(i);

			float scaleX = videoWidth / W;
			float scaleY = videoHeight / H;

			// get brightness
			int index = ((x * scaleX) + videoWidth * (y * scaleY)) * 4; // FBO has four components (including Alpha)
			int brightness = fboPixels[index] / 4; // 4 is an arbitrary scalar to reduce the amount of distortion

												   //Change z-coordinate of vertex
			p.z = brightness; // ofNoise(x * 0.05, y * 0.05, ofGetElapsedTimef() * 0.5) * 100;
			mesh.setVertex(i, p);

			//Change color of vertex
			mesh.setColor(i, ofColor(255, 255, 255));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Set background to black and rendering color to white
	ofBackground(0);
	ofSetHexColor(0xffffff);

	// fbo.draw(0, 0);

	ofPushMatrix(); //Store the coordinate system

					//Move the coordinate center to screen's center
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);

	tiltCurrent = ofLerp(tiltCurrent, tiltTarget, 0.1);
	turnCurrent = ofLerp(turnCurrent, turnTarget, 0.1);
	ofRotateX(tiltCurrent);
	ofRotateZ(turnCurrent);

	//Draw mesh
	image.bind();
	mesh.draw();
	image.unbind();
	// mesh.drawWireframe();

	ofPopMatrix(); //Restore the coordinate system
}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_DOWN) {
		tiltTarget -= 5;
	}
	else if (key == OF_KEY_UP) {
		tiltTarget += 5;
	}
	else if (key == OF_KEY_LEFT) {
		turnTarget -= 5;
	}
	else if (key == OF_KEY_RIGHT) {
		turnTarget += 5;
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
