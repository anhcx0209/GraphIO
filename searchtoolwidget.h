#ifndef SEARCHTOOLWIDGET_H
#define SEARCHTOOLWIDGET_H

#include <QtWidgets>
#include "coregraph.h"
#include <QDebug>
#include <QList>

class SearchToolWidget : public QGroupBox
{
    Q_OBJECT
public:
    SearchToolWidget(CoreGraph *, QWidget *parent = 0);

private:    
    QComboBox *alg_selector_;
    QPushButton *start_button_;
    QPushButton *prev_button_;
    QPushButton *next_button_;
    QLineEdit *start_input_;    

    QLabel *total_step_;
    QSpinBox *cur_step_;

    CoreGraph *graph_;

    QList<CoreGraph *> list_steps_;

    void bfs(QString);
signals:
    void start();
private slots:
    void test();
};

#endif // SEARCHTOOLWIDGET_H
