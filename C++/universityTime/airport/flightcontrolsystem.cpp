#include "flightcontrolsystem.h"

FlightControlSystem::FlightControlSystem(
    const int runwaysNumber,
    const SimTime maxDelayTime,
    const SimTime timeStep
)
{
    _numberOfRunways = runwaysNumber;
    _timetableFileName = TIMETABLE_ABSOLUTE_PATH;
    _maxDelay = maxDelayTime;
    _worldTime = SimTime(0, 0, 0);
    _timeStep = timeStep;
    std::cout << "FlightControlSystem: CONSTRUCTOR: " << "\n"
              << "\tnumberOfRunways: " << _numberOfRunways << "\n"
              << "\ttimetableFileName: " << _timetableFileName << "\n"
              << "\tworldTime: "
                    << _worldTime.day << " days "
                    << _worldTime.hour << ":"
                    << _worldTime.min << "\n"
              << "\ttimeStep: "
                    << _timeStep.day << " days "
                    << _timeStep.hour << ":"
                    << _timeStep.min << std::endl;
    _statNumberRequestsHandled = 0;
    _statMaxActualDelay = 0; // in minutes
    _statAverageActualDelay = 0; // in minutes
    _statMaxRequestNumberOnRunway = 0;
    _statAverageRequestNumberOnRunway = 0;
    _statAverageNumberBusyRunway = 0;
}

void FlightControlSystem::initSimulation()
{
    std::cout << "FlightControlSystem: initSimulation(): creating airport..." << std::endl;
    _airport = new Airport(_numberOfRunways);


    std::cout << "FlightControlSystem: initSimulation(): reading csv..."
              << std::endl;

    readTimetable();

    // show parsed data
    showTimetable();

    std::cout << "FlightControlSystem: initSimulation(): init completed"
              << std::endl;
}

void FlightControlSystem::tick()
{
    _worldTime.tick();
    std::cout << _worldTime.toString() << std::endl;

    while (
        !_requests.empty() &&
        (_worldTime == _requests.front()->planned_time())
    ) {
        FlightRequest* newRequest = _requests.front();
        _requests.pop();

        // generate random delay for request
        newRequest->setDelayTime(generateDelay());

        // sending request to airport
        _airport->handleRequest(newRequest);

        _requestsHandled.push(newRequest);
        _requestsHandledVector.push_back(newRequest);
//        std::cout << "#### " << _requestsHandledVector.size() << std::endl;
    }

    _airport->tick(_worldTime);

    computeStat();
}

void FlightControlSystem::showTimetable()
{
    std::cout << "FlightControlSystem: showTimetable" << std::endl;

    std::queue<FlightRequest*> temp_queue(_requests);

    int i=1;
    while (!temp_queue.empty()) {
        std::cout << i << "\t";
        temp_queue.front()->show();
        i++;
        temp_queue.pop();
    }
}

void FlightControlSystem::showTimetableHandled()
{
    std::cout << "FlightControlSystem: showTimetableHandled" << std::endl;

    std::queue<FlightRequest*> temp_queue(_requestsHandled);

    int i=1;
    while (!temp_queue.empty()) {
        std::cout << i << "\t";
        temp_queue.front()->show();
        i++;
        temp_queue.pop();
    }
}

SimTime FlightControlSystem::generateDelay()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, _maxDelay.mins());

    return SimTime(distr(eng));
}

void FlightControlSystem::readTimetable()
{
    // init reading csv file
    io::CSVReader<4> csvReader(_timetableFileName);
    csvReader.read_header(
        io::ignore_extra_column,
        "flight",
        "airplane_type",
        "up/down",
        "planned_time"
//        "delay_time",
//        "ready_time",
//        "on_runway_time",
//        "takeoff/landing_time",
//        "runwayID",
//        "handled"
    );
    std::string flight;
    int airplane_type;
    std::string up_down;
    std::string planned_time; // convert this to SimTime

    // read csv file
    while(csvReader.read_row(flight, airplane_type, up_down, planned_time)) {
        // print row of csv
        std::cout << flight << " | "
                  << airplane_type << " | "
                  << up_down << " | "
                  << planned_time << std::endl;
        // create a request in queue
        FlightRequest* new_request = new FlightRequest(
            flight,
            static_cast<AirplaneType>(airplane_type),
            up_down,
            SimTime(planned_time)
        );
        _requests.push(new_request);
        _timetableVector.push_back(new_request);
    }
}

void FlightControlSystem::computeStat()
{

    _statNumberRequestsHandled = 0;
    for (size_t i=0; i < _requestsHandledVector.size(); i++) {
        if (_requestsHandledVector[i]->handled()) {
            _statNumberRequestsHandled += 1;
        }
    }

//    _statMaxActualDelay = 0; // in minutes
    if (_requestsHandledVector.size()) {
        int t = 0;
        _statMaxActualDelay = (_requestsHandledVector[0]->on_runway_time()
                - _requestsHandledVector[0]->ready_time()).mins();

        for (size_t i=0; i < _requestsHandledVector.size(); i++) {
            if (_requestsHandledVector[i]->handled())  {
                t = (_requestsHandledVector[i]->on_runway_time()
                     - _requestsHandledVector[i]->ready_time()).mins();
                if (_statMaxActualDelay < t) {
                    _statMaxActualDelay = t;
                }
            }
        }
    }

//    _statAverageActualDelay = 0; // in minutes
    _statAverageActualDelay = 0;
    int n = 0;
    for (size_t i=0; i < _requestsHandledVector.size(); i++) {
        if (_requestsHandledVector[i]->handled())  {
            _statAverageActualDelay += (_requestsHandledVector[i]->on_runway_time()
                 - _requestsHandledVector[i]->ready_time()).mins();
            n++;
        }
    }
    if (n) {
        _statAverageActualDelay /= n;
    }

    _statMaxRequestNumberOnRunway = _airport->statMaxRequestNumberOnRunway();

    _statAverageRequestNumberOnRunway = _airport->statAverageRequestNumberOnRunway();

    _statAverageNumberBusyRunway = _airport->statAverageNumberBusyRunway();
}

float FlightControlSystem::statAverageRequestNumberOnRunway() const
{
    return _statAverageRequestNumberOnRunway;
}

float FlightControlSystem::statAverageNumberBusyRunway() const
{
    return _statAverageNumberBusyRunway;
}

std::vector<Runway *> FlightControlSystem::getRunways() const
{
    if (_airport) {
        return _airport->getRunways();
    } else {
        return {};
    }
}

std::vector<FlightRequest *> FlightControlSystem::getAllRequests() const
{
    std::vector<FlightRequest*> result;
    result = _timetableVector;
    return result;
}

int FlightControlSystem::statMaxRequestNumberOnRunway() const
{
    return _statMaxRequestNumberOnRunway;
}

float FlightControlSystem::statAverageActualDelay() const
{
    return _statAverageActualDelay;
}

int FlightControlSystem::statMaxActualDelay() const
{
    return _statMaxActualDelay;
}

int FlightControlSystem::statNumberRequestsHandled() const
{
    return _statNumberRequestsHandled;
}

