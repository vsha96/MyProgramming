#include "runway.h"

Runway::Runway()
{
    _runwayID = -1;
    std::cout << "Runway: CONSTRUCTOR: " << "\n"
              << "\t_runwayID: " << _runwayID << std::endl;
    _onRunwayRequest = nullptr;
}

Runway::Runway(const int runwayID)
{
    _runwayID = runwayID;
    std::cout << "Runway: CONSTRUCTOR: " << "\n"
              << "\t_runwayID: " << _runwayID << std::endl;
    _onRunwayRequest = nullptr;
}

int Runway::runwayID() const
{
    return _runwayID;
}

int Runway::queueSize() const
{
    return _requests.size();
}

void Runway::setRunwayID(int newRunwayID)
{
    _runwayID = newRunwayID;
    std::cout << "Runway: setRunwayID: " << _runwayID << std::endl;
}

void Runway::tick(const SimTime worldTime)
{
    // here is a strategy how the runway chooses next flight request

    if (!isBusy()) {
        // taking request from queue
        if (_requests.size() > 0) {
            // watch ready time in the first request from queue
            FlightRequest* incomingRequest = _requests.front();
            if (incomingRequest->ready_time() <= worldTime) {
                // pass flight to the runway and set time
                _onRunwayRequest = incomingRequest;
                _onRunwayRequest->setOnRunwayTime(worldTime);

                // pop the request from the queue of runway
                deleteFirstFromQueue();

                // TEST show busy
                if (isBusy()) {
                    std::cout << "Runway " << _runwayID << " is busy" << std::endl;
                }
                std::cout << "Runway " << _runwayID << " is handling" << std::endl;
                std::cout << "\t";
                _onRunwayRequest->show();
            }
        }
    }

    if (isBusy()) {
        // handling current request
        SimTime on_runway_time = _onRunwayRequest->on_runway_time();
        SimTime duration_takeoff_landing = _onRunwayRequest->aiplane_type_time();

        if (on_runway_time + duration_takeoff_landing == worldTime) {

            // show status message
            std::cout << "Runway " << _runwayID << std::endl;
            std::cout << "\t" << _onRunwayRequest->flight();
            if (_onRunwayRequest->up_down() == "up") {
                std::cout << " took off!" << std::endl;
            } else if (_onRunwayRequest->up_down() == "down") {
                std::cout << " landed!" << std::endl;
            }

            _onRunwayRequest->setTakeoffLandingTime(worldTime);
            _onRunwayRequest->setHandled(true);
            _onRunwayRequest = nullptr;

            // TEST show busy
            if (!isBusy()) {
                std::cout << "Runway " << _runwayID << " is free" << std::endl;
            }
        }
    }

    // TODO place this in tick()
//    SimTime duration_takeoff_landing = newRequest->aiplane_type_time();

    /*
    // handle request
    if (_requests.size() > 0) {
//        std::cout << "!!!!!! " << _runwayID << std::endl;

        FlightRequest* currentRequest = _requests.front();

        if (currentRequest->real_time() == worldTime) {
            // pop the request from the queue of runway
            currentRequest->setHandled(true);
            _requests.pop();
            // show status message
            std::cout << "Runway " << _runwayID << std::endl;
            std::cout << "\t" << currentRequest->flight();
            if (currentRequest->up_down() == "up") {
                std::cout << " took off!" << std::endl;
            } else if (currentRequest->up_down() == "down") {
                std::cout << " landed!" << std::endl;
            }
        }
        // TODO here we must be busy or not
    }
    */
}

void Runway::acceptRequest(FlightRequest *newRequest)
{
    std::cout << "Runway: acceptRequest: \n\t";

    newRequest->setRunway_id(_runwayID);

    // computing ready time
    //  as planned_time + delay + takeoff_landing_time
    SimTime planned_time = newRequest->planned_time();
    SimTime delay = newRequest->delay_time();

    // setting ready time
    newRequest->setReadyTime(
        planned_time + delay
    );
    // show in test purposes
    newRequest->show();

    _requests.push(newRequest);
}

bool Runway::isBusy()
{
    return (_onRunwayRequest != nullptr);
}

std::string Runway::getInfoOnRunwayRequest()
{
    if (_onRunwayRequest) {
        return _onRunwayRequest->flight();
    } else {
        return "";
    }
}

void Runway::deleteFirstFromQueue()
{
    _requests.pop();
}
