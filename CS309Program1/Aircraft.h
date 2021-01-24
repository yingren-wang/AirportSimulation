/*******************************************************
 *  Aircraft.h
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#ifndef Aircraft_h
#define Aircraft_h

#include <stdio.h>
#include <string>

using namespace std;

class Aircraft
{
    char aMake[32];
	char aType[32];
    double aRateClimb;
    double aWingSpan;
    double aLength;
    double aCruiseSpeed;
    double aCruiseAltitude;
    
public:
    Aircraft();
    
    // set functions
    void setMake(char *ptr){
        strcpy(aMake, ptr);
    }
    void setType(char *ptr){
        strcpy(aType, ptr);
    }
    void setRateClimb(double rateClimb)
    {aRateClimb = rateClimb;};
    void setWingSpan(double wingSpan)
    {aWingSpan = wingSpan;};
    void setLength(double length)
    {aLength = length;};
    void setCruiseSpeed(double cruiseSpeed)
    {aCruiseSpeed = cruiseSpeed;};
    void setCruiseAltitude(double cruiseAltitude)
    {aCruiseAltitude = cruiseAltitude;};
    
    void setAll(char *make, char *type, double rateClimb, double wingSpan, double length, double cruiseSpeed, double cruiseAltitude){
        strcpy(aMake, make);
        strcpy(aType, type);
        aRateClimb = rateClimb;
        aWingSpan = wingSpan;
        aLength = length;
        aCruiseSpeed = cruiseSpeed;
        aCruiseAltitude = cruiseAltitude;
    };
    
    // get functions
    char* getMake();
	char* getType();
    double getRateClimb();
    double getWingSpan();
    double getLength();
    double getCruiseSpeed();
    double getCruiseAltitude();
};

#endif /* Aircraft_h */
