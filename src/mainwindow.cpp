#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_reloadCameras_clicked()
{
    sm.reloadCameras();
    ui->cameraCombo->clear();
    for(int i = 0; i < sm.getAvailableCameras(); i++)
    {
        ui->cameraCombo->addItem(QString::number(i));
    }
}

void MainWindow::on_loadVideoFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                              tr("Open Video"), ".",
                                              tr("Video Files (*.avi *.mpg *.mp4)"));
    sm.setSelectedVideo(filename.toStdString().data());
    ui->currVideo->setText("..."+filename.mid(filename.length()-30));
}

void MainWindow::on_loadImageFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                              tr("Open Image"), ".",
                                              tr("Image Files (*.jpg *.jpeg *.png)"));
    sm.setSelectedImage(filename.toStdString().data());
    ui->currImage->setText("..."+filename.mid(filename.length()-30));
}

void MainWindow::on_launchCamera_clicked()
{
    sm.setSelectedCamera(ui->cameraCombo->currentText().toInt());

    toggleUI(false);
    screen *s = new screen(&ap, &sm, this);
    connect(s, SIGNAL(completed()), this, SLOT(processComplete()));
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    s->show();
    s->launchCamera();
}

void MainWindow::on_launchVideoFile_clicked()
{
    toggleUI(false);
    screen *s = new screen(&ap, &sm, this);
    connect(s, SIGNAL(completed()), this, SLOT(processComplete()));
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    s->show();
    s->launchVideo();
}

void MainWindow::on_launchImageFile_clicked()
{
    toggleUI(false);
    screen *s = new screen(&ap, &sm, this);
    connect(s, SIGNAL(completed()), this, SLOT(processComplete()));
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    s->show();
    s->launchImage();
}

void MainWindow::processComplete()
{
    toggleUI(true);
}

void MainWindow::toggleUI(bool state)
{
    ui->loadVideoFile->setEnabled(state);
    ui->launchCamera->setEnabled(state);
    ui->launchImageFile->setEnabled(state);
    ui->loadImageFile->setEnabled(state);
    ui->reloadCameras->setEnabled(state);
    ui->launchVideoFile->setEnabled(state);
    ui->cameraCombo->setEnabled(state);
    ui->algoButton->setEnabled(state);
}

void MainWindow::on_algoButton_clicked()
{
#ifdef ACTIVE_CONTOUR_ALG
    ParamInterface *s = new ParamInterface(&ap, this);
    connect(s, SIGNAL(completed()), this, SLOT(processComplete()));
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    s->show();
#endif

#ifdef CUSTOM_CONTOUR_ALG
    CustonSnakeParams *s = new CustonSnakeParams(&ap, this);
    connect(s, SIGNAL(completed()), this, SLOT(processComplete()));
    s->setAttribute(Qt::WA_DeleteOnClose, true);
    s->show();
#endif

    toggleUI(false);
}
