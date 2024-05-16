#ifndef PARAMFILE_H
#define PARAMFILE_H
#include <QObject>

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

using namespace std;


class paramFile : public QObject
{
    Q_OBJECT
public:
    explicit paramFile(const QString &filename) : m_filename(filename){
        };

    QString value;

signals:
    void loadParam(QString,QString);
    void paramValueReturn(QString,QString);

public slots:
    bool readParam(const QString &key);
    bool writeParam(const QString &key, const QString &value);

private:
    QString m_filename;
};

#endif // PARAMFILE_H
