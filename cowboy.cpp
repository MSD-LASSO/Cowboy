#include "cowboy.h"

Cowboy::Cowboy()
{

}

void Cowboy::mySlot()
{
    QMessageBox msgBox;
    msgBox.setText("hi this is the cowboy slot");
    msgBox.exec();
}

QDateTime Cowboy::getStartAccess()
{
    return startAccess;
}

QDateTime Cowboy::getEndAccess()
{
    return endAccess;
}

double Cowboy::getTleError()
{
    return tleError;
}

double Cowboy::getRecordInterval()
{
    return recordInterval;
}

double Cowboy::getRecordTime()
{
    return recordTime;
}

double Cowboy::getSampleRate()
{
    return sampleRate;
}

int Cowboy::getNumEvents()
{
    return numEvents;
}

double Cowboy::getChannelFreq()
{
    return channelFreq;
}

double Cowboy::getCenterFreq()
{
    return centerFreq;
}

double Cowboy::getFilterFreq()
{
    return filterFreq;
}

QString Cowboy::getStringOutputFolder()
{
    return folder;
}

void Cowboy::setRecordInterval(double elRecordoIntervalo)
{
    recordInterval=elRecordoIntervalo;
}

void Cowboy::setRecordTime(double elRecordoTiempo)
{
    recordTime=elRecordoTiempo;
}

void Cowboy::setSampleRate(double sampuloRato)
{
    sampleRate=sampuloRato;
}

