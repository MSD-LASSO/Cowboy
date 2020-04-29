#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cowboy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* TODO
     * make station tabs dynamic, so we can add extra stations if needed
     * add tooltips
     * implement evensts
     * warning on close
     * mirror basic & adv tab
     * check sample rate precision and reflect in decimals
     * grey out unimplemented functions
     * default value for output folder
     * add event: max record time based on current record interval
    */

    QIcon folder_icon = QIcon("img/folder.png");
    ui->browse_basic_btn->setIcon(folder_icon);
    ui->browse_adv_btn->setIcon(folder_icon);

    setWindowTitle("Cowboy");

    setupFreqInputs();
    setupSamplingInputs();
    setupAccessTimeInputs();

    //std::system("./HelloWorld");

    connect(ui->download_adv_btn, &QPushButton::clicked, cowboy, &Cowboy::mySlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFreqInputs()
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

    // decimation
    ui->decim_statA_spinBox->setMinimum(minDecimation);
    ui->decim_statA_spinBox->setMaximum(maxDecimation);
    ui->decim_statA_spinBox->setValue(cowboy->getDecimation());
}

void MainWindow::setupSamplingInputs()
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

void MainWindow::setupAccessTimeInputs()
{
    // time dates
    ui->startAccess_basic_date->setDate(cowboy->getStartAccess().date());
    ui->endAccess_basic_date->setDate(cowboy->getEndAccess().date());

    ui->startAccess_adv_timeDate->setDateTime(cowboy->getStartAccess());
    ui->endAccess_adv_timeDate->setDateTime(cowboy->getEndAccess());

    // TLE tolerance
    ui->tleTol_dial->setValue( cowboy->getTleError(tu_seconds) );
    ui->tleTol_label->setText( QString::number(cowboy->getTleError(tu_seconds), 'g', decTleTol) );

    // norad ID
    // pad display text with leading 0's
    setNoradIdText(cowboy->getNoradID());
    ui->noradID_adv_edit->setInputMask(noradIdInputMask);
}

void MainWindow::on_checkAccess_adv_btn_clicked()
{
    // qDebug("frequency %f: \n",cowboy->getCenterFreq());
    // qDebug("sampling rate %f: \n ",cowboy->getSampleRate());
    // qDebug("access %s: \n",cowboy->getStartAccess().toString());
    // std::system("./HelloWorld");
    QString commandStringPt1="java -jar OrekitAccessDopplerCalculator.jar ";
    QString tleErrorString= QString::number(cowboy->getTleError(tu_seconds), 'f', 3);
    QString recordRateString=QString::number(cowboy->getRecordInterval(),'f',3);
    //QString noradIDString=QString::number(cowboy->getNoradID(),'f',3);
    QString noradIDString = QString::number(cowboy->getNoradID(), DECIMAL_BASE);
    QString channelFreqString=QString::number(cowboy->getChannelFreq(),'f',3);
    QString commandStringTotal=commandStringPt1+"noradID="+noradIDString+" errorTimeForTLE="+tleErrorString+" recordingRate="+
            recordRateString+" channelFrequency="+channelFreqString;
    // qDebug("asdf %s", noradIDString.toUtf8().constData());
    //TO DO : START TIME/ END TIME STRING CONVERSION
    qDebug("string %s",commandStringTotal.toUtf8().constData());
    //const char *commandStringChar=commandStringPt1.toStdString().c_str();
    const char *commandStringChar=commandStringTotal.toUtf8().constData();
    // std::system("./HelloWorld");

    std::system(commandStringChar);
    //std::system("java -jar OrekitAccessDopplerCalculator.jar noradID=30776");

    //java -jar OrekitAccessDopplerCalculator.jar errorTimeForTLE=0.3 recordingRate=60 noradID=30776 channelFrequency=437.15 endTime=2020-02-12T17:08:34.584+00:00


}

void MainWindow::updateSamplingInputs()
{
    // record interval

    cowboy->setRecordInterval(ui->recInterval_statA_spinBox->value());
    cowboy->setSampleRate(ui->sampleRate_statA_spinBox->value());
    cowboy->setRecordTime(ui->recTime_statA_spinBox->value());

}

void MainWindow::on_updateSettings_statA_btn_clicked()
{
   // TODO make system call to run python script that will update SDR settings
}

void MainWindow::on_startAccess_adv_timeDate_editingFinished()
{
    QDateTime startDateTime = ui->startAccess_adv_timeDate->dateTime();
    QDateTime endDateTime = cowboy->getEndAccess();

    // validate entry
    if (startDateTime.date() >= QDate::currentDate())    // check date only so start is not always reset
    {
        if (startDateTime < endDateTime)
        {
            cowboy->setStartAccess(startDateTime);
        }
        else // end date must be after start date
        {
            // response is to set the endDate to (startDate + 1 day)

            cowboy->setStartAccess(startDateTime);

            endDateTime = startDateTime.addDays(1);
            ui->endAccess_adv_timeDate->setDateTime(endDateTime);
            cowboy->setEndAccess(endDateTime);
        }
    }
    else // start must be current date or later
    {
        startDateTime = QDateTime::currentDateTime();
        ui->startAccess_adv_timeDate->setDateTime(startDateTime);
        cowboy->setStartAccess(startDateTime);
    }
}

void MainWindow::on_endAccess_adv_timeDate_editingFinished()
{
    QDateTime endDateTime = ui->endAccess_adv_timeDate->dateTime();
    QDateTime startDateTime = cowboy->getStartAccess();

    // validate entry

    if (endDateTime > startDateTime)
    {
        cowboy->setEndAccess(endDateTime);
    }
    else // if end < start, response by setting the end date to (startDate + 1 day)
    {
        endDateTime = startDateTime.addDays(1);
        ui->endAccess_adv_timeDate->setDateTime(endDateTime);
        cowboy->setEndAccess(endDateTime);
    }
}

void MainWindow::on_channelFreq_adv_statA_spinBox_editingFinished()
{
    cowboy->setChannelFreq(ui->channelFreq_adv_statA_spinBox->value());
}

void MainWindow::on_centerFreq_adv_statA_spinBox_editingFinished()
{
    cowboy->setCenterFreq(ui->centerFreq_adv_statA_spinBox->value());
}

void MainWindow::on_filterBand_statA_spindBox_editingFinished()
{
    cowboy->setFilterFreq(ui->filterBand_statA_spindBox->value());
}

void MainWindow::on_decim_statA_spinBox_editingFinished()
{
    cowboy->setDecimation(ui->decim_statA_spinBox->value());
}

void MainWindow::on_recInterval_statA_spinBox_editingFinished()
{
    // compare in seconds
    double recordInterval = ui->recInterval_statA_spinBox->value();
    double recordTime = cowboy->getRecordTime()/(double)MS_IN_S;

    // validate
    if (recordInterval >= recordTime)
    {
        cowboy->setRecordInterval(recordInterval);
    }
    else // don't change record interval
    {
        recordInterval = cowboy->getRecordInterval();
        ui->recInterval_statA_spinBox->setValue( recordInterval );
    }
}

void MainWindow::on_sampleRate_statA_spinBox_editingFinished()
{
    cowboy->setSampleRate(ui->sampleRate_statA_spinBox->value());
}

void MainWindow::on_recTime_statA_spinBox_editingFinished()
{
    //compare in ms
    double recordTime = ui->recTime_statA_spinBox->value();
    double recordInterval = cowboy->getRecordInterval()*(double)MS_IN_S;

    if (recordTime <= recordInterval)
    {
        cowboy->setRecordTime(recordTime);
    }
    else // don't change record Time
    {
        recordTime = cowboy->getRecordTime();
        ui->recTime_statA_spinBox->setValue(recordTime);
    }
}

void MainWindow::on_noradID_adv_edit_editingFinished()
{
    bool returnStatus;
    int noradId = ui->noradID_adv_edit->text().toInt(&returnStatus);
    if (true == returnStatus && noradId > 0)
    {
        cowboy->setNoradID(noradId);
        setNoradIdText(noradId);
    }
    else
    {
        setNoradIdText(cowboy->getNoradID());
    }
}

void MainWindow::setNoradIdText(int id)
{
    // pad display text with leading 0's
    QString noradIdStr = QString("%1").arg((uint)id, noradIdLength, (int)DECIMAL_BASE, QChar('0'));
    ui->noradID_adv_edit->setText(noradIdStr);
}
