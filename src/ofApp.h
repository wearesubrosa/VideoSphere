#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int scale;

		ofVideoPlayer 		vid;
		ofSpherePrimitive sphere;
		ofMaterial material;
		ofPlanePrimitive plane;
		ofxPanel gui;
		ofCamera camera;

		ofxFloatSlider radius;
		ofxFloatSlider sphereResolution;
		ofxFloatSlider sphereZ;
		ofxFloatSlider fov;
		ofxToggle filled;

		void bind();
		void unbind();
		void drawMouseUI();
		ofVec2f mouseDownPosition;
		bool isMouseDown;

		float keyAcc = 2.0f;

		float maxVel = 100.0f;
		float friction = 0.9f;

		ofPoint acc;
		ofPoint vel;
		
};
