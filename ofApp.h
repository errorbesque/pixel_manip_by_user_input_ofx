#pragma once

#include "ofMain.h"
#include "ofPoint.h"
#include "ofxGui.h"

#include "ofImage.h"
#include "ofxCvImage.h"
#include "ofxCvColorImage.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxPSBlend.h"
#include "ofPixels.h"

#include "ofColor.h"

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
        vector<ofPoint> getPixelsBetweenPoints(ofPoint p1, ofPoint p2);
    
        void guiChanged(int &test1);
		
    ofPoint myMouse;
    ofPoint tempPoint;
    vector<ofPoint> pointVect; //
    vector<ofPoint> pointVectToPixels; //
    vector<int> timeOfPointVect;

    int framenum = 0;
    
    ofImage r1,r2;
    ofPixels pixels;
    
    ofxPanel gui;
    ofxIntSlider extrude_x;
    ofxIntSlider extrude_y;
    ofxIntSlider jitter_on;
};
