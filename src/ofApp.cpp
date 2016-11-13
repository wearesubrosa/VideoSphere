#include "ofApp.h"

bool bDrawGui;
int mode;
ofDirectShowPlayer * dPlayer;

//--------------------------------------------------------------
void ofApp::setup() {
	mode = 0;
	dPlayer = new ofDirectShowPlayer();
	ofPtr<ofBaseVideoPlayer> ptr(dPlayer);
	vid.setPlayer(ptr);

	bDrawGui = false;
	ofSetVerticalSync(true);
	ofBackground(20);

	ofDisableArbTex();

	gui.setup();
	gui.add(filled.setup("fill", true));
	gui.add(radius.setup("radius", ofGetWidth(), 10, ofGetWidth()*4));
	gui.add(sphereZ.setup("Sphere Z", 0, ofGetWidth()*-1, ofGetWidth()*4));
	gui.add(sphereResolution.setup("Sphere Resolution", 12, 0, 64));
	gui.add(fov.setup("Camera FOV", 100, 0, 360));

	float width = ofGetWidth() * .12;
	float height = ofGetHeight() * .12;

	sphere.setRadius(width);
	plane.set(width*1.5, height*1.5);

	material.setShininess(120);
	// the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));

	ofSetSphereResolution(sphereResolution);

	vid.load("360-ashima.mp4");
	vid.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	vid.setLoopState(OF_LOOP_NORMAL);
	vid.play();

	scale = 2;

	camera.setVFlip(true);

}

//--------------------------------------------------------------
void ofApp::update() {
	vid.update();
	//cam.tilt(ofGetElapsedTimef());
	vel += acc;
	vel *= friction;

	// could also use cam.move(x,y,z);
	camera.dolly(vel.z);
	camera.truck(vel.x);

	if (isMouseDown) {
		camera.tilt((ofGetMouseY() - mouseDownPosition.y) / -500.0f);
		camera.pan((ofGetMouseX() - mouseDownPosition.x) / 500.0f);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (mode) {
	case 0:
		camera.setFov(fov);

		camera.begin();
		ofSetSphereResolution(sphereResolution);

		ofEnableDepthTest();

		// draw the outer sphere
		vid.getTexture().bind();
		material.begin();

		if (filled) {
			ofFill();
		}
		else {
			ofNoFill();
		}

		ofDrawSphere(0, 0, sphereZ, radius);
		material.end();
		vid.getTexture().unbind();

		ofDisableDepthTest();
		camera.end();

		break;
	case 1:
		vid.draw(0, 0);
		break;
	}
	if(bDrawGui) gui.draw();

	if (isMouseDown) {
		drawMouseUI();
	}
	ofSetColor(0);
	ofDrawRectangle(0, 0, 120, 20);
	ofSetColor(255);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 0, 20);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case 's':
		scale = scale * 1.25;
		break;

	case 'g':
		bDrawGui = !bDrawGui;
		break;
	case 'f':
	case 'F':
		ofToggleFullscreen();
		break;
	case 'i':
	case 'I':
		mode++;
		if (mode > 1) mode = 0;
		break;
	}

	sphere.mapTexCoordsFromTexture(vid.getTexture());

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	isMouseDown = true;
	mouseDownPosition.set(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	isMouseDown = false;
}

void ofApp::drawMouseUI() {
	ofFill();
	ofSetColor(255);
	ofDrawEllipse(mouseDownPosition.x, mouseDownPosition.y, 10, 10);
	ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), 5, 5);
	ofDrawLine(mouseDownPosition.x, mouseDownPosition.y, ofGetMouseX(), ofGetMouseY());
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

void ofApp::bind() {
	//    ofTexture &tex = hasTex->getTextureReference();
	//    tex.bind();
	//    
	//    glMatrixMode(GL_TEXTURE);
	//    glPushMatrix();
	//    glLoadIdentity();
	//    
	//    ofTextureData texData = tex.getTextureData();
	//    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
	//        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
	//    } else {
	//        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
	//    }
	//    
	//    glMatrixMode(GL_MODELVIEW);
}

void ofApp::unbind() {
	//    hasTex->getTextureReference().unbind();
	//    
	//    glMatrixMode(GL_TEXTURE);
	//    glPopMatrix();
	//    glMatrixMode(GL_MODELVIEW);
}
