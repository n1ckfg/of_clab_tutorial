#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video.load("goat.mp4");
    video.setVolume(0);
	video.play(); 

	fbo.allocate(videoWidth, videoHeight);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();

	for (int y = 0; y < gridH; y++) {
		for (int x = 0; x < gridW; x++) {
			mesh.addVertex(ofPoint((x - gridW / 2) * meshSize, (y - gridH / 2) * meshSize, 0));
			mesh.addTexCoord(ofPoint(x * (videoWidth / gridW), y * (videoHeight / gridH)));
			mesh.addColor(ofColor(255, 255, 255));
		}
	}

	for (int y = 0; y < gridH - 1; y++) {
		for (int x = 0; x < gridW - 1; x++) {
			int i1 = x + gridW * y;
			int i2 = x + 1 + gridW * y;
			int i3 = x + gridW * (y + 1);
			int i4 = x + 1 + gridW * (y + 1);
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
		//ofSetColor(255, 255, 255, alpha);

		video.draw(0, 0);
		ofDisableAlphaBlending();
		fbo.end();
	}

    fbo.readToPixels(fboPixels);
	image.setFromPixels(fboPixels);

	for (int y = 0; y < gridH; y++) {
		for (int x = 0; x < gridW; x++) {
			int i = x + gridW * y;
			ofPoint p = mesh.getVertex(i);

			float scaleX = videoWidth / gridW;
			float scaleY = videoHeight / gridH;

			int index = ((x * scaleX) + videoWidth * (y * scaleY)) * 4;
            int brightness = fboPixels[index] * meshHeightScale;

			p.z = brightness; 
			mesh.setVertex(i, p);

            mesh.setColor(i, (ofColor) image.getPixels()[index]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Set background to black and rendering color to white
	ofBackground(0);
	ofSetHexColor(0xffffff);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);

	tiltCurrent = ofLerp(tiltCurrent, tiltTarget, 0.1);
	turnCurrent = ofLerp(turnCurrent, turnTarget, 0.1);
	ofRotateX(tiltCurrent);
	ofRotateZ(turnCurrent);

    image.bind();
	mesh.draw();
    image.unbind();
    mesh.drawWireframe();

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_DOWN) {
		tiltTarget -= 5;
	} else if (key == OF_KEY_UP) {
		tiltTarget += 5;
	} else if (key == OF_KEY_LEFT) {
		turnTarget -= 5;
	} else if (key == OF_KEY_RIGHT) {
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
