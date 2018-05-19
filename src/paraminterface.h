#ifndef PARAMINTERFACE_H
#define PARAMINTERFACE_H

#include "Vision/tsparams.h"


#ifdef ACTIVE_CONTOUR_ALG

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class ParamInterface;
}

class ParamInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParamInterface(AlgoParams * ap, QWidget *parent = 0);
    ~ParamInterface();

private slots:
    void on_cancelButton_clicked();
    void on_doneButton_clicked();

    void on_sobelView_toggled(bool checked);

    void on_snakeView_toggled(bool checked);

    void on_alphaSlider_valueChanged(int value);

    void on_betaSlider_valueChanged(int value);

    void on_gammaSlider_valueChanged(int value);

signals:
    void completed();

private:
    Ui::ParamInterface *ui;
    AlgoParams *lap;
    void closeEvent(QCloseEvent *event);
};


#endif // ACTIVE_CONTOUR_ALG
#endif // PARAMINTERFACE_H
