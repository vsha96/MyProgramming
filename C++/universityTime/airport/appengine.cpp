#include "appengine.h"

AppEngine::AppEngine()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AppEngine::worldTimeTick);
    m_worldTime = SimTime(0, 0, 0);

    m_numberOfRunways = 0;
    m_airportModel = nullptr;
    m_requestsModel = nullptr;
    m_simulationStarted = false;

    _FCSystem = nullptr;
}

AppEngine::AppEngine(int numberOfRunways)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AppEngine::worldTimeTick);
    m_worldTime = SimTime(0, 0, 0);

    m_numberOfRunways = numberOfRunways;
    m_airportModel = new QAirportModel(m_numberOfRunways);
    m_requestsModel = new QRequestsModel();

    m_simulationStarted = false;

    _FCSystem = nullptr;
}

QString AppEngine::getWorldTimeDay()
{
    return QString::number(m_worldTime.day);
}

QString AppEngine::getWorldTimeHour()
{
    if (m_worldTime.hour < 10)
        return "0" + QString::number(m_worldTime.hour);
    else
        return QString::number(m_worldTime.hour);
}

QString AppEngine::getWorldTimeMin()
{
    if (m_worldTime.min < 10)
        return "0" + QString::number(m_worldTime.min);
    else
        return QString::number(m_worldTime.min);
}

int AppEngine::getNumberOfRunways()
{
    return m_numberOfRunways;
}

void AppEngine::setNumberOfRunways(const int &numberOfRunways)
{
    m_numberOfRunways = numberOfRunways;
    std::cout << "AppEngine: Number of runways has been changed "
              << numberOfRunways << std::endl;
    emit numberOfRunwaysChanged();
}

QAirportModel* AppEngine::getAirportModel()
{
    return m_airportModel;
}

void AppEngine::increaseClicked()
{
    if (!simulationStarted()) {
    // do smt with our model
        if (m_airportModel) {
            m_airportModel->increaseRunwayNumber();
            setNumberOfRunways(m_airportModel->numberOfRunways());
        } else {
            std::cout << "WARN: AppEngine: increaseClicked: m_airportModel = nullptr" << std::endl;
        }
    } else {
        std::cout << "AppEngine: increaseClicked: can not change number when the simulation started"
                  << std::endl;
    }
}

void AppEngine::decreaseClicked()
{
    if (!simulationStarted()) {
        // do smt with our model
        if (m_airportModel) {
            m_airportModel->decreaseRunwayNumber();
            setNumberOfRunways(m_airportModel->numberOfRunways());
        } else {
            std::cout << "WARN: AppEngine: decreaseClicked: m_airportModel = nullptr"
                      << std::endl;
        }
    } else {
        std::cout << "AppEngine: decreaseClicked: can not change number when the simulation started"
                  << std::endl;
    }
}

void AppEngine::startSimulation()
{
    // time step per sec
    // init timeStep
    SimTime timeStep(TIMESTEP_MIN, TIMESTEP_HOUR, TIMESTEP_DAY);
    int msec = trunc(1000/timeStep.mins());

    if (!simulationStarted()) {
        // init maxDelayTime
        SimTime maxDelayTime(MAXDELAY_MIN, MAXDELAY_HOUR, MAXDELAY_DAY);

        setSimulationStarted(true);

        // create flight control system
        _FCSystem = new
            FlightControlSystem(
                getNumberOfRunways(),
                maxDelayTime,
                timeStep
            );

        std::cout << "AppEngine: startSimulation: simulation started!"
                  << std::endl;

        _FCSystem->initSimulation();

        // set runways for model
        m_airportModel->setRunways(_FCSystem->getRunways());
        m_airportModel->setSimulationStarted(true);
        // set requests for model
        m_requestsModel->setRequests(_FCSystem->getAllRequests());
        m_requestsModel->setSimulationStarted(true);

        m_timer->start(msec);
    } else {
        m_timer->start(msec);
    }
}

void AppEngine::stopSimulation()
{
    m_timer->stop();

    std::cout << "AppEngine: stopSimulation: STOP"
              << std::endl;

    // TEST
    _FCSystem->showTimetable();
    _FCSystem->showTimetableHandled();
}

void AppEngine::worldTimeTick()
{
    m_worldTime.tick();
    emit worldTimeChanged();

    _FCSystem->tick();

    // update visual info
    m_airportModel->updateVisual();
    m_requestsModel->updateVisual();

    if (m_worldTime == SimTime(0,0,1)) {
        m_timer->stop();

        // ? save results to csv
        _FCSystem->showTimetableHandled();
    }
}

bool AppEngine::simulationStarted() const
{
    return m_simulationStarted;
}

void AppEngine::setSimulationStarted(bool newSimulationStarted)
{
    m_simulationStarted = newSimulationStarted;
}

int AppEngine::getStatNumberRequestsHandled()
{
    if (_FCSystem) {
        return _FCSystem->statNumberRequestsHandled();
    } else {
        return 0;
    }
}

int AppEngine::getStatMaxActualDelay()
{
    if (_FCSystem) {
        return _FCSystem->statMaxActualDelay();
    } else {
        return 0;
    }
}

float AppEngine::getStatAverageActualDelay()
{
    if (_FCSystem) {
        return _FCSystem->statAverageActualDelay();
    } else {
        return 0;
    }
}

int AppEngine::getStatMaxRequestNumberOnRunway()
{
    if (_FCSystem) {
        return _FCSystem->statMaxRequestNumberOnRunway();
    } else {
        return 0;
    }
}

float AppEngine::getStatAverageRequestNumberOnRunway()
{
    if (_FCSystem) {
        return _FCSystem->statAverageRequestNumberOnRunway();
    } else {
        return 0;
    }
}

float AppEngine::getStatAverageNumberBusyRunway()
{
    if (_FCSystem) {
        return _FCSystem->statAverageNumberBusyRunway();
    } else {
        return 0;
    }
}

QRequestsModel *AppEngine::getRequestsModel() const
{
    return m_requestsModel;
}


