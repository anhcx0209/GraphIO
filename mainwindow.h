#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "edglist.h"
#include "incmat.h"
#include "structadj.h"
#include "wmat.h"
#include "graphscene.h"
#include "newadjmat.h"
#include "newincmat.h"
#include "newwmat.h"
#include "newedglist.h"
#include "newstructadj.h"
#include "helpdialog.h"

#include <QMainWindow>
#include <QDebug>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void start(CoreGraph *);
    void startNewVisual();
    void startNewAdjMat();
    void startNewIncMat();
    void startNewWMat();
    void startNewEdgList();
    void startNewStructAdj();
    void openGraph();
    void saveGraph();
    void openHelp();
    void about();
    void openDemo1();
    void openDemo2();

    void gotGraphFromDialog(CoreGraph *);

    void changePage(int);
    void visualGraphGroupClicked(int);
private:
    void createActions();
    void createMenu();
    void createToolbars();
    void setupPageWidget(CoreGraph *);

    CoreGraph *graph_;

    GraphScene *scene_;
    QGraphicsView *view_;

    QTableView *adjmat_view_;
    QTableView *edglist_view_;
    QTableView *incmat_view_;
    QTableView *structadj_view_;
    QTableView *wmat_view_;

    QStackedWidget *pages_widget_;

    QMenu *file_menu_;
    QMenu *demo_menu_;
    QMenu *help_menu_;
    QMenu *new_menu_;

    QAction *demo_action_1_;
    QAction *demo_action_2_;
    QAction *demo_action_3_;

    QAction *new_action_;
    QAction *new_visual_action_;
    QAction *new_adjmat_action_;
    QAction *new_incmat_action_;
    QAction *new_wmat_action_;
    QAction *new_edglist_action_;
    QAction *new_structadj_action_;

    QAction *open_action_;
    QAction *save_action_;
    QAction *exit_action_;
    QAction *delete_action_;

    QAction *about_action_;
    QAction *help_action_;

    QToolBar *graph_toolbar_;
    QToolBar *view_toolbar_;

    QComboBox *view_combobox_;

    QButtonGroup *visual_graph_group_;
};

#endif // MAINWINDOW_H
