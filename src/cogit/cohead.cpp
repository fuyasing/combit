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
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "cohead.h"

CoHead::CoHead(CoRepo* repo, QString name, CoCommit* commit):CoRef(repo, name, commit, CoRefType::Head)
{
	m_name = name;
	m_commit = commit;
}

CoHead::CoHead(CoRepo* repo, QString name, QString commit):CoRef(repo, name, commit, CoRefType::Head)
{
	m_name = name;
	m_commit = new CoCommit(repo, commit);
}

CoHead::CoHead(CoRepo* repo,QString name):CoRef(repo, name, CoRefType::Head)
{
}

CoHead::~CoHead()
{

}

const CoCommit* CoHead::update()
{
	CoKwargs opts.insert("hash","");
	QStringList cmd << "show-ref" << "refs/heads/"+name();
	QString out;
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	if(success)
	{
		setCommit(out.trimmed());
	}
	return commit();
}

static QList<CoHead*> CoHead::findAllHeads(CoRepo* repo, CoKwargs opts)
{
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
