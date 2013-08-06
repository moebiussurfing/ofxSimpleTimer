//
//  ofxSimpleTimer.cpp
//
//  Created by Ben McChesney on 3/8/13.
//  Maintained and open sourced by

//  Helios Interactive
//  301 8th Street
//  STE 250
//  San Francisco , CA

#include "ofxSimpleTimer.h"

void ofxSimpleTimer::setup ( unsigned long delayInMillis )
{
    startTimeMillis = 0.0f ;
    delayMillis = delayInMillis ;
    bIsRunning = false ;
	bIsPaused = false;
}
void ofxSimpleTimer::reset(){
	startTimeMillis = 0.0f ;
    bIsRunning = false ;
	bIsPaused = false;
}
void ofxSimpleTimer::update( )
{
    
    if ( bIsRunning == true )
    {
		if (bIsPaused)
			startTimeMillis = startTimeMillis + (ofGetElapsedTimeMillis() - startTimeMillis);
        //calculate
        if( (ofGetElapsedTimeMillis() - startTimeMillis) > delayMillis )
        {
            ofLog( OF_LOG_VERBOSE , "ofxSimpleTimer::update() TIMER COMPLETE" ) ; 
            bIsRunning = false ;
            if ( bLoop == true )
                start( bLoop ) ;
            
            int args = 18 ;
            ofNotifyEvent( TIMER_COMPLETE , args ) ; 
        }
    }

}

void ofxSimpleTimer::draw( float x , float y )
{
    string debugString = "" ;
    if ( bIsRunning )
    {
        float timeLeft = delayMillis - (ofGetElapsedTimeMillis() - startTimeMillis) ;
        debugString = " RUNNING ! " + ofToString( timeLeft ) + " % : " + ofToString( getNormalizedProgress() ) ;
    }
    else
    {
        debugString = " not running " ;
    }
    
    ofDrawBitmapStringHighlight( debugString , x , y ) ; 
}

void ofxSimpleTimer::start( bool _bLoop , bool bForceReset )
{
	//ofLog( OF_LOG_VERBOSE , "ofxSimpleTimer::start() " ) ;

    //We don't want to start the timer if it's already running
    bool bStartTimer = !bIsRunning ;
   	 
    //Unless we specifically want it too
    if ( bForceReset == true )
        bStartTimer = true ;
    
    if ( bStartTimer == true )
    {
	
        bIsRunning = true ;
		bIsPaused = false;
        startTimeMillis = ofGetElapsedTimeMillis() ;
        bLoop = _bLoop ;
        ofLog( OF_LOG_VERBOSE , "ofxSimpleTimer::start() " ) ;
    }
}

void ofxSimpleTimer::stop( ) 
{
   //We don't want to start the timer if it's already running
   if ( bIsRunning == true ) 
		ofLog( OF_LOG_VERBOSE , "ofxSimpleTimer::stop() " ) ;
	
	bIsRunning = false ; 
	bIsPaused = false;


   
}
void ofxSimpleTimer::togglePause(){
	if (bIsRunning)
		bIsPaused = !bIsPaused;

}

float ofxSimpleTimer::getNormalizedProgress ( )  
{
	if ( !bIsRunning ) return 0.0f ; 

	if ( bIsPaused){
		
		startTimeMillis += (ofGetElapsedTimeMillis() - startTimeMillis);
	}
	float nDiff = delayMillis - (ofGetElapsedTimeMillis() - startTimeMillis) ;
	float percent = (float)nDiff / (float)delayMillis ; 
	return ( 1.0f - percent ) ; 
}