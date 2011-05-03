/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coref.cpp
 *	\brief CoRef类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "coref.h"
#include "corepo.h"
#include "cocommit.h"

#include <QStringList>

CoRef::CoRef(CoRepo* repo, QString name, CoCommit* commit, CoRefType type)
{
	m_repo = repo;
	m_name = name;
	m_commit = commit;
	m_type = type;
}

CoRef::CoRef(CoRepo* repo, QString name, QString commit, CoRefType type)
{
	m_repo = repo;
	m_name = name;
	m_commit = new CoCommit(repo, commit);
	m_type = type;
}

CoRef::CoRef(CoRepo* repo,QString name, CoRefType type)
{
	m_repo = repo;
	m_name = name;
	m_type = type;

	CoKwargs opts;
	opts.insert("hash","");
	QStringList cmd;
	QString out;
	switch(type)
	{
		case Head:
			{
				cmd << "show-ref" << "refs/heads/"+name;
				break;
			}
		case Tag:
			{
				cmd << "show-ref" << "refs/tags/"+name;
				break;
			}
		default:
			break;
	}
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	if(success)
	{
		m_commit = new CoCommit(repo,out.trimmed());
	}
}

CoRef::~CoRef()
{
}

CoRepo* CoRef::repo() const
{
	return m_repo;
}

const QString CoRef::name() const
{
	return m_name;
}

const CoCommit* CoRef::commit() const
{
	return m_commit;
}

bool CoRef::setCommit(CoCommit* commit)
{
	if(m_commit)
		delete m_commit;
	m_commit = commit;
	return true;
}
bool CoRef::setCommit(QString commit)
{
	if(m_commit)
		delete m_commit;
	m_commit = new CoCommit(m_repo, commit);
	return true;
}
