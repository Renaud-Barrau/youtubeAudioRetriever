/**
 * @file paramfile.h
 * @brief Header of the paramFile class
 *
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
 * @brief The paramFile class provides a simple interface for reading and writing parameters to a JSON configuration file.
 *
 * This class is derived from QObject and uses the Qt JSON module to parse and generate JSON documents.
 * The configuration file is specified by the m\_filename member variable, which is set in the constructor.
 *
 * The class provides two public slots: readParam() and writeParam().
 * The readParam() slot takes a single input parameter 'key' and returns the value associated with that key in the JSON configuration file,
 * or "0" if the key is not found.
 * The writeParam() slot takes two input parameters 'key' and 'value', and writes the value to the JSON configuration file.
 *
 * @note This class does not provide any error handling or synchronization mechanisms.
 * It is intended to be used in a simple, single-threaded application where the configuration file is not modified by external processes.
 *
 * @see QJsonDocument, QJsonObject, QFile
 */
class paramFile : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a new paramFile object with the specified configuration file.
     * @param filename The path to the configuration file.
     */
    explicit paramFile(const QString &filename) : m_filename(filename){
        };


public slots:
    QString readParam(const QString &key);
    bool writeParam(const QString &key, const QString &value);

private:
    /**
     * @brief The path to the configuration file.
     */
    QString m_filename;
};

#endif // PARAMFILE_H
