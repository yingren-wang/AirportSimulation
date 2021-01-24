/*******************************************************
 *  City.cpp
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#include "City.h"
#include <iomanip>

// constructor
City::City(){
    for(int n = 0; n < 32; n++){
        cName[n] = '0';
    }
    for(int n = 0; n < 32; n++){
        cState[n] = '0';
    }
    for(int n = 0; n < 32; n++){
        cSymbol[n] = '0';
    }
    cLatitude = 0.0;
    cLongitude = 0.0;
    cSymbolIndex = 0;
}

// get functions
char* City::getName(){
    return cName;   
}
char* City::getState(){
    return cState;
};
char* City::getSymbol(){
    return cSymbol;
}
double City::getLatitude(){
	return cLatitude;
}
double City::getLongitude(){
	return cLongitude;
}
int City::getSymbolIndex(){
    return cSymbolIndex;
}
