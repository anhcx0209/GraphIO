#ifndef NEWSTRUCTADJ_H
#define NEWSTRUCTADJ_H

#include "enterdialog.h"
#include "structadj.h"

class NewStructAdj : public EnterDialog
{
public:
    NewStructAdj();

protected:
    void enterData();
    void sendData();
};

#endif // NEWSTRUCTADJ_H
