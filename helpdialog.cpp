#include "helpdialog.h"

HelpBrowser::HelpBrowser(const QString &path, const QString &page, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_GroupLeader);

    QSize size = QSize(25, 25);
    browser_ = new QTextBrowser();
    browser_->setSearchPaths(QStringList() << path << ":/doc/images");
    browser_->setSource(page);

    home_button_ = new QToolButton();
    home_button_->setIcon(QIcon(":/icons/home.png"));
    home_button_->setIconSize(size);

    back_button_ = new QToolButton();
    back_button_->setIcon(QIcon(":/icons/back.png"));
    back_button_->setIconSize(size);

    close_button_ = new QToolButton();
    close_button_->setIcon(QIcon(":/icons/close.png"));
    close_button_->setIconSize(size);


    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(home_button_);
    buttonLayout->addWidget(back_button_);
    buttonLayout->addStretch();
    buttonLayout->addWidget(close_button_);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(browser_);
    setLayout(mainLayout);

    connect(home_button_, SIGNAL(clicked()), browser_, SLOT(home()));
    connect(back_button_, SIGNAL(clicked()), browser_, SLOT(backward()));
    connect(close_button_, SIGNAL(clicked()), this, SLOT(close()));

    connect(browser_,
            SIGNAL(sourceChanged(QUrl)),
            this,
            SLOT(updateWindowtitle()));

    setWindowIcon(QIcon(":/icons/help_icon.png"));
}

void HelpBrowser::showPage(const QString &page)
{
    QString path = QDir(":/doc").absolutePath();
    HelpBrowser *browser = new HelpBrowser(path, page);
    browser->resize(500, 400);
    browser->show();
}

void HelpBrowser::updateWindowtitle()
{
    setWindowTitle(tr("Справка: %1").arg(browser_->documentTitle()));
}
