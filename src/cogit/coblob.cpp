/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coblob.cpp
 *	\brief CoBlob类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "coblob.h"
#include "corepo.h"
#include "cocommit.h"

#include <QFileInfo>
#include <QRegExp>

CoBlob::CoBlob(CoRepo *repo, QString id, qint32 mode, QString name):CoObject(repo,id,CoObject::Blob)
{
	m_mode = mode;
	m_name = name;
	m_size = -1;
	m_data = "";
}

CoBlob::~CoBlob()
{
}

const qint32 CoBlob::mode() const
{
	return m_mode;
}

const QString CoBlob::name() const
{
	return m_name;
}

const int CoBlob::size()
{
	if(m_size < 0)
	{
		QStringList cmd;
		cmd << "cat-file" << id();
		CoKwargs opts;
		opts.insert("s","");
		QString out,error;
		bool success = repo()->repoGit()->execute(cmd, opts, &out, &error);
		if(success)
			m_size =  out.trimmed().toInt();
	}
	return m_size;
}

const QString CoBlob::data()
{
	if(m_data.isEmpty())
	{
		QStringList cmd;
		cmd << "cat-file" << id();
		CoKwargs opts;
		opts.insert("p","");
		QString out,error;
		bool success = repo()->repoGit()->execute(cmd, opts, &out, &error);
		if(success)
			m_data =  out;
	}
	return m_data;
}

const QString CoBlob::baseName() const
{
	QString base;
	QFileInfo fi(m_name);
	base = fi.completeBaseName();
	return base;
}

const QString CoBlob::mimeType() const
{
	//TODO
}

const QString CoBlob::getDataFromId(CoRepo* repo, QString id)
{
	QStringList cmd;
	cmd << "cat-file" << id;
	CoKwargs opts;
	opts.insert("p","");
	QString out,error;
	bool success = repo->repoGit()->execute(cmd, opts, &out, &error);
	if(success)
		return out;
}

const CoBlames CoBlob::blame(CoRepo* repo,const CoCommit* commit,const QString file)
{
	QStringList cmd;
	cmd << "cat-file" << commit->id() << "--" << file;
	CoKwargs opts;
	opts.insert("p", "");
	QString out, error;
	bool success = repo->repoGit()->execute(cmd, opts, &out, &error);
	if(!success)
		return CoBlames();
	CoBlames blame;
	CoCommit* last_commit;
	QString str;
	foreach(str,out.split(QRegExp("\\n")))
	{
		str = str.trimmed();
		QRegExp commitIdRe("^[0-9A-Fa-f]{40}");
		if(commitIdRe.indexIn(str)!=-1)
		{
			str = str.trimmed();
			QRegExp re1cl("^([0-9A-Fa-f]{40})(\\d+)(\\d+)(\\d+)$");
			QRegExp recl("^([0-9A-Fa-f]{40})(\\d+)(\\d+)$");
			if(re1cl.indexIn(str)!=-1)
			{
				last_commit = new CoCommit(repo,re1cl.cap(1));
				blame.insert(last_commit,re1cl.cap(3).toInt());
			}
			else if(recl.indexIn(str)!=-1)
			{
				blame.insert(last_commit,recl.cap(3).toInt());
			}
		}
	}
	return blame;
}

