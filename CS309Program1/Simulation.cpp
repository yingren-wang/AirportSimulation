/*******************************************************
*  Simulation.cpp
*  Programming Assignment 1 Airline Simulation
*  Author: Yingren Wang
*  Date: July 3, 2019
*
*  This program is entirely my own work
********************************************************/

#include "Simulation.h"

#include <iomanip>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>

#include <sys/types.h>     // needed for the _ftime() function
#include <sys/timeb.h>     // contains definition of _timeb struct
#include <time.h>          // needed for other time functions and structures


using namespace std;

Simulation::Simulation(){
    // initialize vectors
    for(int i = 0; i < sCityVector.size(); i++){
        sCityVector[i] = NULL;
    }
    for(int i = 0; i < sAircraftVector.size(); i++){
        sAircraftVector[i] = NULL;
    }
    for(int i = 0; i < sFlightVector.size(); i++){
        sFlightVector[i] = NULL;
    }
	for(int i = 0; i < sInAirFlightVector.size(); i++){
        sInAirFlightVector[i] = NULL;
    }
		// welcome
	cout << 
		"========================================================================\n" <<
		"|		AIRLINE FLIGHT SIMULATION DEMONSTRATION			|\n" <<
		"|		  CS 307 -- Programming Assignment 1			|\n" <<
		"========================================================================\n" <<
		endl;

    // prompt user for file name
    string dataFileName = "";
    // prompt user for name of the data file
    cout << "Please enter the name of the simulation data file then press Enter:" << endl;
    // get the data file name
    cin >> dataFileName;

	ifstream infile;
	infile.open(dataFileName);
	if(!infile){
		cout << "The input file can't be opened successfully." << endl;
		exit(1);
	}

	char fileName1[32];
	char fileName2[32];
	
	infile >> fileName1 >> fileName2;
	
	char *fileName1Ptr = fileName1;
    char *fileName2Ptr = fileName2;
	
	// do what so that I can have two dataFileNames?

	cout << "At what speed do you want to run the simulation? (1x, 2x, 3x)\n" << "	Please enter 1, 2, or 3 and press Enter." << endl;
	cin >> sSpeed;
    
    CityDataParser cityDataParser;
    FlightDataParser flightDataParser;
    
    // initiate city data
    cityDataParser.InitCityData(fileName1Ptr);
	// initiate flight data
	flightDataParser.InitFlightData(fileName2Ptr);
    // get city count
    sCityCount = cityDataParser.getCityCount();
    
    // get symbols array
    char **symbols;
    cityDataParser.getCitySymbolsArray(&symbols);

    // get all the cities' data and put them in a city vector
    for(int i = 0; i < sCityCount; i++){
        City *city = new City;
        char cName[32];
        char cState[32];
        char cSymbol[32];
        double lat;
        double lon;
        int index;
        // get info of a city
        cityDataParser.getCityData(cName, cState, cSymbol, &lat, &lon);
        // use the set function to set the info of the city
        city -> setAll(cName, cState, cSymbol, lat, lon);
        sCityVector.push_back(city);
        // check the symbols so that the City can know its own symbol index
        for(int j = 0; j < sCityCount; j++){
            if(strcmp(cSymbol, symbols[j]) == 0){ // if cSymbol is the same as symbols[j], found the symbol index
                index = j;
                city -> setIndex(index);
				break;
            }
        }
    }
    
    int sAircraftCount = flightDataParser.getAircraftCount();
    for(int i = 0; i < sAircraftCount; i++){
        Aircraft *aircraft = new Aircraft;
        //get aircraft data
        char aMake[32];
        char aType[32];
        double rateOfClimb;
        double wingspan;
        double length;
        double cruiseSpeed;
        double cruiseAlt;
        flightDataParser.getAircraftData(aMake, aType, &rateOfClimb, &wingspan, &length, &cruiseSpeed, &cruiseAlt);
        aircraft -> setAll(aMake, aType, rateOfClimb, wingspan, length, cruiseSpeed, cruiseAlt);
        sAircraftVector.push_back(aircraft);
    }

	// get distance table
	double *distances;
	cityDataParser.getDistTable(&distances);

	// get start time
	int hour;
	int minute;
	flightDataParser.getStartTime(&hour, &minute);

	// get counts

	sFlightCount = flightDataParser.getFlightCount();
    for(int i = 0; i < sFlightCount; i++){
        Flight *flight = new Flight;
        // get flight data
        char airline[32];
        char planeType[32];
        int flightNumber;
        char departureCity[4];
        int departureHour;
        int departureMin;
        char destinationCity[4];
        flightDataParser.getFlightData(airline, planeType, &flightNumber, departureCity, &departureHour, &departureMin, destinationCity);
        flight -> setAll(airline, planeType, flightNumber, departureCity, departureHour, departureMin, destinationCity);
        // get distance between cities
		for(int i = 0; i < sAircraftCount; i++){
			if(strcmp(planeType, sAircraftVector[i] -> getMake()) == 0){
				flight -> setAircraftPtr(sAircraftVector[i]);
			}
		}

        int index1, index2;
        for(int i = 0; i < sCityCount; i++){
            if(strcmp(departureCity, sCityVector[i] -> getSymbol()) == 0){
                index1 = sCityVector[i] -> getSymbolIndex();
				flight -> setDepartureCityPtr(sCityVector[i]);
            }
            if(strcmp(destinationCity, sCityVector[i] -> getSymbol()) == 0){
                index2 = sCityVector[i] -> getSymbolIndex();
				flight -> setDestinationCityPtr(sCityVector[i]);
            }
        }
        double distanceBetweenCities;
        distanceBetweenCities = distances[index1 * sCityCount + index2];
        flight -> setDistanceBetweenCities(distanceBetweenCities);
		flight -> setAircraftTripTime();
		flight -> setMACA();
		int startHour;
        int startMin;
        flightDataParser.getStartTime(&startHour, &startMin);
        flight -> setStartTime(startHour, startMin);
		flight -> setCurrentTime(startHour, startMin);
		flight -> setArrivalTime();

		
        sFlightVector.push_back(flight);
    }
};


// function for output to the screen
void Simulation::output(){

	for(int i = 0; i < sFlightCount; i++){
		if(sFlightVector[i] -> getDeparture() == true){
			// print out departure information
			cout << 
				"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<
				"\nNow departing: " << sFlightVector[i] -> getAirline() << " flight " << sFlightVector[i] -> getFlightNumber() << ", " << sFlightVector[i] -> getPlaneType() << "\n	From " << 
				sFlightVector[i] -> getDepartureCityPtr() -> getName() << ", " << sFlightVector[i] -> getDepartureCityPtr() -> getState() << "\n		enroute to " <<
				sFlightVector[i] -> getDestinationCityPtr() -> getName() << ", " << sFlightVector[i] -> getDestinationCityPtr() -> getState() << "\n	Estimated Time of Arrival: ";
				printf("%02d:%02d\n", sFlightVector[i] -> getArrivalHour(), sFlightVector[i]-> getArrivalMin());
				printf("Current clock time: %02d:%02d\n", sFlightVector[0] -> getCurrentHour(), sFlightVector[0]-> getCurrentMin());
				cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
		}	
	}
	for(int i = 0; i < sFlightCount; i++){
		if(sFlightVector[i] -> getInAir() == true){
			cout << sFlightVector[i] -> getAirline() << " Airlines FLight " << sFlightVector[i] -> getFlightNumber() << " - " << sFlightVector[i] -> getPlaneType() <<
				endl << "	Departs: " << sFlightVector[i] -> getDepartureCity() << " (" << sFlightVector[i] -> getDepartureCityPtr() -> getLatitude() << ", " << sFlightVector[i] -> getDepartureCityPtr() -> getLongitude() <<
				") at ";
			printf("%02d:%02d\n", sFlightVector[i] -> getDepartureHour(), sFlightVector[i]-> getDepartureMin());
			cout << "	Arrives: " << sFlightVector[i] -> getDestinationCity() << " (" << sFlightVector[i] -> getDestinationCityPtr() -> getLatitude() << ", " << sFlightVector[i] -> getDestinationCityPtr() -> getLongitude() <<
				") at ";
			printf("%02d:%02d\n", sFlightVector[i] -> getArrivalHour(), sFlightVector[i]-> getArrivalMin());
			cout << "	Current location: " << " (" << sFlightVector[i] -> getCurLatitude() << ", " << sFlightVector[i] -> getCurLongitude() << ")\n" << "		" << sFlightVector[i] -> getDistFromStart() << " miles from " << sFlightVector[i] -> getDepartureCity() <<
				", " << sFlightVector[i] -> getDistToEnd() << " miles to " << sFlightVector[i] -> getDestinationCity() << "\n" << "	Current speed: " << sFlightVector[i] -> getAircraftPtr() -> getCruiseSpeed() << " MPH\n" << "	Current altitude: " <<
				sFlightVector[i] -> getCurAltitude() << " feet\n";
		}
	}
}

void Simulation::runSimulation(){

    // timer starting from here
    struct _timeb   tStruct;
    double          thisTime;
    double          outputTime;
    double          updateTime;
    bool            done = false;  // while loop flag
    
    _ftime(&tStruct);    // Get start time
    thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
    updateTime = thisTime + 1.0 / sSpeed;
    outputTime = thisTime + 5.0; // Set next 5 second interval time

	// start simulation time output
	printf("\n*** Starting simulation at %02d:%02d ***\n\n\n\n", sFlightVector[0] -> getStartHour(), sFlightVector[0] -> getStartMin());
	// TODO: find what time is considered as starting time here

	int finishedCount = 0;
	while(finishedCount != sFlightVector.size())     // Start an eternal loop
    {
        _ftime(&tStruct);    // Get the current time
        thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
		if(thisTime >= updateTime){
			// if it's the update time, every flight in the flight vector should check departure time and update if it is the time
            updateTime += 1.0 / sSpeed;
            for(int i = 0; i < sFlightVector.size(); i++){
                sFlightVector[i] -> update();
				if(sFlightVector[i] -> getLanded() == true){
					finishedCount++;
				}
            }
        }
        // Check for 5 second interval to print status to screen
        if(thisTime >= outputTime)
        {
		cout << 
			"========================================================================\n" <<
			"|	Flight Simulation - Status report on all flights enroute	|\n" <<
			"========================================================================\n";
		printf("Current clock time: %02d:%02d\n\n", sFlightVector[0] -> getCurrentHour(), sFlightVector[0]-> getCurrentMin());
            // Call functions to perform actions at 5 second intervals
			output();
            outputTime += 5.0; // Set time for next 5 second interval
        }
    }
    // timer ends here
}

Simulation::~Simulation(){};
