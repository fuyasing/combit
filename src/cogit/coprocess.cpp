 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coprocess.cpp
 *	\brief CoProcess类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "coprocess.h"
#include "cogit.h"

#include <QByteArray>

CoProcess::CoProcess(CoGit *git,const QString& wd):QProcess(git)
{
	m_gitWdDir = wd;
	m_stdOut = NULL;
	m_stdError = NULL;
	m_inStream = "";
	canceling = isWinShell = isErrorExit = false;
}
bool CoProcess::runSync(QStringList cmd, QByteArray* stdOut, QByteArray* stdError, QString inStream)
{
	m_cmd = cmd;
	m_stdOut = stdOut;
	m_stdError = stdError;
	m_inStream = inStream;
	if(m_stdOut)
		m_stdOut->clear();
	if(m_stdError)
		m_stdError->clear();
	if(!m_inStream.isEmpty())
		setStandardInputFile(m_inStream);

	setupSignals();

	if (!startProcess(m_cmd))
		return false;

	busy = true;

	while(busy)
	{
		waitForFinished(20);
	}
	return !isErrorExit;

}

void CoProcess::setupSignals()
{
	connect(this, SIGNAL(readyReadStandarOutput()),
			this,SLOT(onReadyReadStandardOutput()));
	connect(this,SIGNAL(readyReadStandardError()),
			this,SLOT(onReadyReadStandardError()));
	connect(this, SIGNAL(finished(int,QProcess::ExitStatus)),
			this,SLOT(onFinished(int,QProcess::ExitStatus)));
}

void CoProcess::sendExceptionSignal()
{
	emit exceptionOccur(CoErrors::GitCommandError);
}

bool CoProcess::startProcess(QStringList cmd)
{
	setWorkingDirectory(m_gitWdDir);
	start(cmd.takeFirst(),cmd);
	if(!waitForStarted())
	{
		m_stdError->append("Unable to start the process!");
		sendExceptionSignal();
		return false;
	}
	return true;
}

void CoProcess::onCancel()
{
	canceling = true;
#ifdef Q_OS_WIN32
	kill();
#else
	terminate();
#endif
	waitForFinished();
}

void CoProcess::onReadyReadStandardOutput()
{
	if(canceling)
		return;
	if(m_stdOut)
		m_stdOut->append(readAllStandardOutput());
	return;
}

void CoProcess::onReadyReadStandardError()
{
	if(canceling)
		return;
	if(m_stdError)
		m_stdError->append(readAllStandardError());
	return;
}

void CoProcess::onFinished(int exitCode,QProcess::ExitStatus exitStatus)
{
	isErrorExit = (exitStatus != QProcess::NormalExit)
		|| (exitCode !=0 && isWinShell)
		|| !m_stdError->isEmpty()
		|| canceling;

	if(!canceling)
	{
		if (isErrorExit)
			sendExceptionSignal();
	}
	busy = false;
}
