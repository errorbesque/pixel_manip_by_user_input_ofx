#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // present image (future state: allow user to select image)
    ofSetColor(255, 0, 0);
    r1.load(ofToDataPath("hoop1.jpg"));
    
    pixels  = r1.getPixels();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    switch(whichMode) {
        case 1:
            // draw finished polygon
            ofBeginShape();
            for( int i = 0; i < pointVect.size(); i++) {
                ofVertex(pointVect[i]);
            }
            ofEndShape();
            // for all pixels in image
            // test if inside the polygon we just drew
            for (int j=0; j<r1.getHeight(); j++) {
                max_x.push_back(0);
                for (int i = 0; i<r1.getWidth(); i++) {
                    if (ofInsidePoly(i,j,pointVect)) {
                        if (i>max_x[j]) {
                            max_x[j]=i;
                        }
                    }
                }
            }
            
            // start extrusion
            
            break;
        case 2:
            // all pixels right of the border are extruded
            for (int j=0; j<r1.getHeight(); j++) {
                if (max_x[j]!=0) {
                for (int i=max_x[j];i<r1.getWidth();i++){
                    pixels.setColor(i,j,pixels.getColor(max_x[j],j));
                }}
            }
            
            break;
    } // end switch
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // mode: drawing polygon
    switch(whichMode){
        case -1:
            // draw image
            // r1.draw(2,2,600,700);
            
        case 0:
            // ofBackground(0);
            // continuously draw image
            r1.draw(2,2,r1.getWidth(),r1.getHeight());

            ofDrawCircle(myMouse,2);
            
            // draw the clicked-on points
            ofSetColor(255,0,0);
            for(int i=1; i<pointVect.size(); i++){
                    ofDrawLine(pointVect[i],pointVect[i-1]);
            }
            
            ofNoFill();
            ofSetColor(0,70,255);
            
            // draw the last point to the current point
            ofSetColor(128,128,128);
            if (pointVect.size()) ofDrawLine(myMouse,pointVect[pointVect.size()-1]);
            break;
            
        case 1: // fill a finished polygon
            
            r1.draw(2,2,r1.getWidth(),r1.getHeight());
            
            for (int j=0;j<400; j++){
                ofDrawCircle(max_x[j],j,2);
            }
            whichMode = 2;
            
            break;
            
        case 2: // extrusion
            // r2.draw(2,2,r1.getWidth(),r1.getHeight());
            ofSetColor(255,255,255);
            ofNoFill();

            r2.setFromPixels(pixels);
            r2.draw(2,2,r2.getWidth(),r2.getHeight());
            break;
    }
}


void ofApp::extrudePixels(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        // m_triangulation.clear();
        // m_points.clear();
        pointVect.clear();
        whichMode = 0; // go back to prepping
        pixels  = r1.getPixels();

    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    myMouse.x = x;
    myMouse.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofSetColor(0, 255, 0);
    // maybe start tracking points?
    pointVect.push_back(myMouse);
    //
    
    if (pointVect.size()>2 && pointVect[pointVect.size()-1].distance(pointVect[0]) < vectDistanceThreshold) {
        // finished the polygon, start the extrusion
        // prompt the user for which direction
        whichMode = 1;
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofSetColor(255, 0, 0);
    // draw a line from old point to new point
    
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
