#ifndef FLIGHTCONTROLSYSTEM_H
#define FLIGHTCONTROLSYSTEM_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <random>

#include "airport.h"
#include "flight_request.h"
#include "csv.h"

#define TIMETABLE_ABSOLUTE_PATH "/Users/vsha96/git_repos/airport/timetable.csv"
#define MAXDELAY_MIN 10
#define MAXDELAY_HOUR 0
#define MAXDELAY_DAY 0

class FlightControlSystem
{
    SimTime generateDelay();
    void readTimetable();

    // TODO: statistics
    void computeStat();
public:
    FlightControlSystem(const int runwaysNumber, const SimTime maxDelayTime, const SimTime timeStep);
    void initSimulation();
    void stopSimulation(); // TODO save timetable
    void restartSimulation(); // ? TODO

    // appEngine triggers it
    void tick();

    void showTimetable();
    void showTimetableHandled();

    // statistics
    int statNumberRequestsHandled() const;
    int statMaxActualDelay() const;
    float statAverageActualDelay() const;
    int statMaxRequestNumberOnRunway() const;
    float statAverageRequestNumberOnRunway() const;
    float statAverageNumberBusyRunway() const;

    // for visual info
    std::vector<Runway*> getRunways() const;
    std::vector<FlightRequest*> getAllRequests() const;
private:
    int _numberOfRunways;
    // timetable file
    std::string _timetableFileName;

    std::queue<FlightRequest*>  _requests;
    std::queue<FlightRequest*>  _requestsHandled;
    std::vector<FlightRequest*> _requestsHandledVector;
    std::vector<FlightRequest*> _timetableVector; // there are all requests

    // time
    SimTime _maxDelay;
    SimTime _worldTime;
    SimTime _timeStep;

    Airport *_airport;

    // TODO: statistics
    int _statNumberRequestsHandled;
    int _statMaxActualDelay; // in minutes
    float _statAverageActualDelay; // in minutes
    int _statMaxRequestNumberOnRunway;
    float _statAverageRequestNumberOnRunway;
    float _statAverageNumberBusyRunway;
};

#endif // FLIGHTCONTROLSYSTEM_H
