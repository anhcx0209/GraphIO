#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QToolButton>
#include <QDir>
#include <QDebug>

class HelpBrowser : public QWidget
{
    Q_OBJECT

public:
    HelpBrowser(const QString &path, const QString &page, QWidget *parent = 0);
    static void showPage(const QString &page);

private slots:
    void updateWindowtitle();

private:
    QTextBrowser *browser_;
    QToolButton *home_button_;
    QToolButton *back_button_;
    QToolButton *close_button_;
};

#endif // HELPDIALOG_H
