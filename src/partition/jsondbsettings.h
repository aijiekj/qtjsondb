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

#ifndef JSONDB_SETTINGS_H
#define JSONDB_SETTINGS_H

#include "jsondbpartitionglobal.h"

#include <QObject>
#include <QStringList>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE_JSONDB_PARTITION

#define jsondbSettings JsonDbSettings::instance()

class Q_JSONDB_PARTITION_EXPORT JsonDbSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool rejectStaleUpdates READ rejectStaleUpdates WRITE setRejectStaleUpdates)
    Q_PROPERTY(bool debug READ debug WRITE setDebug)
    Q_PROPERTY(bool verbose READ verbose WRITE setVerbose)
    Q_PROPERTY(bool performanceLog READ performanceLog WRITE setPerformanceLog)
    Q_PROPERTY(int cacheSize READ cacheSize WRITE setCacheSize)
    Q_PROPERTY(int compactRate READ compactRate WRITE setCompactRate)
    Q_PROPERTY(bool enforceAccessControl READ enforceAccessControl WRITE setEnforceAccessControl)
    Q_PROPERTY(int transactionSize READ transactionSize WRITE setTransactionSize)
    Q_PROPERTY(bool validateSchemas READ validateSchemas WRITE setValidateSchemas)
    Q_PROPERTY(bool softValidation READ softValidation WRITE setSoftValidation)
    Q_PROPERTY(int syncInterval READ syncInterval WRITE setSyncInterval)
    Q_PROPERTY(int indexSyncInterval READ indexSyncInterval WRITE setIndexSyncInterval)
    Q_PROPERTY(bool debugQuery READ debugQuery WRITE setDebugQuery)
    Q_PROPERTY(QStringList configSearchPath READ configSearchPath WRITE setConfigSearchPath)

public:
    static JsonDbSettings *instance();

    inline void reload() { loadEnvironment(); }

    inline bool rejectStaleUpdates() const { return mRejectStaleUpdates; }
    inline void setRejectStaleUpdates(bool reject) { mRejectStaleUpdates = reject; }

    inline bool debug() const { return mDebug; }
    inline void setDebug(bool debug) { mDebug = debug; }

    inline bool verbose() const { return mVerbose; }
    inline void setVerbose(bool verbose) { mVerbose = verbose; }

    inline bool performanceLog() const { return mPerformanceLog; }
    inline void setPerformanceLog(bool performanceLog) { mPerformanceLog = performanceLog; }

    inline int cacheSize() const { return mCacheSize; }
    inline void setCacheSize(int cacheSize) { mCacheSize = cacheSize; }

    inline int compactRate() const { return mCompactRate; }
    inline void setCompactRate(int compactRate) { mCompactRate = compactRate; }

    inline bool enforceAccessControl() const { return mEnforceAccessControl; }
    inline void setEnforceAccessControl(bool enforce) { mEnforceAccessControl = enforce; }

    inline int transactionSize() const { return mTransactionSize; }
    inline void setTransactionSize(int transactionSize) { mTransactionSize = transactionSize; }

    inline bool validateSchemas() const { return mValidateSchemas; }
    inline void setValidateSchemas(bool validate) { mValidateSchemas = validate; }

    inline bool softValidation() const { return mSoftValidation; }
    inline void setSoftValidation(bool soft) { mSoftValidation = soft; }

    inline int syncInterval() const { return mSyncInterval; }
    inline void setSyncInterval(int interval) { mSyncInterval = interval; }

    inline int indexSyncInterval() const { return mIndexSyncInterval; }
    inline void setIndexSyncInterval(int interval) { mIndexSyncInterval = interval; }

    inline bool debugQuery() const { return mDebugQuery; }
    inline void setDebugQuery(bool debug) { mDebugQuery = debug; }

    inline QStringList configSearchPath() const { return mConfigSearchPath; }
    inline void setConfigSearchPath(const QStringList &searchPath) { mConfigSearchPath = searchPath; }

    JsonDbSettings();

private:
    void loadEnvironment();

    bool mRejectStaleUpdates;
    bool mDebug;
    bool mVerbose;
    bool mPerformanceLog;
    int mCacheSize;
    int mCompactRate;
    bool mEnforceAccessControl;
    int mTransactionSize;
    bool mValidateSchemas;
    bool mSoftValidation;
    int mSyncInterval;
    int mIndexSyncInterval;
    bool mDebugQuery;
    QStringList mConfigSearchPath;
};

QT_END_NAMESPACE_JSONDB_PARTITION

QT_END_HEADER

#endif // JSONDB_SETTINGS_H
