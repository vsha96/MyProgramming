#ifndef APPENGINE_H
#define APPENGINE_H

#include <QTimer>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

#include <iostream>
#include <cmath>

#include "qairportmodel.h"
#include "qrequestsmodel.h"

#include "flight_request.h"
#include "flightcontrolsystem.h"
//#include <testmodel.h>

#define TIMESTEP_MIN  5
#define TIMESTEP_HOUR 0
#define TIMESTEP_DAY  0

class AppEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberOfRunways READ getNumberOfRunways WRITE setNumberOfRunways NOTIFY numberOfRunwaysChanged)
    Q_PROPERTY(QString worldTimeDay READ getWorldTimeDay NOTIFY worldTimeChanged)
    Q_PROPERTY(QString worldTimeHour READ getWorldTimeHour NOTIFY worldTimeChanged)
    Q_PROPERTY(QString worldTimeMin READ getWorldTimeMin NOTIFY worldTimeChanged)
    // stats
    Q_PROPERTY(int statNumberRequestsHandled READ getStatNumberRequestsHandled NOTIFY worldTimeChanged)
    Q_PROPERTY(int statMaxActualDelay READ getStatMaxActualDelay NOTIFY worldTimeChanged)
    Q_PROPERTY(float statAverageActualDelay READ getStatAverageActualDelay NOTIFY worldTimeChanged)
    Q_PROPERTY(int statMaxRequestNumberOnRunway READ getStatMaxRequestNumberOnRunway NOTIFY worldTimeChanged)
    Q_PROPERTY(float statAverageRequestNumberOnRunway READ getStatAverageRequestNumberOnRunway NOTIFY worldTimeChanged)
    Q_PROPERTY(float statAverageNumberBusyRunway READ getStatAverageNumberBusyRunway NOTIFY worldTimeChanged)
    QML_ELEMENT
public:
    AppEngine();
    AppEngine(int numberOfRunways);
    QString getWorldTimeDay();
    QString getWorldTimeHour();
    QString getWorldTimeMin();

    int getNumberOfRunways();
    void setNumberOfRunways(const int &numberOfRunways);
    QAirportModel* getAirportModel();
    QRequestsModel* getRequestsModel() const;

    Q_INVOKABLE void increaseClicked();
    Q_INVOKABLE void decreaseClicked();
    Q_INVOKABLE void startSimulation();
    Q_INVOKABLE void stopSimulation();

    void worldTimeTick();

    bool simulationStarted() const;
    void setSimulationStarted(bool newSimulationStarted);

    // stats
    int getStatNumberRequestsHandled();
    int getStatMaxActualDelay();
    float getStatAverageActualDelay();
    int getStatMaxRequestNumberOnRunway();
    float getStatAverageRequestNumberOnRunway();
    float getStatAverageNumberBusyRunway();


signals:
    void numberOfRunwaysChanged();
    void worldTimeChanged();
//    void statsChanged(); // no need, updates every worldTimeChanged()

private:
    QTimer *m_timer;
    SimTime m_worldTime;
    int m_numberOfRunways;

    QAirportModel *m_airportModel;
    QRequestsModel *m_requestsModel;

    bool m_simulationStarted;

    FlightControlSystem *_FCSystem;
};

#endif // APPENGINE_H
