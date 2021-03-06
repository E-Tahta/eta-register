/*****************************************************************************
 *   Copyright (C) 2016 by Yunusemre Senturk                                 *
 *   <yunusemre.senturk@pardus.org.tr>                                       *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#include "fileio.h"
#include "logger.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QDate>

#define CONFIG_FILE "/.config/eta/eta-register"
#define IWB_INFO_FILE "/usr/share/eta/eta-check-inputdevice/type-of-iwb"

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{
    d = new QDir(QDir::home());
    logger = new Logger(this);

    filepath = d->homePath() + QString::fromLatin1(CONFIG_FILE);
    filename = "data.eta";
    fullpath = filepath + "/" + filename;

    QFileInfo checkFile(fullpath);
    if(!checkFile.exists() || !checkFile.isFile()) {
        logger->log(logger->green_color
                    + "Creating config file"
                    + logger->no_color);
        d->mkpath(filepath);
        QFile file(fullpath);
        if (file.open(QIODevice::ReadWrite)) {
            file.close();
        } else {
            logger->log(logger->red_color
                        + file.errorString()
                        + logger->no_color);
        }
    }
}

QStringList FileIO::readData()
{
    l.clear();
    QFileInfo checkFile(fullpath);
    if(checkFile.exists() && checkFile.isFile()) {
        d->mkpath(filepath);
        QFile file(fullpath);
        if (!file.open(QIODevice::ReadOnly)) {
            logger->log(logger->red_color
                        + "Could not open data file while trying to read"
                        + logger->no_color);
        } else {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                l.append(line);
            }
        }

    } else {
        logger->log(logger->red_color
                    + "Data file does not exist or corrupted"
                    + logger->no_color);
    }
    return l;
}

void FileIO::writeData()
{
    QDate date = QDate::currentDate();
    QString data = "";

    QString::number(date.day());
    QString::number(date.month());
    QString::number(date.year());


    data = QString::number(date.day())+ "-" +QString::number(date.month())+ "-"
            +QString::number(date.year());

    if(!QDir::isAbsolutePath(filepath)) {
        d->mkpath(filepath);
    }
    QFile file(fullpath);
    if (!file.open(QIODevice::WriteOnly)) {
        logger->log(logger->red_color
                    + "Could not open data file while trying to write"
                    + logger->no_color);
    } else {
        QTextStream out(&file);
        out << data;
        file.close();
    }

}

QString FileIO::readIWBInfo() const
{
    QString content;

    QFile file(IWB_INFO_FILE);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        content = stream.readAll();
        file.close();
    } else {
        logger->log(logger->red_color
                    + QString(file.errorString() + " : "
                              + file.fileName()).toLatin1().data()
                    + " Exiting ..."
                    + logger->no_color);
        exit(1);
    }
    return content;
}
