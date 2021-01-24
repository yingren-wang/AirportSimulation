/*******************************************************
 *  Flight.h
 *  Programming Assignment 1 Airline Simulation
 *  Author: Yingren Wang
 *  Date: July 3, 2019
 *
 *  This program is entirely my own work
 ********************************************************/

#ifndef Flight_h
#define Flight_h

#include <stdio.h>
#include <string>
#include "Aircraft.h"
#include "City.h"


using namespace std;

class Flight
{
    char fAirline[32];
    char fPlaneType[32];
    int fFlightNumber;
    char fDepartureCity[4];
    int fDepartureHour;
    int fDepartureMin;
    char fDestinationCity[4];
    
    Aircraft *fAircraftPtr;
    City *fDepartureCityPtr;
    City *fDestinationCityPtr;
    double fElapsedHour;
    double fElapsedMin;
    int fStartHour;
    int fStartMin;
	int fCurrentHour;
	int fCurrentMin;
	int fArrivalHour;
	int fArrivalMin;
    double fDistBetweenCities;
    double fAircraftTripTime;
    double fDistFromStart;
    double fDistToEnd;
    double fCurLatitude;
    double fCurLongitude;
	double fCurAltitude;
	int fMACA; // minutes to achieve cruise altitude
	bool fDeparture;
    bool fInAir;
    bool fLanded;
    
public:
    Flight();
    void update();
    
    // set functions
    void setAirline(char *ptr){
        strcpy(fAirline, ptr);
    };
    void setPlaneType(char *ptr){
        strcpy(fPlaneType, ptr);
    };
    void setFlightNumber(int flightNumber)
    {fFlightNumber = flightNumber;};
    void setDepartureCity(char *ptr){
        strcpy(fDepartureCity, ptr);
    };
    void setDepartureHour(int departureHour)
    {fDepartureHour = departureHour;};
    void setDepartureMin(int departureMin)
    {fDepartureMin = departureMin;};
    void setDestinationCity(char *ptr){
        strcpy(fDestinationCity, ptr);
    };

	void setAircraftPtr(Aircraft* ptr){
        fAircraftPtr = ptr;
    };
	void setDepartureCityPtr(City* ptr){
        fDepartureCityPtr = ptr;
    };
	void setDestinationCityPtr(City* ptr){
        fDestinationCityPtr = ptr;
    };

    void setAircraftTripTime(){
        fAircraftTripTime = fDistBetweenCities/(fAircraftPtr -> getCruiseSpeed());
    };
    void setDistFromStart(){
        fDistFromStart = (fElapsedHour/fAircraftTripTime) * fDistBetweenCities;
    };
    void setDistToEnd(){
        fDistToEnd = fDistBetweenCities - fDistFromStart;
    };
	void setCurLatitude(){
		fCurLatitude = (fDepartureCityPtr -> getLatitude()) + ((fDestinationCityPtr -> getLatitude()) - (fDepartureCityPtr -> getLatitude())) * (fElapsedHour/fAircraftTripTime);
	};
	void setCurLongitude(){
        fCurLongitude = fDepartureCityPtr -> getLongitude() + (fDestinationCityPtr -> getLongitude() - fDepartureCityPtr -> getLongitude()) * (fElapsedHour/fAircraftTripTime);
	};
	void setCurrentAltitude(){
		if(fAircraftTripTime <= fMACA * 2){
			if(fElapsedMin + fElapsedHour * 60 <= fMACA){
				fCurAltitude = fElapsedMin * (fAircraftPtr -> getRateClimb());
			}
			else{
				fCurAltitude -= fElapsedMin * (fAircraftPtr -> getRateClimb());
			}
		}
		else{
			if(fElapsedMin + fElapsedHour * 60 < fMACA){
				fCurAltitude = fElapsedMin * (fAircraftPtr -> getRateClimb());
			}
			else if(fElapsedMin + fElapsedHour * 60 >= fMACA && fElapsedMin + fElapsedHour * 60 <=  fAircraftTripTime - fMACA){
				fCurAltitude = fAircraftPtr -> getCruiseAltitude();
			}
			else
			{
				fCurAltitude -= fElapsedMin * (fAircraftPtr -> getRateClimb());
			}
		}
	};
    void setMACA(){
		fMACA = fAircraftPtr -> getCruiseAltitude() / (fAircraftPtr -> getCruiseSpeed() / 60.0 * 5280.0);
	};
    void setStartTime(int startHour, int startMin){
        fStartHour = startHour;
        fStartMin = startMin;
    };
	void setCurrentTime(int currentHour, int currentMin){
		fCurrentHour = currentHour;
		fCurrentMin = currentMin;
	};
	void setArrivalTime(){
		fArrivalMin = fDepartureMin + (fAircraftTripTime * 60);
		fArrivalHour = fDepartureHour;
		while(fArrivalMin >= 60){
			fArrivalHour++;
			fArrivalMin = fArrivalMin - 60;
		}
	};
    void setDistanceBetweenCities(double distBetweenCities){
        fDistBetweenCities = distBetweenCities;
    };
    void setDeparture(bool departure){
        fDeparture = departure;
    };
    void setInAir(bool inAir){
        fInAir = inAir;
    };
    void setLanded(bool landed){
        fLanded = landed;
    };

    void setAll(char *airline, char *planeType, int flightNumber, char *departureCity, int departureHour, int departureMin, char *destinationCity){
        strcpy(fAirline, airline);
        strcpy(fDepartureCity, departureCity);
        strcpy(fDestinationCity, destinationCity);
        strcpy(fPlaneType, planeType);
        fFlightNumber = flightNumber;
        fDepartureHour = departureHour;
        fDepartureMin = departureMin;
    }
    
    // get funtions
    char* getAirline();
    char* getPlaneType();
    int getFlightNumber();
    char* getDepartureCity();
    int getDepartureHour();
    int getDepartureMin();
    char* getDestinationCity();
    // TO DO: get functions for every private variable
    Aircraft* getAircraftPtr(){
        return fAircraftPtr;
    };
    City* getDestinationCityPtr(){
        return fDestinationCityPtr;
    };
    City* getDepartureCityPtr(){
        return fDepartureCityPtr;
    };
    double getElapsedHour(){
        return fElapsedHour;
    };
    double getElapsedMin(){
        return fElapsedMin;
    };
    int getStartHour(){
        return fStartHour;
    };
    int getStartMin(){
        return fStartMin;
    };
	int getCurrentHour(){
		return fCurrentHour;
	};
	int getCurrentMin(){
		return fCurrentMin;
	};
	int getArrivalHour(){
		return fArrivalHour;
	}
	int getArrivalMin(){
		return fArrivalMin;
	}
    double getDistBetweenCities(){
        return fDistBetweenCities;
    };
    double getAircraftTripTime(){
        return fAircraftTripTime;
    };
    double getDistFromStart(){
        return fDistFromStart;
    };
    double getDistToEnd(){
        return fDistToEnd;
    };
    double getCurLatitude(){
        return fCurLatitude;
    };
    double getCurLongitude(){
        return fCurLongitude;
    };
    double getCurAltitude(){
        return fCurLongitude;
    };
    int getMACA(){
        return fMACA;
    };
    bool getDeparture(){
        return fDeparture;
    };
    bool getInAir(){
        return fInAir;
    };
    bool getLanded(){
        return fLanded;
    };
};

#endif /* Flight_h */
