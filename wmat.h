#ifndef WMAT_H
#define WMAT_H

#include <QAbstractTableModel>
#include "coregraph.h"

class WMat : public QAbstractTableModel
{
private:
    CoreGraph *graph_;
public:
    WMat(CoreGraph *);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // WMAT_H
