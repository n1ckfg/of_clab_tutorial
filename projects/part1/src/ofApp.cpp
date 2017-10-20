#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();

	gui.add(wavelength.setup("wavelength", 0.125, 0.05, 0.2));
	gui.add(amplitude.setup("amplitude", 20, 0, 40));
	gui.add(noiseScale.setup("noiseScale", 5, 0, 10));
	gui.add(distortion.setup("distortion", 5, 0, 10));
	gui.add(ySpeed.setup("ySpeed", 1, 0, 5));

	image1.loadImage("Sylvie_Pic.png");

	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {
	image2 = wave(image1);
}

//--------------------------------------------------------------
void ofApp::draw() {
	image2.draw(0, 0);  
	ofBackgroundGradient(ofColor::white, ofColor::black);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}

ofImage ofApp::wave(ofImage sourceImg) {
	ofImage newImg;
	newImg.clone(sourceImg);
	float time = ofGetElapsedTimef();
	for (int y=0; y<image1.getHeight(); y++) { 
		for (int x=0; x<image1.getWidth(); x++) { 
			float noise = ofNoise(time + y * 0.001) * noiseScale;
			float noiseAmp = noise * amplitude;
			float waveform = sin((y * wavelength) + time * ySpeed);
			float wave = (waveform + distortion) * noiseAmp;
			int xWave = x + wave;
			ofColor color = sourceImg.getColor( xWave, y ); 
			newImg.setColor( x, y, color ); 
		} 
	} 
	newImg.update(); 
	return newImg;
}