#ifndef COREVERTEX_H
#define COREVERTEX_H

#include <QString>

class CoreVertex
{
private:
    QString id_;
    bool visit_;
public:
    CoreVertex(QString i);
    QString id() {return id_;}
    void setId(QString i) {id_ = i;}
    void setVisit(bool value) { visit_ = value; }
    void visit() { return visit_; }
};

#endif // COREVERTEX_H
