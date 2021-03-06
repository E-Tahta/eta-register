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
#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QStringList>
#include <QString>

class QDir;
class Logger;

class FileIO : public QObject
{
    Q_OBJECT
public:
    explicit FileIO(QObject *parent = 0);

    QStringList readData();
    void writeData();
    QString readIWBInfo() const;

signals:

private:
    QString filepath;
    QString filename;
    QString fullpath;
    QStringList l;
    QDir *d;
    Logger *logger;

public slots:

};

#endif // FILEIO_H
