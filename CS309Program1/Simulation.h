/*******************************************************
 *  Simulation.h
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#ifndef Simulation_h
#define Simulation_h

#include <stdio.h>
#include <vector>

#include "CityDataParser.h"
#include "FlightDataParser.h"

#include "Aircraft.h"
#include "City.h"
#include "Flight.h"

#endif /* Simulation_hpp */

class Simulation
{
    // have vector as private variable so that other classes can access to these info too
    vector<City*> sCityVector;
    vector<Aircraft*> sAircraftVector;
    vector<Flight*> sFlightVector;
	vector<Flight*> sInAirFlightVector;
	int sSpeed;
	int sAircraftCount;
	int sFlightCount;
	int sCityCount;
    
public:
    Simulation();
    void runSimulation();
    ~Simulation();

	void output();
    
    // set functions
    void setCityVector(vector<City*> cityVec){
        cityVec = sCityVector;
    };
    void setAircraftVector(vector<Aircraft*> aircraftVec){
        aircraftVec = sAircraftVector;
    };
    void setFlightVector(vector<Flight*> flightVec){
        flightVec = sFlightVector;
    };
	void setInAirFlightVector(vector<Flight*> inAirFlightVec){
        inAirFlightVec = sInAirFlightVector;
    };
    
    // get functions
    vector<City*> getCityVector(){
        return sCityVector;
    };
    vector<Aircraft*> getAircraftVector(){
        return sAircraftVector;
    };
    vector<Flight*> getFlightVector(){
        return sFlightVector;
    };
	vector<Flight*> getInAirFlightVector(){
        return sInAirFlightVector;
    };
    
};
