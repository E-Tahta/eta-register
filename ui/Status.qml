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
import QtQuick.Controls 1.2

Item {

    ToolButton {
        id: btnClose
        iconSource: "Images/close.svg"
        width: main.width/10
        height: btnClose.width
        x: parent.width - btnClose.width
        onClicked: {
            Qt.quit();
        }
    }

    Image {
        id: svgBusy
        source: "Images/busy.svg"
        width: main.height * 2 / 3
        height: main.height * 2 / 3
        visible: main.busy ? true : false
        anchors.centerIn: parent
        NumberAnimation on rotation {
            id: rotationAnimation
            duration: 1000
            from: 0
            to: 360
            loops:Animation.Infinite
        }

    }

    Column {
        width: parent.width / 4
        height: parent.height * 3 / 4
        anchors.centerIn: parent
        spacing: main.spacing
        visible: main.busy ? false : true


        Image {
            id: svgStatus
            source: main.imageSource
            width: parent.width
            height: parent.width

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (main.success) {
                        Qt.quit()
                    }
                }
            }
        }

        Item {
            height: 60
            width: parent.width
            Text {
                id:txtStatusMessage
                font.bold: true
                height: 60
                font.pointSize: main.messageTextSize
                text: main.statusMessage
                color: main.textColor
                opacity: main.busy ? 0 : 1
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: btnRetry
            height: 60
            width: parent.width
            color: main.btnYesColor
            radius: main.rad
            visible: main.success ? false : true


            Text {
                id: txtRetry
                text: "Tekrar dene"
                font.bold: true
                font.pointSize: main.buttonTextSize
                anchors.centerIn: parent
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    main.busy = true
                    bridge.sendData(main.cityCode,main.town,main.school,
                                    main.code, main.cpu, main.touchPanel)
                    stackView.push(status)
                    timer.running = true
                }
            }
        }


    }

}
