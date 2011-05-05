 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cotag.cpp
 *	\brief CoTag类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "cotag.h"
#include "corepo.h"
#include "cocommit.h"

CoTag::CoTag(CoRepo* repo, QString name, CoCommit* commit):CoRef(repo, name, commit, CoRef::Tag)
{
	m_name = name;
	m_commit = commit;
}

CoTag::CoTag(CoRepo* repo, QString name, QString commit):CoRef(repo, name, commit, CoRef::Tag)
{
	m_name = name;
	m_commit = new CoCommit(repo, commit);
}

CoTag::CoTag(CoRepo* repo, QString name):CoRef(repo, name, CoRef::Tag)
{
}

CoTag::~CoTag()
{
}

QList<CoTag*> CoTag::findAllTags(CoRepo* repo, CoKwargs opts)
{
	if(!repo->isRepo())
		return QList<CoTag*>();
	QStringList cmd;
	QList<CoTag*> tags;
	cmd << "for-each-ref" << "refs/tags";
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
				tags.append(new CoTag(repo, name, commit));
		}
	}
	return tags;
}
