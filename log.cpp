#include "log.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>

Log::Log()
{

}

bool Log::escreve(QString linha)
{
    bool escreveu = false;
    QString preamb = "["+QDateTime::currentDateTime().toString(Qt::ISODate)+"]: ";
    //ui->editLog->appendPlainText(preamb+msg);

    QString filename = "Log.txt";
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text) )
    {
        QTextStream stream(&file);
        stream << preamb+linha << "\n";
        escreveu = true;
    }
    file.close();
    return escreveu;
}
