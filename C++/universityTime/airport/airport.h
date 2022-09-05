#ifndef AIRPORT_H
#define AIRPORT_H

#include "runway.h"
#include "flight_request.h"
#include <vector>

class Airport
{

public:
    Airport(const int numberOfRunways);

    void handleRequest(FlightRequest* request);
    void tick(const SimTime worldTime);

    // statistics
    int statMaxRequestNumberOnRunway() const;
    float statAverageRequestNumberOnRunway() const;
    float statAverageNumberBusyRunway() const;

    // for visual info
    std::vector<Runway*> getRunways() const;
private:
    std::vector<Runway*> _runways;
};

#endif // AIRPORT_H
