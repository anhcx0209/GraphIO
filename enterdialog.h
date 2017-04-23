#ifndef ENTERDIALOG_H
#define ENTERDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include "coregraph.h"

class EnterDialog : public QDialog
{
    Q_OBJECT
public:
    EnterDialog(QString name);

signals:
    void finishEnterData(CoreGraph *);

protected slots:
    virtual void enterData() = 0;
    virtual void sendData() = 0;

protected:
    QString name_;
    QComboBox *type_combobox_;
    QSpinBox *number_edges_spinbox_;
    QSpinBox *number_vertexs_spinbox_;

    QTableView *table_view_;
    CoreGraph *data_;
};

#endif // ENTERDIALOG_H
