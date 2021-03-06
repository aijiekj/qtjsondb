/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtJsonDb 1.0 as JsonDb
import "content"

Rectangle {
    width: 400
    height: 300
    property int fontsize: 20
    color: "black";

    JsonDb.Partition {
        id: systemPartition
    }

    RssModel {
        id: rssModel
        function createCallback(error, response) {
            if (error) {
                console.log("Error Creating image "+error.code+" "+error.message);
                return;
            }
            for (var i = 0; i < response.items.length; i++) {
                responses.append(response.items[i]);
                console.log("Created Object : "+JSON.stringify(response.items[i]));
            }
        }

        onStatusChanged: {
            console.log("onStatusChange status=" + status);
            if (rssModel.status == 1) {
                for (var i = 0; i < rssModel.count; i++) {
                    var obj = rssModel.get(i);
                    obj['_type'] = "FlickrImage";
                    //console.log("i=" + i + " " + JSON.stringify(obj));
                    systemPartition.create(obj, createCallback);
                }
            }
        }
    }

    ListModel {
        id: responses
    }
    ListView {
        id: listView
        anchors.top: parent.top
        anchors.bottom: toolBar.top
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        width: parent.width
        model: responses
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 ;width: 200;}
        focus: true
        delegate: Row {
            spacing: 10
            Text {
                text: _uuid
                font.pointSize: fontsize
                color: "white"
            }
        }
    }

    ToolBar {
        id: toolBar
        height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        button1Label: "Update";
        onButton1Clicked: rssModel.reload()
    }

}
