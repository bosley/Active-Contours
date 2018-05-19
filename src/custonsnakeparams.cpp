#include "custonsnakeparams.h"
#include "ui_custonsnakeparams.h"

#ifdef CUSTOM_CONTOUR_ALG

CustonSnakeParams::CustonSnakeParams(AlgoParams * ap, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustonSnakeParams)
{
    ui->setupUi(this);
    this->lap = ap;
}

CustonSnakeParams::~CustonSnakeParams()
{
    delete ui;
}

void CustonSnakeParams::closeEvent(QCloseEvent *event)
{
    emit completed();
    event->accept();
}

void CustonSnakeParams::on_doneButton_clicked()
{
    // Update the algo class with input params

    this->close();
}

void CustonSnakeParams::on_cancelButton_clicked()
{
    this->close();
}

#endif //CUSTOM_CONTOUR_ALG
