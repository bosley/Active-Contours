#ifndef CUSTONSNAKEPARAMS_H
#define CUSTONSNAKEPARAMS_H

// Required to get CUSTOM_CONTOUR_ALG
#include "Vision/tsparams.h"

#ifdef CUSTOM_CONTOUR_ALG

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class CustonSnakeParams;
}

class CustonSnakeParams : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustonSnakeParams(AlgoParams * ap, QWidget *parent = 0);
    ~CustonSnakeParams();

signals:
    void completed();

private slots:
    void on_doneButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CustonSnakeParams *ui;
    AlgoParams *lap;
    void closeEvent(QCloseEvent *event);
};

#endif // CUSTOM_CONTOUR_ALG
#endif // CUSTONSNAKEPARAMS_H
