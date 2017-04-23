#ifndef NEWWMAT_H
#define NEWWMAT_H

#include "enterdialog.h"
#include "wmat.h"

class NewWMat : public EnterDialog
{
public:
    NewWMat(QString);
protected:
    void enterData();
    void sendData();
};

#endif // NEWWMAT_H
