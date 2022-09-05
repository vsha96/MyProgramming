#include "airport.h"

Airport::Airport(const int numberOfRunways)
{
    _runways.resize(numberOfRunways);

    std::cout << "Airport: CONSTRUCTOR: " << "\n"
              << "\tnumber of runways: " << _runways.size() << std::endl;

    for (size_t i=0; i < _runways.size(); i++) {
        _runways[i] = new Runway(i);
    }

}

void Airport::handleRequest(FlightRequest *request)
{
    std::cout << "Airport: handleRequest: \n\t";
    request->show();

    // here is a strategy how we deal with requests
    //  if we want more complex strat
    //  we may need worldTime from FlightControlSystem

    // we are sending request to the runway with
    //  minimum queue size
    size_t indexMin = 0;
    int min = _runways[indexMin]->queueSize();
    for (size_t i=0; i<_runways.size(); i++) {
        if (min > _runways[i]->queueSize()) {
            indexMin = i;
            min = _runways[indexMin]->queueSize();
        }
    }
    // send request to the runway
    _runways[indexMin]->acceptRequest(request);
}

void Airport::tick(const SimTime worldTime)
{
    for (size_t i=0; i < _runways.size(); i++) {
        _runways[i]->tick(worldTime);
    }
}

int Airport::statMaxRequestNumberOnRunway() const
{
    int max = _runways[0]->queueSize();
    int t = 0;
    for (size_t i=0; i<_runways.size(); i++) {
        t = _runways[i]->queueSize();
        if (max < t) {
            max = t;
        }
    }
    return max;
}

float Airport::statAverageRequestNumberOnRunway() const
{
    int sum = 0;
    int n = 0;
    int t = 0;
    for (size_t i=0; i<_runways.size(); i++) {
        t = _runways[i]->queueSize();
        if (t) {
            sum += t;
            n++;
        }

    }

    if (n) {
        return sum / n;
    } else {
        return 0;
    }
}

float Airport::statAverageNumberBusyRunway() const
{
    int n = 0;
    for (size_t i=0; i<_runways.size(); i++) {
        if (_runways[i]->isBusy()) {
            n++;
        }
    }
    return n / _runways.size();
}

std::vector<Runway *> Airport::getRunways() const
{
    std::vector<Runway*> result;
    result = _runways;
    return result;
}
