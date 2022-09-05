#ifndef TESTMODEL_H
#define TESTMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QtQmlIntegration>
#include <vector>
#include <iostream>

class TestModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TestModel(int numberOfItems, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void trigger();
    void triggerDelete();
signals:
//    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles = QList<int>());
private:
    int m_n;
    std::vector<QString> text;
    std::vector<QString> color;
};

#endif // TESTMODEL_H
