#ifndef INCMAT_H
#define INCMAT_H

#include <QAbstractTableModel>
#include "coregraph.h"

class IncMat : public QAbstractTableModel
{
    Q_OBJECT
private:
    CoreGraph *graph_;
public:
    IncMat(CoreGraph *g);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
signals:
    void editCompleted(QString);
};

#endif // INCMAT_H
