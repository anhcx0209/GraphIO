#ifndef COREVERTEX_H
#define COREVERTEX_H

#include <QString>

class CoreVertex
{
private:
    QString id_;
public:
    CoreVertex(QString i);
    QString id() {return id_;}
    void setId(QString i) {id_ = i;}
};

#endif // COREVERTEX_H
