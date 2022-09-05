#ifndef RUNWAY_H
#define RUNWAY_H

#include <iostream>
#include <queue>
#include <string>

#import "flight_request.h"

class Runway
{
public:
    Runway();
    Runway(const int runwayID);

    int runwayID() const;
    int queueSize() const;
    void setRunwayID(int newRunwayID);
    void tick(const SimTime worldTime);
    void acceptRequest(FlightRequest *newRequest);

    bool isBusy();
    std::string getInfoOnRunwayRequest();
private:
    void deleteFirstFromQueue();
private:
    int _runwayID;
    std::queue <FlightRequest*> _requests;
    FlightRequest* _onRunwayRequest; // request being processed
};

#endif // RUNWAY_H
