#include "screen.h"
#include "ui_screen.h"

screen::screen(AlgoParams *ap ,SourceManager *sm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::screen)
{
    lsm = sm;
    ui->setupUi(this);
    connect(ui->screenWidget, SIGNAL(errorMessage(QString)), this, SLOT(errorMessage(QString)));
    connect(ui->screenWidget, SIGNAL(displayStopped()), this, SLOT(displayStopped()));

    ui->screenWidget->setParams(ap);

    _complete = false;
    _userStarted = false;
    _failure = false;
}

screen::~screen()
{
    delete ui;
}

void screen::errorMessage(QString m)
{
    QMessageBox msgBox;
    msgBox.setText(m);
    msgBox.exec();
}

void screen::displayStopped()
{
    _complete = true;
    emit completed();
}

void screen::on_actionStop_triggered()
{
    ui->screenWidget->stop();
}

void screen::closeEvent(QCloseEvent *event)
{
    if(!_complete)
    {
        while(!ui->screenWidget->stopped())
            ui->screenWidget->stop();
        while(!_complete){}
    }
    event->accept();
}

void screen::resizeEvent(QResizeEvent *event)
{
    event->accept();
}

void screen::launchVideo()
{
   if(!ui->screenWidget->startVideo(lsm->getSelectedVideo()))
   {
       emit completed();
       _failure = true;
       this->close();
   }
}

void screen::launchCamera()
{
    if(!ui->screenWidget->startCamera(lsm->getSelectedCamera()))
    {
        emit completed();
        _failure = true;
        this->close();
    }
}

void screen::launchImage()
{
    if(!ui->screenWidget->startImage(lsm->getSelectedImage()))
    {
        emit completed();
        _failure = true;
        this->close();
    }
}

void screen::on_ssButton_clicked()
{
    if(ui->screenWidget->canStart())
    {
        ui->screenWidget->startAlgo();
        ui->ssButton->setVisible(false);
    } else {
        errorMessage("Not enough points to initialize snake!");
    }
}
