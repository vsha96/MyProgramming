#ifndef QREQUESTSMODEL_H
#define QREQUESTSMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QtQmlIntegration>

#include <vector>

#include "flight_request.h"

class QRequestsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QRequestsModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setSimulationStarted(bool newSimulationStarted);
    void setRequests(const std::vector<FlightRequest *> &newRequests);
    void updateVisual();
private:
    bool _updated;
    bool _simulationStarted;
    std::vector<FlightRequest*> _requests;
};

#endif // QREQUESTSMODEL_H
