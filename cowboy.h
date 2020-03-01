#ifndef COWBOY_H
#define COWBOY_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>

#define MS_IN_S 1000

//static const int staticPublicVar = 10;

enum returnCodes {success, failure, warning};

enum timeUnit {tu_seconds, tu_ms};

class Cowboy : public QObject
{
public:
    Cowboy();

    QDateTime getStartAccess();
    QDateTime getEndAccess();
    double getTleError(timeUnit unit);

    double getRecordInterval();
    double getRecordTime();
    double getSampleRate();

    int getNumEvents();

    double getChannelFreq();
    double getCenterFreq();
    double getFilterFreq();

    void setStartAccess(QDateTime datetime);
    void setEndAccess(QDateTime datetime);
    void setTleError(double error, timeUnit unit);

    void setRecordInterval(double interval);
    void setRecordTime(double time);
    void setSampleRate(double rate);

    void setNumEvents(int events);

    void setChannelFreq(double freq);
    void setCenterFreq(double freq);
    void setFilterFreq(double freq);

    QString getStringOutputFolder();

public slots:
    void mySlot();

private:
    // TODO make structs for inputs and outputs

    const int elapsedYears = 20; // years elapsed between default start and end access times

    int noradId;

    QDateTime startAccess = QDateTime::currentDateTime();
    QDateTime endAccess = QDateTime::currentDateTime().addYears(elapsedYears);
    double tleError = 0.3;          // s

    double recordInterval = 10.0;   // s
    double recordTime = 500.0;     // ms
    double sampleRate = 10.0;       // MSPS

    int numEvents;
    // TODO add array of access times
    // TODO add array of doppler freq bands

    // frequencies
    double channelFreq = 437.0; // MHz
    double centerFreq = 437.0;  // MHz
    double filterFreq = 10.0;   // kHz

    QString folder = "/out";
};



#endif // COWBOY_H
