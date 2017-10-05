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

    Image {
        id: pardus
        source: "Images/background.jpg"
        height: parent.height
        width: parent.width
        anchors.centerIn: parent
        opacity: 1
    }

    Column {
        width: parent.width / 2
        height: parent.height  * 2 / 3
        anchors.centerIn: parent
        spacing: main.spacing


        Text {
            id:txtConfirmMessage
            width: parent.width
            height: 60
            text: main.confirmMessage
            font.bold: true
            color: main.textColor
            font.pointSize: main.messageTextSize
        }


        Text {
            id:txtCity
            width: parent.width
            height: 60
            text: "İl: "+main.city
            color: main.textColor
            font.pointSize: main.textSize
        }

        Text {
            id:txtTown
            width: parent.width
            height: 60
            text: "İlçe: "+main.town
            color: main.textColor
            font.pointSize: main.textSize
        }

        Text {
            id:txtSchool
            width: parent.width
            height: 60
            text: "Okul adı: "+main.school
            color: main.textColor
            font.pointSize: main.textSize
        }

        Text {
            id:txtCode
            width: parent.width
            height: 60
            text: "Tesis kodu: "+main.code
            color: main.textColor
            font.pointSize: main.textSize
        }

        Row {
            spacing: main.spacing
            width: parent.width

            Rectangle {
                id: btnEdit
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnNoColor
                radius: main.rad

                Text {
                    id: txtEdit
                    text: "Düzelt"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.pop()
                }
            }

            Rectangle {
                id: btnConfirm
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnYesColor
                radius: main.rad
                Text {
                    id: txtConfirm
                    text: "Onayla"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        bridge.sendData(main.cityCode,main.town,main.school,
                                        main.code)
                        stackView.push(status)
                        timer.start()
                    }
                }
            }
        }
    }
}

