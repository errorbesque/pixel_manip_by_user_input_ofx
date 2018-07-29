#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // set up GUI
    gui.setup("pixel options");
    gui.add(extrude_x.setup("x dir",0,-1,1));
    gui.add(extrude_y.setup("y dir",0,-1,1));
    gui.add(jitter_on.setup("jitter points",0,0,1));

    gui.setPosition(600, 700);
    extrude_y.addListener(this, &ofApp::guiChanged);
    extrude_x.addListener(this, &ofApp::guiChanged);

    // -1 pauses drawing
    framenum=-1;

    ofNoFill();
    
    // image in bin/data (future state: allow user to select image)
    r1.load(ofToDataPath("hoop2.jpg"));
    
    pixels  = r1.getPixels();
    r2.setFromPixels(pixels);
    
     // r1.draw(2,2,r1.getWidth(),r1.getHeight());
    ofSetBackgroundAuto(false); // don't clear background?
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (pointVect.size() > 0) framenum++; // only increment if there are points
    gui.draw();
}


//-----

vector<ofPoint> ofApp::getPixelsBetweenPoints(ofPoint p1, ofPoint p2){
    // basic 2-point interpolation

    int x0 = p1.x;
    int x1 = p2.x;
    int y0 = p1.y;
    int y1 = p2.y;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    vector<ofPoint> returnpoints;
    
    while(true)
    {        
        if (x0 == x1 && y0 == y1) break; // done with looking for pixels
        
        e2 = 2 * err;
        
        // EITHER horizontal OR vertical step (but not both!)
        if (e2 > dy)
        {
            err += dy;
            x0 += sx;
        }
        else if (e2 < dx)
        { // <--- this "else" makes the difference
            err += dx;
            y0 += sy;
        }
        
        returnpoints.push_back(ofPoint(x0,y0));
    }
    
    return returnpoints;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (framenum < 0) {
        r2.draw(2,2,r2.getWidth(),r2.getHeight());
    } // if not, we don't want to wipe the image
    
    
            int xx, yy;
            for (int i =0; i<pointVect.size(); i++) { // for all points in pointVect (i.e. points you've clicked/dragged)
                // propagate the color of the clicked pixel to other pixels
                ofSetColor(pixels.getColor(pointVect[i].x, pointVect[i].y));
                // if jitter on, corrupt starting point.
                pointVect[i].x+=jitter_on*int(ofRandom(-2,2))*extrude_x;
                pointVect[i].y+=jitter_on*int(ofRandom(-2,2))*extrude_y;
                // draw the pixel at that point translated for time and direction.
                xx = pointVect[i].x + extrude_x*(framenum - timeOfPointVect[i])+jitter_on*int(ofRandom(-2,2)); // where the pixel would have drifted by now
                yy = pointVect[i].y + extrude_y*(framenum - timeOfPointVect[i]); // where the pixel would have drifted by now

                // validate (don't try to draw if out of frame)
                if (xx < r1.getWidth() && xx > 0 && yy > 0 && yy < r1.getHeight()) {
                    ofDrawCircle(xx, yy, 1); // draw small circle
                }
            }
    
    
    gui.draw();
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){ // reset image
        pointVect.clear();
        pointVectToPixels.clear();
        pixels  = r1.getPixels();
        r2.setFromPixels(pixels);
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
    myMouse.x = x;
    myMouse.y = y;
    pointVect.push_back(myMouse);
    timeOfPointVect.push_back(framenum);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pointVect.push_back(myMouse);
    timeOfPointVect.push_back(framenum);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    pointVect.push_back(myMouse);
    timeOfPointVect.push_back(framenum);
    
}

void ofApp::guiChanged(int &test1){
    // directionality change. revert to no points clicked so the old points won't start going in the new direction.
    pointVect.clear(); // remove points
    timeOfPointVect.clear(); // remove points
    framenum = 0;
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
