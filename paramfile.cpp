#include "paramfile.h"


bool paramFile::readParam(const QString &key)
{
    QFile file(paramFile::m_filename);
    if (!file.open(QIODevice::ReadOnly)) {
        cout << "Failed to open file for reading" << endl;
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj.contains(key)) {
            paramFile::value = obj[key].toString();
            emit paramValueReturn(key,paramFile::value);
            return true;
        }
    }

    qWarning() << "Key not found in file";
    return false;
}

bool paramFile::writeParam(const QString &key, const QString &value)
{
    QFile file(paramFile::m_filename);
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning() << "Failed to open file for writing";
        return false;
    }

    QJsonDocument doc;
    QJsonObject obj;

    if (file.size() > 0) {
        doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isObject()) {
            obj = doc.object();
        }
    }

    obj[key] = value;
    doc.setObject(obj);

    file.resize(0);
    file.write(doc.toJson());
    file.close();

    return true;
}
