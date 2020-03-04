#include "cowboy.h"
#include <QFile>
#include <QTextStream>
#
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
void Cowboy::readingAccessTimes(){
    QString noradIDString = QString::number(44331, DECIMAL_BASE);
    QString fileName="DopplerAccess"+noradIDString+".txt";
    //READING THE OUTPUT FILE

     QString numStationsString;
     QString baseFreqLine;
     QString signalBandwidthLine;
     QString recordTimeLine;
     QString numEventsLine;


    // ifstream myfile (fileName);

    // getline (myfile,numStationsString);

     QFile inputFile(fileName);
     if (inputFile.open(QIODevice::ReadOnly))
     {
        QTextStream in(&inputFile);

        QString firstline = in.readLine();
        numStationsString=firstline.replace(0,12,"");
        int numStations=numStationsString.toInt();
        qDebug("num stations: %d",numStations);
        QString station[numStations];

        for (int n=0; n<numStations;n++){    //next n lines: station names

               QString line=in.readLine();
               qDebug(qUtf8Printable(line));
               station[n]=line;
           }

        QString numEventsLine=in.readLine();
        //qDebug(qUtf8Printable(numEventsLine.replace(0,10,"")));
        QString numEventLineNum=numEventsLine.replace(0,10,"");
        int numEvents=numEventLineNum.toInt();
        //qDebug(qUtf8Printable(numEventLineNum));
        //qDebug("numevents: %d",numEvents);
        QVector<QVector<QString> >dateArray;

        QVector<QVector<QVector<QString> > > frequencyArray;

        int numContainers=numStations*3;  // 3 is because there is nominal, low, and high freq containers.

             for (int l=0;l<numContainers;l++){

                 frequencyArray.append((QVector<QVector<QString> >())); //defining "numContainers" # of blank 2d arrays

                 for (int m=0;m<numEvents;m++){
                     frequencyArray[l].append((QVector<QString>())); //next, defining "numEvents" # of rows for the 2d arrays.
                 }

             }

             int b=-1;
                 QString nextLine;
                 int magnitudeMultiplier=1000000; //from MHz to Hz
                // regex reg("\\s+");
                 nextLine=in.readLine();
                while (b< (numEvents) && !in.atEnd()){

                  //cout <<nextLine.substr(0,23)<< '\n';

                  if (nextLine.left(6)=="Access"){   //substring of QString from the left end
                    qDebug(qUtf8Printable("this is a header line"));
                    b++;
                    dateArray.append( (QVector<QString>()));

                   }
                  else{
                  dateArray[b].append(nextLine.left(23));   //0 to 23 is the date part of the line
                  nextLine=nextLine.mid(28,nextLine.size()-28);
                  qDebug(qUtf8Printable(nextLine));
                  QRegExp splitter("\\s+");  //special delimiter to split by tabs
                  QStringList freqs=nextLine.split(splitter);
                  qDebug( qUtf8Printable(freqs[0]));
                  //QString asdf="asdf"; asdf.toD
                  //double asdf1=1; asdf.toStdString()
                //  int numOfEntries=freqs.length;
                  for (int n=0; n<numContainers; n++)
                  {
                   double dopFreq=freqs[n].toDouble();
                   dopFreq=dopFreq*magnitudeMultiplier;
                   int dopFreqInt=static_cast<int>(dopFreq);
                   //qDebug("asdf %d",dopFreqInt);
                    frequencyArray[n][b].push_back(QString::number(dopFreqInt));
                   }

                  }
                  nextLine=in.readLine();

                }
                inputFile.close();  //end of retreiving data from java


                //storing all access time info into cowboy class private vars.
                 datesArray=dateArray;
                 frequenciesArray=frequencyArray;


                        //Debugging lines to check if data is stored properly
                       for (int d=0; d<numEvents;d++){
                             qDebug("datearrayeventsize: %d",dateArray[d].size());

                             for (int f=0; f<dateArray[d].size();f++){
                             qDebug(qUtf8Printable(dateArray[d][f]));
                             }

                        }


                       //Freq checking

                       qDebug("freqArraysize: %d",frequencyArray.size());
                        qDebug("actions in event size %d",(frequencyArray[0].size()));
                           for (int p=0; p<frequencyArray.size();p++){
                               for (int q=0; q<frequencyArray[0].size();q++){
                                   for (int r=0; r<frequencyArray[0][q].size();r++){

                                        qDebug(qUtf8Printable( frequencyArray[p][q][r]) );


                                   }

                                qDebug(qUtf8Printable ( "\n event end" ));
                               }
                               qDebug(qUtf8Printable("container end"));

                           }

     }
}




    //checking if dates were stored properly
/*
    for (int d=0; d<numEvents;d++){
        cout <<dateArray[d].size()<< '\n';
        for (int f=0; f<dateArray[d].size();f++){
        cout <<dateArray[d][f]<< '\n';
        }

     }

    //checking if frequencies were stored properly
    cout<<to_string(frequencyArray.size())<< '\n';
    cout<<to_string(frequencyArray[0].size())<< '\n';
     for (int p=0; p<frequencyArray.size();p++){
         for (int q=0; q<frequencyArray[0].size();q++){
             for (int r=0; r<frequencyArray[0][q].size();r++){

                  cout<<frequencyArray[p][q][r]<< ' ';

          // cout<<to_string(frequencyArray[p][q].size())<< ' ';
             }

          cout <<"\n event end"<< '\n';
         }
         cout <<"container end"<< '\n';

     }


    //Python Command for Andrew's Program...


    //python record_ref.py --channel-freq=X --samp-rate=X --center-freq=X --num-samples=X --file-loc=’/home/pi/Documents/Record/XXXXX’

*/

