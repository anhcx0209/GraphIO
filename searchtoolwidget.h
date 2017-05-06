#ifndef SEARCHTOOLWIDGET_H
#define SEARCHTOOLWIDGET_H

#include <QtWidgets>

class SearchToolWidget : public QGroupBox
{    
public:
    SearchToolWidget(QWidget *parent = 0);

private:    
    QComboBox *alg_selector_;
    QPushButton *start_button_;
    QPushButton *prev_button_;
    QPushButton *next_button_;
    QLineEdit *start_input_;    

    QLabel *total_step_;
    QSpinBox *cur_step_;
};

#endif // SEARCHTOOLWIDGET_H
