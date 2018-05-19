#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "MediaManager/sourcemanager.h"
#include "Vision/tsparams.h"

#ifdef ACTIVE_CONTOUR_ALG
#include "paraminterface.h"
#endif

#ifdef CUSTOM_CONTOUR_ALG
#include "custonsnakeparams.h"
#endif

#include "screen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_reloadCameras_clicked();
    void on_loadVideoFile_clicked();
    void on_launchCamera_clicked();
    void on_launchVideoFile_clicked();
    void on_loadImageFile_clicked();
    void on_launchImageFile_clicked();
    
    void on_algoButton_clicked();

public slots:
    void processComplete();

private:
    Ui::MainWindow *ui;

    SourceManager sm;
    AlgoParams ap;

    void toggleUI(bool state);
};

#endif // MAINWINDOW_H
