#ifndef SCREEN_H
#define SCREEN_H

#include <QMainWindow>
#include "screen.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QResizeEvent>
#include "MediaManager/sourcemanager.h"
#include "Vision/tsparams.h"

namespace Ui {
class screen;
}

class screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit screen(AlgoParams *ap, SourceManager *sm, QWidget *parent = 0);
    ~screen();
    void launchVideo();
    void launchCamera();
    void launchImage();

public slots:
    void errorMessage(QString m);

    void displayStopped();

private slots:
    void on_actionStop_triggered();

    void on_ssButton_clicked();

signals:
    void completed();

private:
    Ui::screen *ui;
    SourceManager *lsm;
    bool _complete;
    bool _userStarted;
    bool _failure;

    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

};

#endif // SCREEN_H

