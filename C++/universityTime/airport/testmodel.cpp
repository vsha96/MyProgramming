#include "testmodel.h"

TestModel::TestModel(int numberOfItems, QObject *parent)
    : QAbstractListModel {parent}
{
    Q_UNUSED(parent);
    m_n = numberOfItems;
    text.resize(m_n);
    color.resize(m_n);
    fill(text.begin(), text.end(), "TEXT");
    fill(color.begin(), color.end(), "purple");
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_n;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant {};
    }

    //
    //    return QVariant::fromValue(m_runways[rowIndex].getRunway_id());

    //    DisplayRole = 0,
    //    DecorationRole = 1,

    const int rowIndex = index.row();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant::fromValue(rowIndex);
//        return QVariant::fromValue(text[rowIndex]);
        break;
    case Qt::DecorationRole:
        return QVariant::fromValue(color[rowIndex]);
        break;
    }
    return QVariant {};
}

void TestModel::trigger()
{
//    beginResetModel();
    beginInsertRows(QModelIndex(), m_n, m_n);
    m_n++;
    text.resize(m_n);
    color.resize(m_n);

    text[text.size()-1] = "NEW";
    color[color.size()-1] = "black";

    /*
    insertRow(m_n, index(m_n));
    for (int i=0; i<rowCount(); i++) {
        emit dataChanged(index(i), index(i), {Qt::DisplayRole, Qt::DecorationRole} );
    }
    */
//    auto mindex = index(m_n - 1);
//    emit dataChanged(mindex, mindex, {Qt::DisplayRole, Qt::DecorationRole} );

    std::cout << "TestModel: triggered: m_n = " << m_n << std::endl;

    endInsertRows();
    //    endResetModel();
}

void TestModel::triggerDelete()
{
    if (m_n < 2) {
        std::cout << "WARN: TestModel: triggerDelete: m_n = "
                  << m_n
                  << std::endl;
    } else {
        m_n--;
        beginRemoveRows(QModelIndex(), m_n, m_n);
        text.resize(m_n);
        color.resize(m_n);

        text[text.size()-1] = "OLD";
        color[color.size()-1] = "red";

        std::cout << "TestModel: triggered delete: m_n = " << m_n  << std::endl;

        endRemoveRows();
    }
}
