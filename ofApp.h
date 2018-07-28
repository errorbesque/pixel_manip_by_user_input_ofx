#pragma once

#include "ofMain.h"
#include "ofPoint.h"
#include "ofxDelaunay2D.h"

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
    
        void extrudePixels();
        bool InsidePolygon(vector<ofPoint> polygon, int N, ofPoint p);
		
    ofPoint myMouse;
    ofPoint tempPoint;
    vector<ofPoint> pointVect; //
    vector<ofVec2f> m_points;
    float vectDistanceThreshold = 20;
    int whichMode = 0;
    int pixelExtrusionDirection = 1;
    vector<int> max_x;
    
    ofImage r1,r2;
    ofPixels pixels;
    
    protected:
        ofMesh m_triangulation;
};
