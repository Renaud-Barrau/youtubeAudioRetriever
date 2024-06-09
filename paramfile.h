/**
 * @file paramfile.h
 * @brief This file handle the read/write access to the params.json file that stores important data, sush as :
 * - API credentials for OAUTH identification (Api key, client ID, client secret code, refresh token)
 * - path for ffmpeg dependency
 * - path for music folder output
 *
 * Read and write function make use of QJsonDocument and QjsonObject to deals with the param file and browse in the different keys.
 */


#ifndef PARAMFILE_H
#define PARAMFILE_H
#include <QObject>

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

using namespace std;

/**
 * @class paramFile
 * @brief The paramFile class represent the object in charge of loading and saving important data into a parameter file.
 */
class paramFile : public QObject
{
    Q_OBJECT
public:
    explicit paramFile(const QString &filename) : m_filename(filename){
        };


public slots:
    QString readParam(const QString &key);
    bool writeParam(const QString &key, const QString &value);

private:
    QString m_filename;
};

#endif // PARAMFILE_H
