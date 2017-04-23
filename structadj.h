#ifndef STRUCTADJ_H
#define STRUCTADJ_H

#include <QAbstractTableModel>
#include "coregraph.h"

class StructAdj : public QAbstractTableModel
{
private:
    CoreGraph *graph_;

public:
    StructAdj(CoreGraph *g);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // STRUCTADJ_H
