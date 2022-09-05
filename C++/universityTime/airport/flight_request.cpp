#include "flight_request.h"

FlightRequest::FlightRequest(std::string flight, AirplaneType airplane_type, std::string up_down, SimTime planned_time)
{
    _flight = flight;
    _airplane_type = airplane_type;
    _up_down = up_down;
    _planned_time = planned_time;
    _delay_time = SimTime(0,0,0);
    _ready_time = SimTime(0,0,0);
    _on_runway_time = SimTime(0,0,0);
    _takeoff_landing_time = SimTime(0,0,0);
    _runway_id = -1;
    _handled = false;
}

void FlightRequest::show()
{
    std::cout << _flight << " | "
              << _airplane_type << " | "
              << _up_down << " | "
              << _planned_time.toString() << " | "
              << "+" << _delay_time.toString() << " | "
              << _ready_time.toString() << " | "
              << _on_runway_time.toString() << " | "
              << _takeoff_landing_time.toString() << " | "
              << _runway_id << " | "
              << _handled
              << std::endl;
}

std::string FlightRequest::getInfo()
{
    if (!handled()) {
        return _flight + "|" + _planned_time.toString();
    } else {
        return _flight + "|" + _planned_time.toString() + "|" + _takeoff_landing_time.toString();
    }
}

const SimTime &FlightRequest::planned_time() const
{
    return _planned_time;
}

void FlightRequest::setRunway_id(int newRunway_id)
{
    _runway_id = newRunway_id;
}

void FlightRequest::setDelayTime(const SimTime &newDelay_time)
{
    _delay_time = newDelay_time;
}

void FlightRequest::setReadyTime(const SimTime &ready_time)
{
    _ready_time = ready_time;
}

//AirplaneType FlightRequest::airplane_type() const
//{
//    return _airplane_type;
//}

const SimTime &FlightRequest::delay_time() const
{
    return _delay_time;
}

const SimTime &FlightRequest::ready_time() const
{
    return _ready_time;
}

const SimTime FlightRequest::aiplane_type_time()
{
    switch (_airplane_type) {
    case airplane1:
        return SimTime(5,0,0);
        break;
    case airplane2:
        return SimTime(10,0,0);
        break;
    case airplane3:
        return SimTime(15,0,0);
        break;
    }
}

const std::string &FlightRequest::flight() const
{
    return _flight;
}

const std::string &FlightRequest::up_down() const
{
    return _up_down;
}

void FlightRequest::setHandled(bool newHandled)
{
    _handled = newHandled;
}

bool FlightRequest::handled() const
{
    return _handled;
}

const SimTime &FlightRequest::on_runway_time() const
{
    return _on_runway_time;
}

const SimTime &FlightRequest::takeoff_landing_time() const
{
    return _takeoff_landing_time;
}

void FlightRequest::setTakeoffLandingTime(const SimTime &new_takeoff_landing_time)
{
    _takeoff_landing_time = new_takeoff_landing_time;
}

void FlightRequest::setOnRunwayTime(const SimTime &new_on_runway_time)
{
    _on_runway_time = new_on_runway_time;
}
