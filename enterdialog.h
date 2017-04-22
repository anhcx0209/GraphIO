#ifndef ENTERDIALOG_H
#define ENTERDIALOG_H

#include "adjmat.h"
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>

class EnterDialog : public QDialog
{
    Q_OBJECT
public:
    EnterDialog();
private slots:
    void enterData();
private:
    QString *name_;
    QComboBox *type_combobox_;
    QSpinBox *number_edges_spinbox_;
    QSpinBox *number_vertexs_spinbox_;

    CoreGraph *graph_;
    QTableView *table_view_;
};

#endif // ENTERDIALOG_H
