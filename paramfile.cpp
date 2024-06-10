/**
 * @file paramfile.cpp
 * @brief Implementation of the paramFile class

 */

#include "paramfile.h"

/**
 * @fn paramFile::readParam(const QString &key)
 * @brief Reads a parameter from the JSON configuration file.
 *
 * This method opens the configuration file specified by paramFile::m\_filename in read-only mode.
 * If the file cannot be opened, an error message is printed to the console and the method returns "0".
 *
 * The method then reads the entire contents of the file and parses it as a JSON document using QJsonDocument::fromJson().
 * If the parsed document is a JSON object, the method checks whether it contains a key that matches the input parameter 'key'.
 * If the key is found, the method prints the value to the console, converts it to a QString using QJsonValue::toString(),
 * and returns the QString.
 *
 * If the key is not found in the JSON object, or if the parsed document is not a JSON object, the method prints an error message
 * to the console and returns "0".
 *
 * @param key The key to search for in the JSON configuration file.
 * @return QString The value associated with the input key in the JSON configuration file, or "0" if the key is not found.
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
            cout << "return value : " << obj[key].toString().toStdString() << endl;
            return obj[key].toString();
        }
    }

    cout << "Key not found in file" << endl;
    return "0";
}


/**
 * @fn paramFile::writeParam(const QString &key, const QString &value)
 * @brief Writes a parameter to the JSON configuration file.
 *
 * This method opens the configuration file specified by paramFile::m\_filename in read-write mode.
 * If the file cannot be opened, an error message is printed to the console and the method returns false.
 *
 * If the file is not empty, the method reads the entire contents of the file and parses it as a JSON document using QJsonDocument::fromJson().
 * If the parsed document is a JSON object, the method sets the value of the input key 'key' to an empty string and then to the input value 'value'
 * using QJsonObject::operator\[\].
 *
 * The method then sets the JSON object as the root object of the JSON document using QJsonDocument::setObject(),
 * truncates the file to zero length using QFile::resize(),
 * writes the JSON document to the file using QFile::write(),
 * and closes the file.
 *
 * If the file is empty or the parsed document is not a JSON object, the method creates a new JSON object,
 * sets the value of the input key 'key' to the input value 'value' using QJsonObject::operator\[\],
 * sets the JSON object as the root object of the JSON document using QJsonDocument::setObject(),
 * truncates the file to zero length using QFile::resize(),
 * writes the JSON document to the file using QFile::write(),
 * and closes the file.
 *
 * @param key The key to write to the JSON configuration file.
 * @param value The value to associate with the input key in the JSON configuration file.
 * @return bool true if the parameter was successfully written to the file, or false otherwise.
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


