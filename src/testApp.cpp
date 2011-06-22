#include "testApp.h"

#define LOCATIONS_SIZE 18
#define USERS_SIZE 8

LocationHub locations[LOCATIONS_SIZE] ; 

User users[USERS_SIZE] ; 
//------------------------------

void testApp::setup(){
    for ( int i = 0; i < LOCATIONS_SIZE ; i++ ) 
    {
        ofColor _color ; 
        _color.r = ofRandom( 0 , 255 ) ; 
        _color.g = ofRandom( 0 , 255 ) ; 
        _color.b = ofRandom( 0 , 255 ) ; 
        locations[i] = LocationHub( ofxVec2f( ofRandom( 0 , ofGetWidth() ) , ofRandom( 0 , ofGetHeight() ) ) , _color ) ;
    }
    
    for ( int i = 0 ; i < USERS_SIZE ; i++ )
    {
        //fxVec2f pos , ofxVec2f tar 
        int index = int(ofRandom(0,20)) ; 
        users[i] = User( ofxVec2f( ofRandom( 0 , ofGetWidth() ) , ofRandom ( 0 , ofGetHeight() ) ) , locations[index].location, index ) ; 
    }
    
    ofSetFrameRate( 30 ) ;
    
    ofBackground(0, 0, 0);
    ofSetBackgroundAuto(false) ; 
}

//--------------------------------------------------------------
void testApp::update()
{
    //for ( int i = 0; i < 20 ; i++ ) 
    //{
    //    locations[i].update() ; 
    //}
                                                                                                   
    for ( int i = 0; i < USERS_SIZE ; i++ ) 
    {
        users[i].update() ; 
    }                                                                                               
}

//--------------------------------------------------------------
void testApp::draw()
{
    
    ofEnableAlphaBlending() ; 
    ofSetColor ( 0 , 0 , 0 , 255 ) ;
    ofFill() ; 
    ofRect ( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 

   // float newDegree = (mouseX +- ofGetWidth() * .5 ) ; 
    ofTranslate ( .5 , .5 ) ; 
    ofRotateX( cameraOffset.x ) ;
    ofRotateY( cameraOffset.y ) ;
    for ( int i = 0 ; i < USERS_SIZE ; i++ ) 
    {
        users[i].draw() ; 
        if ( users[i].changeTarget == true ) 
        {
            int index = int(ofRandom(0,20)) ; 
            users[i].changeTarget = false ; 
            locations[users[i].locationIndex ].population += 2.0f ; 
            users[i].locations.push_back ( locations[users[i].locationIndex ].location ) ; 
            users[i].target = locations[index].location ; 
            users[i].locationIndex = index ; 
            
        }
        //ofLine( users[i].position.x , users[i].position.y ,
        //        users[i].position.x +- users[i].speed.x  , users[i].position.y +- users[i].speed.y) ; 
    }
    ofFill(); 
    ofEnableSmoothing() ; 
    
    for ( int i = 0; i < LOCATIONS_SIZE ; i++ ) 
    {
        ofSetColor( locations[i].color.r , locations[i].color.g , locations[i].color.b  ) ; 
        //iLocationHub = locations[i] ; 
        ofCircle( locations[i].location.x , locations[i].location.y , locations[i].population ) ; 
        // wayPoints[i] = ofxVec2f( ofRandom( 0 , ofGetWidth() ) , ofRandom( 0, ofGetHeight() ) ) ; 
    }
         
    ofRotateX ( -cameraOffset.x ) ; 
    ofRotateY ( -cameraOffset.y ) ; 
    ofTranslate(-.5, -.5) ; 
       // ofRotateX(-newDegree)  ;                                                                                        
                                                                                                   
                                                                                            
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
        float amount = 3.5f ; 
    
    	switch (key) 
        {
         
                case 'w':
                    cameraOffset.y += amount ; 
                    break ;
                case 's' :
                    cameraOffset.y -= amount ; 
                    break ;
                case 'a' :
                    cameraOffset.x -= amount ; 
                    break ; 
                
                case 'd' :
                    cameraOffset.x += amount ;
                    break ; 
                
        }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

