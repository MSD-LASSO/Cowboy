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

TimeZone Cowboy::getTimeZone()
{
    return timezone;
}

double Cowboy::getTleError(TimeUnit unit)
{
    if (unit == tu_seconds)
    {
        return tleError;
    }
    else // ms
    {
        return tleError*(double)MS_IN_S;
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

int Cowboy::getNoradID()
{
    return noradId;
}

int Cowboy::getDecimation()
{
    return decimation;
}

QString Cowboy::getOutputFolder()
{
    return folder;
}

void Cowboy::setStartAccess(QDateTime datetime)
{
    startAccess = datetime;
}

void Cowboy::setEndAccess(QDateTime datetime)
{
    endAccess = datetime;
}

void Cowboy::setTimeZone(TimeZone tz)
{
    timezone = tz;
}

void Cowboy::setTleError(double error, TimeUnit unit)
{
    if (unit == tu_seconds)
    {
        tleError = error;//(double)MS_IN_S;
    }
    else // ms
    {
        tleError = error*(double)MS_IN_S;
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

void Cowboy::setNoradID(int norad)
{
    noradId = norad;
}

void Cowboy::setDecimation(int dec)
{
    decimation = dec;
}

void Cowboy::setOutputFolder(QString outputFolder)
{
    folder = outputFolder;
}
