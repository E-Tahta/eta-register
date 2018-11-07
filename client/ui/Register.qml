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
import "../js/functions.js" as Func

Item {

    Column {
        width: parent.width / 2
        height: parent.height  * 2 / 3
        anchors.centerIn: parent
        spacing: main.spacing

        Text {
            id:txtRegisterMessage
            width: parent.width
            height: 40
            font.pointSize: main.messageTextSize
            font.bold: true
            text: registerMessage
            color: main.textColor
        }

        ComboBox {
            id: city
            width: parent.width
            height: 60
            model: cityModel
            onCurrentIndexChanged: {
                main.currIndex = currentIndex
                main.fillTowns()
                main.cityCode = xmlCities.get(currentIndex) ?
                            xmlCities.get(currentIndex).id : main.cityCode
                if (main.cityCode.length == 1) {
                    main.cityCode = "0"+main.cityCode
                }
            }

        }

        ComboBox {
            id: town
            width: parent.width
            height: 60
            model: townsModel

        }

        TextField {
            id:school
            width: parent.width
            height: 60
            placeholderText: "Okul adını giriniz"
            maximumLength: 100
            onFocusChanged: {
                if(school.focus) {
                    bridge.showKeyboard()
                }
            }
        }

        TextField {
            id:code
            width: parent.width
            height: 60
            placeholderText: "Kurum/Tesis kodunuzu giriniz"
            onFocusChanged: {
                if(code.focus) {
                    bridge.showKeyboard()
                }
            }
        }

        Row {
            spacing: main.spacing
            width: parent.width

            Rectangle {
                id: btnCancel
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnNoColor
                radius: main.rad

                Text {
                    id: txtLater
                    text: "Vazgeç"
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

            Rectangle {
                id: btnSend
                height: 60
                width: parent.width / 2 - main.spacing / 2
                color: main.btnYesColor
                radius: main.rad
                Text {
                    id: txtContinue
                    text: "Gönder"
                    font.bold: true
                    font.pointSize: main.buttonTextSize
                    anchors.centerIn: parent
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        main.city = city.currentText
                        main.town = town.currentText
                        main.school = school.text.trim().toUpperCase()
                        main.code = code.text.trim()

                        if (Func.checkText(main.city)){
                            if (Func.checkText(main.town)) {
                                if (Func.checkText(main.school)) {
                                    if (Func.checkCode(main.code)) {
                                        txtError.text = ""
                                        stackView.push(confirm)
                                        bridge.showKeyboard()
                                    } else {
                                        txtError.text = main.errorCode
                                    }
                                } else {
                                    txtError.text = main.errorEmptyFields
                               }
                            } else {
                                txtError.text = main.errorEmptyFields
                            }
                        } else {
                            txtError.text = main.errorEmptyFields
                        }
                    }
                }
            }
        }
        Item {
            id: container
            width: parent.width
            height: 20

            Text {
                id: txtError
                color: "red"
                opacity: 0
                anchors.centerIn: parent
                onTextChanged: {
                    txtError.opacity = txtError.text != "" ? 1 : 0
                }
            }
        }
    }
}

