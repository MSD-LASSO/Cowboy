#ifndef COWBOY_H
#define COWBOY_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>

#define MS_IN_S 1000

//static const int staticPublicVar = 10;

enum returnCodes {success, failure, warning};

class Cowboy : public QObject
{
public:
    Cowboy();

    QDateTime getStartAccess();
    QDateTime getEndAccess();
    double getTleError();

    double getRecordInterval();
    double getRecordTime();
    double getSampleRate();

    int getNumEvents();

    double getChannelFreq();
    double getCenterFreq();
    double getFilterFreq();

    double setRecordInterval(double recordoIntervalo);
    double setRecordTime(double recordoTiempo);
    double setSampleRate(double sampuloRato);

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
