#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphscene.h"
#include "enterdialog.h"

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
    void newGraph();
    void openGraph();
    void saveGraph();
    void about();
private:

    void createActions();
    void createMenu();
//    void createToolbars();

    QMenu *file_menu_;
    QMenu *view_menu_;
    QMenu *help_menu_;

    QAction *new_action_;
    QAction *open_action_;
    QAction *save_action_;
    QAction *exit_action_;

    QAction *about_action_;
    QAction *help_action_;

};

#endif // MAINWINDOW_H
