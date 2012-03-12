/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QTextStream>
#include <QThread>

#include <stdlib.h>

#include "chatclient.h"

class CommandInterface : public QObject
{
    Q_OBJECT
public:
    CommandInterface(ChatClient *client);

public Q_SLOTS:
    void interactive();

private:
    ChatClient *m_client;
};

CommandInterface::CommandInterface(ChatClient *client) :
    m_client(client)
{
}

void CommandInterface::interactive()
{
    QTextStream qin(stdin, QFile::ReadOnly);
    const char *prompt = "jsondb-chat> ";

    forever {
        QString line;

        printf("%s", prompt);
        fflush(stdout);

        line = qin.readLine();
        if (line.isNull())
            break;

        line = line.trimmed();

        if (line.isEmpty())
            continue;

        QStringList args = line.split(QLatin1Char(' '));
        QString method = args.takeFirst();

        if (method != QLatin1String("quit")) {
            QMetaObject::invokeMethod(m_client, method.toLatin1(), Q_ARG(QStringList, args));
            QThread::currentThread()->usleep(1000);
            continue;
        }

        QThread::currentThread()->quit();
        return;
    }
}

static int usage(const QString &name)
{
    fprintf(stderr, "Usage: %s [OPTIONS] USERNAME\n", qPrintable(name));
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "-name NAME\t\tspecify your real name\n");
    fprintf(stderr, "\n");
    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QStringList args(app.arguments());
    QString applicationName = QFileInfo(args.takeFirst()).fileName();

    QString realName;

    while (!args.isEmpty()) {
        if (!args.first().startsWith(QLatin1Char('-')))
            break;

        QString arg(args.takeFirst());
        if (arg == QLatin1String("-name") && !args.isEmpty()) {
            realName = args.takeFirst();
            continue;
        }

        return usage(applicationName);
    }

    if (args.isEmpty())
        return usage(applicationName);

    QString name = args.takeFirst();

    if (!args.isEmpty())
        return usage(applicationName);

    ChatClient client(name, realName);
    CommandInterface interface(&client);
    QThread inputThread;

    interface.moveToThread(&inputThread);
    QObject::connect(&inputThread, SIGNAL(started()), &interface, SLOT(interactive()));
    QObject::connect(&inputThread, SIGNAL(finished()), &app, SLOT(quit()));
    inputThread.start();

    return app.exec();
}

#include "main.moc"