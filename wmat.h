#ifndef WMAT_H
#define WMAT_H

#include <QAbstractTableModel>
#include "coregraph.h"

class WMat : public QAbstractTableModel
{
    Q_OBJECT
private:
    CoreGraph *graph_;
public:
    WMat(CoreGraph *);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role);
signals:
    void editCompleted(QString);
};

#endif // WMAT_H
