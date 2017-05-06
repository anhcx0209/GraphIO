#ifndef NEWADJMAT_H
#define NEWADJMAT_H

#include "enterdialog.h"
#include "adjmat.h"

class NewAdjMat : public EnterDialog
{
public:
    NewAdjMat();

protected slots:
    void enterData();
    void notice(QString);
};

#endif // NEWADJMAT_H
