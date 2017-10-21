#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofVideoPlayer video;
		ofFbo fbo;
		ofMesh mesh;
		ofImage image;
		ofPixels fboPixels;
		int videoWidth = 360;
		int videoHeight = 360;
		int gridW = 100;
		int gridH = 100;
		int meshSize = 6;
        float meshHeightScale = 0.5;
		float tiltCurrent = 0;
		float tiltTarget = 0;
		float turnCurrent = 1;
		float turnTarget = 1;

};
