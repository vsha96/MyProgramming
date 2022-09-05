#include "qrequestsmodel.h"



QRequestsModel::QRequestsModel(QObject *parent)
{
    Q_UNUSED(parent);
    _simulationStarted = false;
    _updated = false;
}

int QRequestsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (_simulationStarted) {
        return _requests.size();
    } else {
        return 0;
    }
}

QVariant QRequestsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant {};
    const int rowIndex = index.row();

    switch (role) {
    case Qt::DisplayRole:
        if (_simulationStarted) {
            return QString::fromStdString( _requests[rowIndex]->getInfo() );
        }
        return QVariant { "text" };
        break;
    case Qt::DecorationRole:
        if (_simulationStarted) {
            if (_requests[rowIndex]->handled()) {
                return QVariant { "green" };
            } else {
                return QVariant { "orange" };
            }
        }
        return QVariant { "red" };
        break;
    }
    return QVariant {};
}

void QRequestsModel::setSimulationStarted(bool newSimulationStarted)
{
    _simulationStarted = newSimulationStarted;
}

void QRequestsModel::updateVisual()
{
    if (!_updated) {
        beginResetModel();
        endResetModel();
        _updated = true;
    }
    for (int i=0; i<rowCount(); i++) {
        emit dataChanged(index(i), index(i), {Qt::DisplayRole, Qt::DecorationRole} );
    }
}

void QRequestsModel::setRequests(const std::vector<FlightRequest *> &newRequests)
{
    _requests = newRequests;
}
