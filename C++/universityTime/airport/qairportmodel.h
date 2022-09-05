#ifndef QAIRPORTMODEL_H
#define QAIRPORTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QtQmlIntegration>

#include <algorithm>
#include <vector>
#include <iostream>

#include "runway.h"

class QAirportModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QAirportModel(const int numberOfRunways, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void increaseRunwayNumber();
    void decreaseRunwayNumber();
    int numberOfRunways() const;

    void setSimulationStarted(bool newSimulationStarted);
    void setRunways(const std::vector<Runway *> &newRunways);
    void updateVisual();
signals:

private:
    int m_numberOfRunways;
    std::vector<QString> m_runwayID;
    std::vector<bool> m_runwayBusy;

    bool _simulationStarted;
    std::vector<Runway*> _runways;
};

#endif // QAIRPORTMODEL_H
