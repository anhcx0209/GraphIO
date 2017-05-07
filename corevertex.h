#ifndef COREVERTEX_H
#define COREVERTEX_H

#include <QString>

class CoreVertex
{
private:
    QString id_;
    bool flag_;
    CoreVertex *visit_;

public:
    CoreVertex(QString i);                  // default constructor
    CoreVertex(const CoreVertex*);          // copy constructor

    QString id() const {return id_;}
    void setId(QString i) {id_ = i;}

    bool flag() const { return flag_; }
    void setFlag(bool value) { flag_ = value; }

    void setVisit(CoreVertex *v) { visit_ = v; }
    CoreVertex *visit() const { return visit_; }
};

#endif // COREVERTEX_H
