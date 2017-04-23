#ifndef NEWINCMAT_H
#define NEWINCMAT_H

#include "enterdialog.h"
#include "incmat.h"

class NewIncMat : public EnterDialog
{
public:
    NewIncMat(QString);
protected:
    void enterData();
    void sendData();
};

#endif // NEWINCMAT_H
