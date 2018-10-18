/*****************************************************************************
 *   Copyright (C) 2016 by Hikmet Bas                                        *
 *   <hikmet.bas@pardus.org.tr>                                              *
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

import QtQuick 2.0

Item {

    Item {
        id: topContainer
        width: parent.width
        height: parent.height / 2

        Text {
            id: txtMessage
            text: message
            font.bold: true
            color: main.textColor
            font.pointSize: main.messageTextSize
            anchors.centerIn: parent
        }
    }

    Column {
        width: parent.width / 2
        height: parent.height / 5
        anchors.centerIn: parent
        spacing: main.spacing


        Rectangle {
            id: btnContinue
            height: 60
            width: parent.width
            color: main.btnYesColor
            radius: main.rad
            Text {
                id: txtContinue
                text: "Kayıt"
                font.bold: true
                font.pointSize: main.buttonTextSize
                anchors.centerIn: parent
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stackView.push(register)
                }
            }
        }

        Rectangle {
            id: btnLater
            height: 60
            width: parent.width
            color: main.btnNoColor
            radius: main.rad

            Text {
                id: txtLater
                text: "Daha Sonra"
                font.bold: true
                font.pointSize: main.buttonTextSize
                anchors.centerIn: parent
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
        }

        Item {
            id: bottomContainer
            width: parent.width
            height: 40

            Text {
                id: txtSubMessage
                text: subMessage
                font.italic: true
                horizontalAlignment: Text.AlignHCenter
                color: main.textColor
                font.pointSize: 10
                anchors.centerIn: parent

            }
        }
    }
}
