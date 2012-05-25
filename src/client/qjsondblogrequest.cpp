/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtAddOn.JsonDb module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qjsondblogrequest_p_p.h"
#include "qjsondbstrings_p.h"
#include "qjsondbobject.h"

#include <QJsonArray>
#include <QDebug>

QT_BEGIN_NAMESPACE_JSONDB

/*!
    \class QJsonDbLogRequest
    \inmodule QtJsonDb
    \internal

    \brief The QJsonDbLogRequest class allows clients to log messages to the JSON DB log.
*/
/*!
    \enum QJsonDbLogRequest::ErrorCode

    This enum describes database connection errors for write requests that can
    be emitted by the error() signal.

    \value NoError

    \sa error(), QJsonDbRequest::ErrorCode
*/

QJsonDbLogRequestPrivate::QJsonDbLogRequestPrivate(const QString &message, QJsonDbLogRequest *q)
    : QJsonDbRequestPrivate(q), message(message)
{
}

/*!
    Constructs a new request object with the given \a parent.
*/
QJsonDbLogRequest::QJsonDbLogRequest(const QString &message, QObject *parent)
    : QJsonDbRequest(new QJsonDbLogRequestPrivate(message, this), parent)
{
}

/*!
    Destroys the request object.
*/
QJsonDbLogRequest::~QJsonDbLogRequest()
{
}

QJsonObject QJsonDbLogRequestPrivate::getRequest() const
{
    QJsonObject request;
    request.insert(JsonDbStrings::Protocol::action(), JsonDbStrings::Protocol::log());
    request.insert(JsonDbStrings::Protocol::partition(), partition);
    request.insert(JsonDbStrings::Protocol::requestId(), requestId);

    QJsonObject object;
    object.insert(JsonDbStrings::Protocol::errorMessage(), message);
    request.insert(JsonDbStrings::Protocol::object(), object);

    return request;
}

void QJsonDbLogRequestPrivate::handleResponse(const QJsonObject &response)
{
    Q_UNUSED(response);
    Q_Q(QJsonDbLogRequest);

    setStatus(QJsonDbRequest::Receiving);
    emit q->started();
    setStatus(QJsonDbRequest::Finished);
    emit q->finished();
}

void QJsonDbLogRequestPrivate::handleError(int code, const QString &message)
{
    setError(QJsonDbRequest::ErrorCode(code), message);
}

#include "moc_qjsondblogrequest_p.cpp"

QT_END_NAMESPACE_JSONDB

