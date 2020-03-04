#ifndef COWBOY_H
#define COWBOY_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>

#define MS_IN_S 1000
#define DECIMAL_BASE 10

//static const int staticPublicVar = 10;

enum ReturnCodes {success, failure, warning};

enum TimeUnit {tu_seconds, tu_ms};

enum TimeZone {tz_UTC, tz_EST, tz_CST, tz_MST, tz_PST};

static QString noradIdInputMask = "00000"; // up to 5 digit number
static int noradIdLength = 5;

class Cowboy : public QObject
{
public:
    Cowboy();

    QDateTime getStartAccess();
    QDateTime getEndAccess();
    TimeZone getTimeZone();
    double getTleError(TimeUnit unit);

    double getRecordInterval();
    double getRecordTime();
    double getSampleRate();

    int getNumEvents();

    double getChannelFreq();
    double getCenterFreq();
    double getFilterFreq();

    int getNoradID();

    int getDecimation();

    QString getOutputFolder();

    void setStartAccess(QDateTime datetime);
    void setEndAccess(QDateTime datetime);
    void setTimeZone(TimeZone tz);
    void setTleError(double error, TimeUnit unit);

    void setRecordInterval(double interval);
    void setRecordTime(double time);
    void setSampleRate(double rate);

    void setNumEvents(int events);

    void setChannelFreq(double freq);
    void setCenterFreq(double freq);
    void setFilterFreq(double freq);

    void setNoradID(int norad);

    void setDecimation(int dec);

    void setOutputFolder(QString outputFolder);

    void readingAccessTimes();

public slots:
    void mySlot();

private:
    // TODO make structs for inputs and outputs

    const int elapsedYears = 20; // years elapsed between default start and end access times

    int noradId = 00001;

    QDateTime startAccess = QDateTime::currentDateTime();
    QDateTime endAccess = QDateTime::currentDateTime().addYears(elapsedYears);
    TimeZone timezone = tz_EST;
    double tleError = 0.3;          // s

    double recordInterval = 10.0;   // s
    double recordTime = 500.0;      // ms
    double sampleRate = 10.0;       // MSPS

    int numEvents;
    // TODO add array of access times
    // TODO add array of doppler freq bands

    // frequencies
    double channelFreq = 437.0; // MHz
    double centerFreq = 437.0;  // MHz
    double filterFreq = 10.0;   // kHz

    int decimation = 1;

    QString folder = "/out";
    QVector<QVector<QString> >datesArray;

    QVector<QVector<QVector<QString> > > frequenciesArray;

};



#endif // COWBOY_H
