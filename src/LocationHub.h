//
//  LocationHub.h
//  scavengerMap
//
//  Created by Ben McChesney on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _LOCATION_HUB
#define _LOCATION_HUB



#include "ofMain.h"
#include "ofxVectorMath.h" 

class LocationHub {
    
	public:
        
        ofxVec2f location , speed ; 
        float population ; 
        ofColor color ; 
    
        LocationHub( ) 
        {
            
        }
    
        LocationHub( ofxVec2f _location , ofColor _color ) 
        {
            location = _location ; 
            color = _color ; 
            population = 0 ; 
            speed = ofxVec2f( ofRandom ( -5 , 5 ) , ofRandom( .1 , .25 ) ) ; 
        }
    
    	void update();

};

#endif