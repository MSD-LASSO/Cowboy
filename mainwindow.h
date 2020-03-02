#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QMessageBox>
#include <QProcess>
#include <QThread>
#include "cowboy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Cowboy* cowboy=new Cowboy();

private slots:


    void on_updateSettings_statA_btn_clicked();

    void on_checkAccess_adv_btn_clicked();

    void on_startAccess_adv_timeDate_editingFinished();

    void on_endAccess_adv_timeDate_editingFinished();

public slots:

private:
    Ui::MainWindow *ui;

    double maxFreq = 550.0;             // mHz
    int decFreq = 3;

    double maxFilt = 10000.0;           // kHz
    int decFilt = 3;

    double maxRecordInterval = 180.0;   // s
    int decRecordInterval = 3;

    double maxSampleRate = 20.0;        // MSPS
    int decSampleRate = 3;

    double maxRecordTime;               // ms, dynamically determined based on the current recordInterval
    int decRecordTime = 3;

    int decTleTol = 3;

    void setupFreqInputs();
    void setupSamplingInputs();
    void setupAccessTimeInputs();
    void updateSamplingInputs();
};

#endif // MAINWINDOW_H
