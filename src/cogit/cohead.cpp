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

CoHead::CoHead():CoRef(NULL,"",NULL,CoRef::Head)
{
}
CoHead::CoHead(CoRepo* repo, QString name, CoCommit* commit):CoRef(repo, name, commit, CoRef::Head)
{
}

CoHead::CoHead(CoRepo* repo, QString name, QString commit):CoRef(repo, name, commit, CoRef::Head)
{
}

CoHead::CoHead(CoRepo* repo,QString name):CoRef(repo, name, CoRef::Head)
{
}

CoHead::~CoHead()
{

}

bool CoHead::isValid() const
{
	return CoRef::isValid();
}

CoCommit* CoHead::update()
{
	if(!isValid())
		return NULL;
	CoKwargs opts;
	opts.insert("hash","");
	QStringList cmd;
	cmd<< "show-ref" << "refs/heads/" + name();
	QString out, error;
	bool success = repo()->repoGit()->execute(cmd, opts, &out, &error);
	if(success)
	{
		setCommit(out.trimmed());
	}
	return commit();
}

QList<CoHead*> CoHead::findAllHeads(CoRepo* repo, CoKwargs opts)
{
	if(repo == NULL || !repo->isRepo())
		return QList<CoHead*>();
	QStringList cmd;
	QList<CoHead*> heads;
	cmd << "for-each-ref" << "refs/heads";
	opts.insert("sort","*authordate");
	opts.insert("format","%(refname:short)%09%(objectname)");
	QString out, error;
	bool success = repo->repoGit()->execute(cmd, opts, &out, &error);
	if(success)
	{
		QString line, commit, name;
		foreach(line, out.trimmed().split("\n"))
		{
				QStringList lineSplit;
				lineSplit =  line.trimmed().split("\t");
				commit =lineSplit.last();
				name = lineSplit.first();
				heads.append(new CoHead(repo, name, commit));
		}
	}
	else
	{
	}
	return heads;
}
