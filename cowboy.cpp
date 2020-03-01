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

double Cowboy::getTleError(timeUnit unit)
{
    if (unit == tu_seconds)
    {
        return tleError*(double)MS_IN_S;
    }
    else // ms
    {
        return tleError;
    }
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

void Cowboy::setStartAccess(QDateTime datetime)
{
    startAccess = datetime;
}

void Cowboy::setEndAccess(QDateTime datetime)
{
    endAccess = datetime;
}

void Cowboy::setTleError(double error, timeUnit unit)
{
    if (unit == tu_seconds)
    {
        tleError = error*(double)MS_IN_S;
    }
    else // ms
    {
        tleError = error;
    }
}

void Cowboy::setRecordInterval(double interval)
{
    recordInterval = interval;
}

void Cowboy::setRecordTime(double time)
{
    recordTime = time;
}

void Cowboy::setSampleRate(double rate)
{
    sampleRate = rate;
}

void Cowboy::setNumEvents(int events)
{
    numEvents = events;
}

void Cowboy::setChannelFreq(double freq)
{
    channelFreq = freq;
}

void Cowboy::setCenterFreq(double freq)
{
    centerFreq = freq;
}

void Cowboy::setFilterFreq(double freq)
{
    filterFreq = freq;
}

QString Cowboy::getStringOutputFolder()
{
    return folder;
}

