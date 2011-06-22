//
//  User.h
//  scavengerMap
//
//  Created by Ben McChesney on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef _USER
#define _USER



#include "ofMain.h"
#include "ofxVectorMath.h" 
#include <vector>

class User {
    
	public:

        ofxVec2f target, position, velocity, force, acceleration ; 
    
        float maxVelocity , maxForce ; 
        int locationIndex ; 
        bool changeTarget ;
        vector<ofxVec2f> locations;
        ofColor color ;
    
        User() 
        {
            
        }
    
        User( ofxVec2f pos , ofxVec2f tar, int _locationIndex ) 
        {
            locationIndex = _locationIndex;
            velocity = (ofRandom(0.1f, 0.4f), ofRandom(0.1f, 0.4f), 0.3f);
            acceleration = ofxVec3f( .4 , .4 , .4 ) ; 
            position = pos ; 
            target = tar ; 
            force = ofxVec3f ( 0 , 0 , 0 ) ; 
            maxVelocity = ofRandom( 3, 6 )  ;
            maxForce = ofRandom ( .05 , .1 )  ; 
            color = ofColor() ; 
            color.r = ofRandom ( 0 , 255 ) ; 
            color.g = ofRandom ( 0 , 255 ) ; 
            color.b = ofRandom ( 0 , 255 ) ; 
            for ( int i = 0 ; i < 6 ; i++ ) 
            {
                locations.push_back( ofxVec2f ( ofRandom( 0 , ofGetWidth() ) , ofRandom( 0 , ofGetHeight() ) ) ) ; 
            }
        }
    
        void update() 
        {
            force.limit(maxForce);
            velocity += force;
            
            velocity.limit(maxVelocity);
            position += velocity;
            
            seek ( target ) ; 
            /*
            speed = target - position ; 
            speed.limit( maxSpeed ) ; 
            position += speed ;
            */
            float dist = position.distance( target ) ; 
            if ( dist < 50 ) 
            {
             //   max
                changeTarget = true ;
            }
            
            int w = ofGetWidth() ; 
            int h = ofGetHeight() ; 
            if ( position.x < 0 ) 
                position.x += w ; 
            if ( position.x > w ) 
                position += -w ; 
            if ( position.y < 0 ) 
                position.y += h ; 
            if ( position.y > h ) 
                position.y += -h ; 
        }
    
    
    void addForce ( ofxVec2f _force ) 
    {
        force += _force ; 
    }
    
    void seek(ofxVec2f oTarget) {
        // This is how it works.
        // 1. We calculate the change in position which would bring
        // use directly to the target. This is "desired_vel". Though we don't
        // want to jump directly to this target, but slowly move to it.
        ofxVec2f desiredVelocity = oTarget - position;
        
        // 2. Therefore we want to move to this position at the maximum
        // allowed speed. We do this by normalizing the vector and then
        // multiplying it with the maximum allowed speed. This is exactly
        // what ofxVec3f.scale() does.
        desiredVelocity.scale(maxVelocity);
        
        // 3. Now we have the maximum desired velocity at the maximum speed.
        // Though we need to adjust this speed as we want to go into that direction
        // at the best we are allowed, which is the remaining velocity.
        desiredVelocity -= velocity;
        
        addForce(desiredVelocity);
        
        //cout << "Desired vel: " << desired_vel.x << ", " << desired_vel.y << endl;
    }
    
    void draw() 
    {
        ofEnableSmoothing();
        glPushMatrix();
        glTranslatef(position.x, position.y, 1 );
        
        //img.draw(0,0);
        glPopMatrix();
        ofSetLineWidth(3);
        
        float arrow_len = 14;
        ofxVec3f arrow_end = position +(velocity.normalized() * arrow_len);
        ofFill();
        ofEnableSmoothing();
        ofSetColor(color.r , color.g, color.b );
        ofLine(position.x, position.y, arrow_end.x, arrow_end.y);
        //ofCircle(arrow_end.x, arrow_end.y, 3);
        
        //ofSetColor(0xFFFFFF);
        ofCircle(position.x, position.y, 5);
        ofNoFill();
        
        ofEnableSmoothing();
        
        //ofSetColor(0xFFFFFF);
        //ofSetLineWidth(20);
        ofCircle(position.x, position.y, 5);
        
        
        ofSetColor(0x00);
        ofSetLineWidth(3);
        ofCircle(position.x, position.y, 7);
        
        
        ofDisableSmoothing();
        
        
        ofEnableAlphaBlending() ; 
        ofSetColor(color.r , color.g , color.b , 25) ; 
        
        ofNoFill() ; 
        //printf( locations.size() ) ;
        ofCircle( position.x , position.y , 2 ) ; 
        
       // ofxVec3f tail_end = position +(-speed.normalized() * arrow_len * 2 );
       // ofLine(position.x, position.y, tail_end.x, tail_end.y);
        ofxVec2f& cur = locations[0] ; 
        ofxVec2f& next = locations[0] ;
        
        int len = locations.size()  ; 
        for ( int i = len ; i > 0 ; i-- )
        {
            ofSetLineWidth( ( 15 - i ) * .35 );
            cur = locations[i] ; 
            //   next = locations[i+1] ; 
            if ( i +1 < locations.size() )
            {
                ofxVec3f midPoint ;
                if ( locations[i].y < locations[i+1].y )
                {
                    midPoint = (locations[i] + locations[i+1]) / 2 ; 
                    midPoint.y +=  midPoint.x * .35 ; 
                }
                else
                {
                    midPoint = (locations[i] + locations[i+1]) / 2 ;
                    midPoint.y +=  -midPoint.x * .35 ;
                }
                //ofLine( locations[i+1].x ,locations[i+1].y , locations[i].x , locations[i].y ) ; 
                ofBezier( cur.x , cur.y , midPoint.x , midPoint.y , midPoint.x , midPoint.y , locations[i+1].x , locations[i+1].y ) ;  
            }
           // ofCircle ( 0 , 0  , 4 ) ; 
        }
    }
};

#endif 