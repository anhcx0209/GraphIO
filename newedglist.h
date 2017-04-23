#ifndef NEWEDGLIST_H
#define NEWEDGLIST_H

#include "enterdialog.h"
#include "edglist.h"

class NewEdgList : public EnterDialog
{
public:
    NewEdgList();
protected:
    void enterData();
    void sendData();
};

#endif // NEWEDGLIST_H
