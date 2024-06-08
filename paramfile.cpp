/**
 * @file paramfile.cpp
 * @brief Implementation of the paramFile class

 */

#include "paramfile.h"

/**
 * @fn paramFile::readParam(const QString &key)
 * @brief This method reads a specific parameter identified by his key passed in parameter.
 * This function uses the QJsonDocument and QJsonObject to navigate through the required value.
 *
 * @param key
 * @return NOTE : This method DOES NOT return the value of the parameter.
 * Instead, it returns a bool to notify if operation failed or not and emits a signal with the value in parameter as a QString, so it can be catched by others classes.
 *
 *
 */
QString paramFile::readParam(const QString &key)
{
    QFile file(paramFile::m_filename);
    if (!file.open(QIODevice::ReadOnly)) {
        cout << "Failed to open file for reading" << endl;
        return "0";
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj.contains(key)) {
//            paramFile::value = obj[key].toString();
//            emit paramValueReturn(key,paramFile::value);
            cout << "return value : " << obj[key].toString().toStdString() << endl;
            return obj[key].toString();
        }
    }

    cout << "Key not found in file" << endl;
    return "0";
}



/**
 * @fn paramFile::writeParam(const QString &key, const QString &value)
 * @brief This method writes a specific parameter with a specific key associated to it.
 * This function uses the QJsonDocument and QJsonObject to navigate through the required value.
 * @param key
 * @param value
 *
 * @return NOTE : This method returns a bool to notify if operation failed or not.
 */
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

    obj[key] = "";
    obj[key] = value;
    doc.setObject(obj);

    file.resize(0);
    file.write(doc.toJson());
    file.close();

    return true;
}


