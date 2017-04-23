#ifndef NEWADJMAT_H
#define NEWADJMAT_H

#include "enterdialog.h"
#include "adjmat.h"

class NewAdjMat : public EnterDialog
{
public:
    NewAdjMat(QString);

protected slots:
    void enterData();
    void sendData();
};

#endif // NEWADJMAT_H
