/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cogit.cpp
 *	\brief CoGit类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "cogit.h"

CoGit::CoGit(QString gitWdDir)
{
	m_gitWdDir = gitWdDir;
	m_hasProcess = false;
}
CoGit::~CoGit()
{
}
bool CoGit::execute(QStringList cmd, CoKwargs opts, QString* stdOut, QString* stdError, QString inStream, bool withExceptionsEmit)
{
	QByteArray rawStdOut, rawStdError;
	bool ret = execute(cmd,opts,stdOut?&rawStdout:NULL,stdError?&rawStdError:NULL,inStream,withExceptionsEmit);
	if(stdOut)
		*stdOut = rawStdOut;
	if(stdError)
		*stdError = rawStdError;
	return ret;
}

bool CoGit::execute(QStringList cmd, CoKwargs opts, QByteArray* stdOut, QByteArray* stdError, QString inStream, bool withExceptionsEmit);
{
	//一次只允许执行一个子进程
	if(m_hasProcess)
		return false;
	m_hasProcess = true;
	CoProcess p(this, m_gitWdDir);
	connect(this,SIGNAL(cancelProcess()),&p,SLOT(onCancel()));
	if(withExceptionsEmit)
		connect(&p,SIGNAL(exceptionOccur(CoError::ErrorType)),this,SLOT(onExcuteExceptionOccur(CoError::ErrorType)));
	if(!opts.isEmpty())
		cmd += transformKwargs(opts);
	cmd.prepend("git");
	bool ret = p.runSync(cmd,stdOut,stdError,inStream);
	m_hasProcess = false;
	return ret;
}

void CoGit::onExcuteExcptionOccur(CoError::ErrorType error)
{
	emit exceptionOccur(error);
}

void CoGit::cancel()
{
	emit cancelProcess();
}

QStringList CoGit::transformKwargs(CoKwargs opts)
{
	QStringList args();
	CoKwargs::const_iterator i = opts.constBegin();
	while(i != opts.constEnd())
	{
		if(i.key().size() == 1)
		{
			if(i.value().isEmpty())
				args << QString("-%1").arg(i.key());
			else
				args << QString("-%1%2").arg(i.key()).arg(i.value());
		}
		else
		{
			if(i.value().isEmpty())
				args << QString("--%1").arg(CoUtils::dashify(i.key()));
			else
				args << QString("--%1=%2").arg(CoUtils::dashify(i.key())).arg(i.value());
		}
	}
	return args;
}
