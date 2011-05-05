 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cohead.cpp
 *	\brief CoHead类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "cohead.h"
#include "cocommit.h"
#include "corepo.h"

CoHead::CoHead(CoRepo* repo, QString name, CoCommit* commit):CoRef(repo, name, commit, CoRef::Head)
{
	m_name = name;
	m_commit = commit;
}

CoHead::CoHead(CoRepo* repo, QString name, QString commit):CoRef(repo, name, commit, CoRef::Head)
{
	m_name = name;
	m_commit = new CoCommit(repo, commit);
}

CoHead::CoHead(CoRepo* repo,QString name):CoRef(repo, name, CoRef::Head)
{
}

CoHead::~CoHead()
{

}

const CoCommit* CoHead::update()
{
	CoKwargs opts;
	opts.insert("hash","");
	QStringList cmd;
	cmd<< "show-ref" << "refs/heads/" + name();
	QString out;
	bool success = repo()->repoGit()->execute(cmd, opts, &out);
	if(success)
	{
		setCommit(out.trimmed());
	}
	return commit();
}

QList<CoHead*> CoHead::findAllHeads(CoRepo* repo, CoKwargs opts)
{
	if(!repo->isRepo())
		return QList<CoHead*>();
	QStringList cmd;
	QList<CoHead*> heads;
	cmd << "for-each-ref" << "refs/heads";
	opts.insert("sort","*authoreddate");
	opts.insert("format","%(refname) %(objectname)");
	QString out;
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	if(success)
	{
		QString line, commit, name;
		foreach(line, out.split('\n'))
		{
				QStringList lineSplit;
				lineSplit =  line.trimmed().split(" ");
				commit =lineSplit.last();
				name = lineSplit.first().split('/').last();
				heads.append(new CoHead(repo, name, commit));
		}
	}
	return heads;
}
