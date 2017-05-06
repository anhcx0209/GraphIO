#ifndef COREVERTEX_H
#define COREVERTEX_H

#include <QString>

class CoreVertex
{
private:
    QString id_;
    bool flag_;
public:
    CoreVertex(QString i);
    QString id() {return id_;}
    void setId(QString i) {id_ = i;}

    bool flag() const { return flag_; }
    void setFlag(bool value) { flag_ = value; }
};

#endif // COREVERTEX_H
