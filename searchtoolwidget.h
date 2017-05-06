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
    enum ALGORITHM { BFS = 0, DFS = 1};

    QComboBox *alg_selector_;
    QPushButton *start_button_;
    QPushButton *prev_button_;
    QPushButton *next_button_;
    QLineEdit *start_input_;

    QLabel *max_step_label_;
    QSpinBox *cur_step_spin_;

    CoreGraph *graph_;

    QList<CoreGraph *> list_steps_;

    int bfs(int i, CoreVertex *start);          // run to step i of bfs
    int dfs(int i, CoreVertex *start);          // run to step i of dfs

    // STEP INFORMATION
    int max_step_;
    int cur_step_;
    ALGORITHM mode_;
    CoreVertex *start_vertex_;
signals:
    void graphChanged();

private slots:
    void changeMode(int);
    void search();
    void nextStep();
    void previouStep();
    void goToStep(int i);
};

#endif // SEARCHTOOLWIDGET_H
