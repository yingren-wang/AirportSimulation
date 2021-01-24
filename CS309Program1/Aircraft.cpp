/*******************************************************
 *  Aircraft.cpp
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#include "Aircraft.h"

using namespace std;

Aircraft::Aircraft(){
	for(int n = 0; n < 32; n++){
        aMake[n] = '0';
    }
	for(int n = 0; n < 32; n++){
        aType[n] = '0';
    }
	aRateClimb = 0.0;
	aWingSpan = 0.0;
	aLength = 0.0;
	aCruiseSpeed = 0.0;
	aCruiseAltitude = 0.0;
}

// get functions
char* Aircraft::getMake(){
    return aMake;
};
char* Aircraft::getType(){
    return aType;
}
double Aircraft::getRateClimb(){
	return aRateClimb;
}
double Aircraft::getWingSpan(){
	return aWingSpan;
}
double Aircraft::getLength(){
	return aLength;
}
double Aircraft::getCruiseSpeed(){
	return aCruiseSpeed;
}
double Aircraft::getCruiseAltitude(){
	return aCruiseAltitude;
}
