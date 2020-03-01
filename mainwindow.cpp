#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cowboy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWi2ndow)
{
    ui->setupUi(this);

    /* TODO
     * Make main class
     * make station tabs dynamic
     * add tooltips
     * implement events
     * warning on close
     * mirror basic & adv tab
     * check that 20 MSPS is max sample rate
     * check sample rate precision and reflect in decimals
     * grey out unimplemented functions
     * default value for output folder
     * add event: max record time based on current record interval
     * fix scope of default values...
    */

    Cowboy* cowboy = new Cowboy();

    QIcon folder_icon = QIcon("img/folder.png");
    ui->browse_basic_btn->setIcon(folder_icon);
    ui->browse_adv_btn->setIcon(folder_icon);

    setWindowTitle("Cowboy");

    setupFreqInputs(cowboy);
    setupSamplingInputs(cowboy);
    setupAccessTimeInputs(cowboy);

    std::system("./HelloWorld");

    connect(ui->download_adv_btn, &QPushButton::clicked, cowboy, &Cowboy::mySlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFreqInputs(Cowboy* cowboy)
{
    // frequency spinboxes
    ui->channelFreq_basic_spinBox->setMaximum(maxFreq);
    ui->channelFreq_adv_statA_spinBox->setMaximum(maxFreq);
    ui->centerFreq_basic_spinBox->setMaximum(maxFreq);
    ui->centerFreq_adv_statA_spinBox->setMaximum(maxFreq);

    ui->channelFreq_basic_spinBox->setDecimals(decFreq);
    ui->channelFreq_adv_statA_spinBox->setDecimals(decFreq);
    ui->centerFreq_basic_spinBox->setDecimals(decFreq);
    ui->centerFreq_adv_statA_spinBox->setDecimals(decFreq);

    ui->channelFreq_basic_spinBox->setValue(cowboy->getChannelFreq());
    ui->channelFreq_adv_statA_spinBox->setValue(cowboy->getChannelFreq());
    ui->centerFreq_basic_spinBox->setValue(cowboy->getCenterFreq());
    ui->centerFreq_adv_statA_spinBox->setValue(cowboy->getCenterFreq());

    // filter
    ui->filterBand_statA_spindBox->setMaximum(maxFilt);
    ui->filterBand_statA_spindBox->setValue(cowboy->getFilterFreq());
    ui->filterBand_statA_spindBox->setDecimals(decFilt);
}

void MainWindow::setupSamplingInputs(Cowboy* cowboy)
{
    // record interval
    ui->recInterval_statA_spinBox->setMaximum(maxRecordInterval);
    ui->recInterval_statA_spinBox->setValue(cowboy->getRecordInterval());
    ui->recInterval_statA_spinBox->setDecimals(decRecordInterval);

    // sample rate
    ui->sampleRate_statA_spinBox->setMaximum(maxSampleRate);
    ui->sampleRate_statA_spinBox->setValue(cowboy->getSampleRate());
    ui->sampleRate_statA_spinBox->setDecimals(decSampleRate);

    // record time
    double maxRecordTime = ui->recInterval_statA_spinBox->value()*MS_IN_S;
    ui->recTime_statA_spinBox->setMaximum(maxRecordTime);
    ui->recTime_statA_spinBox->setValue(cowboy->getRecordTime());
    ui->recTime_statA_spinBox->setDecimals(decRecordTime);
}

void MainWindow::setupAccessTimeInputs(Cowboy* cowboy)
{
    // time dates
    // TODO change to use getAccess functions
    ui->startAccess_basic_date->setDate(cowboy->getStartAccess().date());
    ui->endAccess_basic_date->setDate(cowboy->getEndAccess().date());

    ui->startAccess_adv_timeDate->setDateTime(cowboy->getStartAccess());
    ui->endAccess_adv_timeDate->setDateTime(cowboy->getEndAccess());

    // TLE tolerance
    ui->tleTol_dial->setValue(defaultTleTol);

    double tleTol = (double)ui->tleTol_dial->value()/(double)1000;
    ui->tleTol_label->setText( QString::number(tleTol, 'g', decTleTol));
}

void MainWindow::on_trackSat_adv_btn_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("hello");
    msgBox.exec();
}

void MainWindow::zoePrivateSlot()
{
    QMessageBox msgBox;
    msgBox.setText("executing Zoe's private slot");
    msgBox.exec();
}

void MainWindow::mwSlot()
{
    QMessageBox msgBox;
    msgBox.setText("connection worked");
    msgBox.exec();
}
