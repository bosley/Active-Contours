#include "paraminterface.h"
#include "ui_paraminterface.h"


#ifdef ACTIVE_CONTOUR_ALG
ParamInterface::ParamInterface(AlgoParams * ap, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParamInterface)
{
    ui->setupUi(this);
    this->lap = ap;

    ui->sobelDSCheck->setChecked(lap->getSobelDeadSpace());
    ui->snakeLineCheck->setChecked(lap->getDrawSnakeLines());
    ui->snakePointCheck->setChecked(lap->getDrawSnakePoints());

    for(int i = 1; i < 255; i++)
    {
        ui->sobelCombo->addItem(QString::number(i));
    }

    for(int i = lap->getNumberPoints(); i < 1000; i++)
    {
        ui->contourCombo->addItem(QString::number(i));
    }

    ui->contourCombo->setCurrentIndex(0);
    ui->sobelCombo->setCurrentIndex(lap->getSobelThreash()-1);

    ui->sobelView->setChecked(lap->getViewSobel());
    ui->snakeView->setChecked(!lap->getViewSobel());

    ui->alphaSlider->setRange(0, 10);
    ui->betaSlider->setRange(0, 10);
    ui->gammaSlider->setRange(0, 100);

    ui->alphaSlider->setValue(lap->getAlpha()*10);
    ui->betaSlider->setValue(lap->getBeta()*10);
    ui->gammaSlider->setValue(lap->getGama());

    ui->alphaValLabel->setText(QString::number(lap->getAlpha()));
    ui->betaValLabel->setText(QString::number(lap->getBeta()));
    ui->gammaValLabel->setText(QString::number(lap->getGama()));
}

ParamInterface::~ParamInterface()
{
    this->lap = nullptr;
    delete ui;
}

void ParamInterface::on_cancelButton_clicked()
{
    this->close();
}

void ParamInterface::on_doneButton_clicked()
{
    lap->setNumberPoints(ui->contourCombo->currentText().toInt());
    lap->setSobelThresh(ui->sobelCombo->currentText().toInt());

    lap->setDrawSobelDeadpace(ui->sobelDSCheck->isChecked());
    lap->setDrawSnakeLines(ui->snakeLineCheck->isChecked());
    lap->setDrawSnakePoints(ui->snakePointCheck->isChecked());
    lap->setViewSobel(ui->sobelView->isChecked());
    lap->setAlpha(static_cast<float>(ui->alphaSlider->value())/10.00);
    lap->setBeta(static_cast<float>(ui->betaSlider->value())/10.00);
    lap->setGama(static_cast<float>(ui->gammaSlider->value()));

    this->close();
}

void ParamInterface::closeEvent(QCloseEvent *event)
{
    emit completed();
    event->accept();
}

void ParamInterface::on_sobelView_toggled(bool checked)
{
    ui->snakeView->setChecked(!checked);
}

void ParamInterface::on_snakeView_toggled(bool checked)
{
    ui->sobelView->setChecked(!checked);
}

void ParamInterface::on_alphaSlider_valueChanged(int value)
{
    ui->alphaValLabel->setText(QString::number(
                                   static_cast<float>(value)/10.00)
                               );
}

void ParamInterface::on_betaSlider_valueChanged(int value)
{
    ui->betaValLabel->setText(QString::number(
                                   static_cast<float>(value)/10.00)
                               );
}

void ParamInterface::on_gammaSlider_valueChanged(int value)
{
    ui->gammaValLabel->setText(QString::number(
                                   static_cast<float>(value))
                               );
}
#endif //ACTIVE_CONTOUR_ALG
