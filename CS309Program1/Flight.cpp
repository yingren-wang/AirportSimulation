/*******************************************************
 *  Flight.cpp
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#include "Flight.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

Flight::Flight(){
	for(int n = 0; n < 32; n++){
        fAirline[n] = '0';
    }
	for(int n = 0; n < 32; n++){
        fPlaneType[n] = '0';
    }
	for(int n = 0; n < 4; n++){
		fDepartureCity[n] = '0';
    }
	for(int n = 0; n < 4; n++){
		fDestinationCity[n] = '0';
    }
	fFlightNumber = 0;
	fDepartureHour = 0;
	fDepartureMin = 0;
	
	fAircraftPtr = NULL;
	fDepartureCityPtr = NULL;
    fDestinationCityPtr = NULL;
    fElapsedHour = 0.0;
    fElapsedMin = 0.0;
    fStartHour = 0;
    fStartMin = 0;
	fCurrentHour = 0;
	fCurrentMin = 0;
    fDistBetweenCities = 0.0;
    fAircraftTripTime = 0.0;
    fDistFromStart = 0.0;
	fDistToEnd = 0.0;
	fCurLatitude = 0.0;
	fCurLongitude = 0.0;
	fCurAltitude = 0.0;
	fMACA = 0; // minutes to achieve cruise altitude
	fDeparture = NULL;
	fInAir = NULL;
	fLanded = NULL;
}

void Flight::update(){
    // update time
    fCurrentMin++;            // everytime update() gets called, a minute has past
    if(fCurrentMin == 60){
        fCurrentHour++;
        fCurrentMin = 0;
    }

    // update flight
	if(fDepartureHour == fCurrentHour && fDepartureMin == fCurrentMin){
        fDeparture = true;
        fInAir = true; // when it's time to departure and the flight hasn't depatured, depature
	}
	if(fInAir == true){
		fElapsedMin++;
		if(fElapsedMin == 60){
			fElapsedHour++;
			fElapsedMin = 0;
		}
        // start calculation
        setDistFromStart();
        setDistToEnd();
        setCurLatitude();
        setCurLongitude();
        setCurrentAltitude();
	}
    else if(fInAir == true && fDistToEnd == 0){
        fLanded = true;
        fInAir = false;
    }
}

// get functions
char* Flight::getAirline(){
    return fAirline;   
}
char* Flight::getPlaneType(){
    return fPlaneType;   
}
char* Flight::getDepartureCity(){
	return fDepartureCity;   
}
char* Flight::getDestinationCity(){
    return fDestinationCity;   
}
int Flight::getFlightNumber(){
	return fFlightNumber;
}
int Flight::getDepartureHour(){
	return fDepartureHour;
}
int Flight::getDepartureMin(){
	return fDepartureMin;
}


