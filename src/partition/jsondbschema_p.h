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

#include <QtCore/qlist.h>
#include <QtCore/qvarlengtharray.h>
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>
#include <QtCore/qshareddata.h>

#ifndef JSONDB_SCHEMA_P_H
#define JSONDB_SCHEMA_P_H

QT_BEGIN_HEADER

namespace SchemaValidation {

template<class T>
class SchemaPrivate;

template<class T>
class Schema {
    typedef typename T::Value Value;
    typedef typename T::Key Key;
    typedef typename T::Object Object;
    typedef typename T::ValueList ValueList;
    typedef typename T::Service Service;

public:
    inline bool check(const Value &value, Service *callbackToUseForCheck) const;

    Schema()
        : d_ptr(new SchemaPrivate<T>())
    {}

    Schema(const Object& schema, Service *callbacksToUseForCompilation)
        : d_ptr(new SchemaPrivate<T>())
    {
        d_ptr->compile(schema, callbacksToUseForCompilation);
    }

    bool isValid() const
    {
        return d_ptr->isValid();
    }
private:

    friend class SchemaPrivate<T>;
    QExplicitlySharedDataPointer<SchemaPrivate<T> > d_ptr;
};

template<class T>
class SchemaPrivate : public QSharedData
{
    typedef typename Schema<T>::Value Value;
    typedef typename Schema<T>::Key Key;
    typedef typename Schema<T>::Object Object;
    typedef typename Schema<T>::ValueList ValueList;
    typedef typename Schema<T>::Service Service;

    class Check {
    public:
        Check(SchemaPrivate *schema, const char* errorMessage)
            : m_schema(schema)
            , m_errorMessage(errorMessage)
        {
            Q_ASSERT(schema);
            Q_ASSERT(errorMessage);
        }
        virtual ~Check() {}
        bool check(const Value& value)
        {
            bool result = doCheck(value);
            if (!result) {
                bool ok;
                // TODO it is tricky, as we do not have access to source code of this schema.
                // maybe we can set "additional, hidden " source property in each schema property, or some nice hash?
                m_schema->m_callbacks->setError(QString::fromLatin1("Schema validation error: %1")
                                                .arg(QString::fromLatin1(m_errorMessage).arg(value.toString(&ok))));
            }
            return result;
        }

    protected:
        SchemaPrivate *m_schema;
        // return true if it is ok
        virtual bool doCheck(const Value&) = 0;
    private:
        const char *m_errorMessage;
    };

    // empty check
    class NullCheck;
    // 5.1
    class CheckType;
    // 5.2
    class CheckProperties;
    // 5.5
    class CheckItems;
    // 5.7
    class CheckRequired;
    // 5.9
    class CheckMinimum;
    // 5.10
    class CheckMaximum;
    // 5.11
    class CheckExclusiveMinimum;
    // 5.12
    class CheckExclusiveMaximum;
    // 5.13
    class CheckMinItems;
    // 5.14
    class CheckMaxItems;
    // 5.16
    class CheckPattern;
    // 5.17
    class CheckMinLength;
    // 5.18
    class CheckMaxLength;
    // 5.21
    class CheckTitle;
    // 5.23
    class CheckFormat;
    // 5.26
    class CheckExtends;
    // 5.28
    class CheckRef;
    class CheckDescription;

    inline Check *createCheckPoint(const Key &key, const Value &value);
    inline bool check(const Value &value) const;

public:
    SchemaPrivate()
        : m_maxRequired(0)
        , m_requiredCount(0)
        , m_callbacks(0)
    {}
    ~SchemaPrivate()
    {
        for (int i = 0; i < m_checks.count(); ++i)
            delete m_checks.at(i);
    }

    inline bool check(const Value &value, Service *callbackToUseForCheck) const;
    inline void compile(const Object &schema, Service *callbackToUseForCompile)
    {
        Q_ASSERT(callbackToUseForCompile);
        m_callbacks = callbackToUseForCompile;
        const QList<Key> checksKeys = schema.propertyNames();
        m_checks.reserve(checksKeys.count());
        foreach (const Key &key, checksKeys) {
            m_checks.append(createCheckPoint(key, schema.property(key)));
        }
        m_callbacks = 0;
    }

    bool isValid() const
    {
        // we have some checks so it means that something got compiled.
        return m_checks.size();
    }

private:
    QVarLengthArray<Check *, 4> m_checks;
    qint32 m_maxRequired;
    mutable qint32 m_requiredCount;
    mutable Service *m_callbacks;
};

}

#include "jsondbcheckpoints_p.h"

QT_END_HEADER

#endif // JSONDB_SCHEMA_P_H
