/*******************************************************
 *  City.h
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#ifndef City_h
#define City_h

#include <stdio.h>
#include <string>

using namespace std;

class City
{
    char cName[32];
    char cState[32];
    char cSymbol[32];
    double cLatitude;
    double cLongitude;
    int cSymbolIndex;
    
public:
    // Constructor
    City();
    
    // set functions
    // use strcpy functions to set the name
    void setName(char *ptr){
        strcpy(cName, ptr);
    };
    void setState(char *ptr){
        strcpy(cState, ptr);
    };
    void setSymbol(char *ptr){
        strcpy(cSymbol, ptr);
    };
    void setLatitude(double latitude){
        cLatitude = latitude;
        
    };
    void setLongitude(double longitude){
        cLongitude = longitude;
    };
    void setIndex(int index){
        cSymbolIndex = index;
    }
    
    void setAll(char *name, char *state, char *symbol, double latitude, double longitude){
        strcpy(cName, name);
        strcpy(cState, state);
        strcpy(cSymbol, symbol);
        cLatitude = latitude;
        cLongitude = longitude;
    }
    
    // get functions
    char* getName();
    char* getState();
    char* getSymbol();
    double getLatitude();
    double getLongitude();
    int getSymbolIndex();
};

#endif /* City_h */
