#ifndef INCMAT_H
#define INCMAT_H

#include <QAbstractTableModel>
#include "coregraph.h"

class IncMat : public QAbstractTableModel
{
private:
    CoreGraph *graph_;

public:
    IncMat(CoreGraph *g);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // INCMAT_H
