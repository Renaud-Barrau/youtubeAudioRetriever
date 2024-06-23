#include "logHandler.h"
#include <QFileInfo>
#include <QDir>

logHandler& logHandler::instance() {
    static logHandler instance;
    return instance;
}

void logHandler::init(const QString& fileName, qint64 maxFileSize, int maxBackupIndex) {
    this->baseFileName = fileName;
    this->maxFileSize = maxFileSize;
    this->maxBackupIndex = maxBackupIndex;

    logFile.setFileName(baseFileName);
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Unable to open log file: " << baseFileName.toStdString() << std::endl;
    }
    qInstallMessageHandler(customMessageHandler);
}

void logHandler::close() {
    if (logFile.isOpen()) {
        logFile.close();
    }
}

void logHandler::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    logHandler& handler = logHandler::instance();
    if (handler.logFile.size() >= handler.maxFileSize) {
        handler.rotateLogs();
    }

    static QTextStream stream(&handler.logFile);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    switch (type) {
    case QtDebugMsg:
        stream << "[" << currentTime << "] Debug: " << msg << Qt::endl;
        break;
    case QtWarningMsg:
        stream << "[" << currentTime << "] Warning: " << msg << Qt::endl;
        break;
    case QtInfoMsg:
        stream << "[" << currentTime << "] Info: " << msg << Qt::endl;
        break;
    case QtCriticalMsg:
        stream << "[" << currentTime << "] Critical: " << msg << Qt::endl;
        break;
    case QtFatalMsg:
        stream << "[" << currentTime << "] Fatal: " << msg << Qt::endl;
        abort();
    }

    stream.flush();
}

void logHandler::rotateLogs() {
    logFile.close();

    for (int i = maxBackupIndex; i > 0; --i) {
        QString oldName = baseFileName + "." + QString::number(i);
        QString newName = baseFileName + "." + QString::number(i + 1);

        if (QFile::exists(oldName)) {
            QFile::remove(newName);
            QFile::rename(oldName, newName);
        }
    }

    QString firstBackupName = baseFileName + ".1";
    QFile::rename(baseFileName, firstBackupName);

    logFile.setFileName(baseFileName);
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        std::cerr << "Unable to open log file: " << baseFileName.toStdString() << std::endl;
    }
}

logHandler::~logHandler() {
    close();
}
