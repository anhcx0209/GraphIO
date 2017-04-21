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
};

#endif // STRUCTADJ_H
