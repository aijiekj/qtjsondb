/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtAddOn.JsonDb module of the Qt Toolkit.
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

#ifndef QJSONDB_WRITE_REQUEST_H
#define QJSONDB_WRITE_REQUEST_H

#include <QtCore/QObject>
#include <QtCore/QJsonObject>

#include <QtJsonDb/qjsondbrequest.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE_JSONDB

class QJsonDbWriteRequestPrivate;
class Q_JSONDB_EXPORT QJsonDbWriteRequest : public QJsonDbRequest
{
    Q_OBJECT
    Q_PROPERTY(QList<QJsonObject> objects READ objects WRITE setObjects)
    Q_PROPERTY(QJsonDbWriteRequest::ConflictResolutionMode conflictResolutionMode READ conflictResolutionMode WRITE setConflictResolutionMode)

    Q_PROPERTY(quint32 stateNumber READ stateNumber)

public:
    QJsonDbWriteRequest(QObject *parent = 0);
    ~QJsonDbWriteRequest();

    enum ErrorCode {
        NoError = QJsonDbRequest::NoError,
        InvalidRequest = QJsonDbRequest::InvalidRequest,
        OperationNotPermitted = QJsonDbRequest::OperationNotPermitted,
        InvalidPartition = QJsonDbRequest::InvalidPartition,
        DatabaseConnectionError = QJsonDbRequest::DatabaseConnectionError,
        PartitionUnavailable = QJsonDbRequest::PartitionUnavailable,
        MissingObject = QJsonDbRequest::MissingObject,
        DatabaseError = QJsonDbRequest::DatabaseError,
        MissingUUID = QJsonDbRequest::MissingUUID,
        MissingType = QJsonDbRequest::MissingType,
        UpdatingStaleVersion = QJsonDbRequest::UpdatingStaleVersion,
        FailedSchemaValidation = QJsonDbRequest::FailedSchemaValidation,
        InvalidMap = QJsonDbRequest::InvalidMap,
        InvalidReduce = QJsonDbRequest::InvalidReduce,
        InvalidSchemaOperation = QJsonDbRequest::InvalidSchemaOperation,
        InvalidIndexOperation = QJsonDbRequest::InvalidIndexOperation,
        InvalidType = QJsonDbRequest::InvalidType
    };

    enum ConflictResolutionMode {
        RejectStale = 0,
        Replace = 1
        //Merge = 2
    };

    void setObject(const QJsonObject &object)
    { setObjects(QList<QJsonObject>() << object); }
    void setObjects(const QList<QJsonObject> &);
    QList<QJsonObject> objects() const;

    void setConflictResolutionMode(ConflictResolutionMode mode);
    ConflictResolutionMode conflictResolutionMode() const;

    // read request results. Data is only available after started() was emitted.
    quint32 stateNumber() const;

private:
    Q_DISABLE_COPY(QJsonDbWriteRequest)
    Q_DECLARE_PRIVATE(QJsonDbWriteRequest)
    friend class QJsonDbConnectionPrivate;
};

class Q_JSONDB_EXPORT QJsonDbCreateRequest : public QJsonDbWriteRequest
{
    Q_OBJECT
public:
    QJsonDbCreateRequest(const QJsonObject &object, QObject *parent = 0);
    QJsonDbCreateRequest(const QList<QJsonObject> &objects, QObject *parent = 0);
};

class Q_JSONDB_EXPORT QJsonDbUpdateRequest : public QJsonDbWriteRequest
{
    Q_OBJECT
public:
    QJsonDbUpdateRequest(const QJsonObject &object, QObject *parent = 0);
    QJsonDbUpdateRequest(const QList<QJsonObject> &objects, QObject *parent = 0);
};

class Q_JSONDB_EXPORT QJsonDbRemoveRequest : public QJsonDbWriteRequest
{
    Q_OBJECT
public:
    QJsonDbRemoveRequest(const QJsonObject &object, QObject *parent = 0);
    QJsonDbRemoveRequest(const QList<QJsonObject> &objects, QObject *parent = 0);
};

QT_END_NAMESPACE_JSONDB

QT_END_HEADER

#endif // QJSONDB_WRITE_REQUEST_H
