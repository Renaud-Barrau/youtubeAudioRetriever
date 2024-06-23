#ifndef logHandler_H
#define logHandler_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <iostream>

class logHandler {
public:
    static logHandler& instance();
    void init(const QString& fileName, qint64 maxFileSize = 1024 * 1024, int maxBackupIndex = 5);
    void close();
    static void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    logHandler() = default;
    ~logHandler();
    logHandler(const logHandler&) = delete;
    logHandler& operator=(const logHandler&) = delete;

    void rotateLogs();

    QFile logFile;
    QString baseFileName;
    qint64 maxFileSize;
    int maxBackupIndex;
};

#endif // logHandler_H
