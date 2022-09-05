#include "qairportmodel.h"

QAirportModel::QAirportModel(const int numberOfRunways, QObject *parent)
    : QAbstractListModel {parent}
{
    Q_UNUSED(parent);

    m_numberOfRunways = numberOfRunways;

    m_runwayID.resize(m_numberOfRunways);
    m_runwayBusy.resize(m_numberOfRunways);

//    fill(m_runwayID.begin(), m_runwayID.end(), "0");
//    std::iota(m_runwayID.begin(), m_runwayID.end(), 1);

    for (int i=0; i<m_numberOfRunways; i++) {
        m_runwayID[i] = QString::number(i+1); // set runway id
    }
    fill(m_runwayBusy.begin(), m_runwayBusy.end(), false);

    _simulationStarted = false;
}

int QAirportModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_numberOfRunways;
}

QVariant QAirportModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant {};
    const int rowIndex = index.row();

    switch (role) {
    case Qt::DisplayRole:
        if (_simulationStarted) {
            return QString::fromStdString( _runways[rowIndex]->getInfoOnRunwayRequest() );
//            return QVariant { _runways[rowIndex]->runwayID() };
        }
        return QVariant {m_runwayID[rowIndex]};
        break;
    case Qt::DecorationRole:
        if (_simulationStarted) {
            return QVariant { _runways[rowIndex]->isBusy() };
        }
        return QVariant {m_runwayBusy[rowIndex]};
        // TODO return QVariant { runways[rowIndex]->isBusy() };
        break;
    }
    return QVariant {};
}

void QAirportModel::increaseRunwayNumber()
{
    beginInsertRows(QModelIndex(), m_numberOfRunways, m_numberOfRunways);
    m_numberOfRunways++;
    m_runwayID.resize(m_numberOfRunways);
    m_runwayBusy.resize(m_numberOfRunways);

    // set params of new runway
    m_runwayID[m_runwayID.size()-1] = QString::number(m_numberOfRunways); // DisplayRole
    m_runwayBusy[m_runwayBusy.size()-1] = false; // DecorationRole

    std::cout << "QAirportModel: increaseRunwayNumber: m_numberOfRunways = "
              << m_numberOfRunways << std::endl;

    endInsertRows();
}

void QAirportModel::decreaseRunwayNumber()
{
    if (m_numberOfRunways < 2) {
        std::cout << "WARN: TestModel: triggerDelete: m_n = "
                  << m_numberOfRunways
                  << std::endl;
    } else {
        m_numberOfRunways--;
        beginRemoveRows(QModelIndex(), m_numberOfRunways, m_numberOfRunways);
        m_runwayID.resize(m_numberOfRunways);
        m_runwayID.resize(m_numberOfRunways);

        std::cout << "QAirportModel: decreaseRunwayNumber: m_numberOfRunways = "
                  << m_numberOfRunways  << std::endl;

        endRemoveRows();
    }
}

int QAirportModel::numberOfRunways() const
{
    return m_numberOfRunways;
}

void QAirportModel::setRunways(const std::vector<Runway *> &newRunways)
{
    _runways = newRunways;
}

void QAirportModel::updateVisual()
{
    for (int i=0; i<rowCount(); i++) {
        emit dataChanged(index(i), index(i), {Qt::DisplayRole, Qt::DecorationRole} );
    }
}

void QAirportModel::setSimulationStarted(bool newSimulationStarted)
{
    _simulationStarted = newSimulationStarted;
}
