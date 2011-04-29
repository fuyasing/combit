 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cocommit.cpp
 *	\brief CoCommit类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "cocommit.h"

CoCommit::CoCommit(CoRepo* repo, QString id, CoTree* tree,CoActor author, QDate authored_date, CoActor committer,QDate committed_date, QString message,QList<CoCommit*> parents):CoObject(repo, id, CoObject::Commit)
{
	m_tree = tree;
	m_author = author;
	m_authoredDate = authored_date;
	m_committer = committer;
	m_committedDate = committed_date;
	m_message = message;
	m_parentsList = parents;
}

CoCommit::CoCommit(CoRepo* repo, QString id)
{
	//TODO
}

CoCommit::~CoCommit()
{
}

QList<CoCommit*> CoCommit::parents() const
{
	return m_parentsList;
}

const CoTree* CoCommit::tree() const
{
	return m_tree;
}

const CoActor CoCommit::author() const
{
	return m_author;
}

const QDate CoCommit::authoredDate() const
{
	return m_authoredDate;
}

const CoActor CoCommit::committer() const
{
	return m_committer;
}

const QDate CoCommit::committedDate() const
{
	return m_committedDate;
}

const QString CoCommit::idAbbrev() const
{
	return id().left(7);
}

const QString CoCommit::summary() const
{
	return m_message.split(QRegExp("\\n")).at(0);
}

const QString CoCommit::message() const
{
	return m_message;
}

QList<CoDiff*> CoCommit::diffs() const
{
	if(m_parentsList.isEmpty())
	{
		QStringList cmd;
		cmd << "show" << id();
		CoKwargs opts;
		opts.insert("M","");
		opts.insert("full-index","");
		opts.insert("pretty","raw");
		QString out;
		bool success = repo()->repoGit()->execute(cmd, opts, &out);
		if(success)
		{
			QRegExp re1("diff --git a");
			int start = re1.indexIn(out);
			if(start !=-1)
			{
				out = out.right(out.size() - start);
			}
			else
			{
				out = "";
			}
			return CoDiff::diffsFromString(repo(),out);
		}
	}
	else
	{
		return makeDiff(repo(),m_parentsList.first(),this);
	}
}

const CoStats* CoCommit::stats() const
{
	QString out;
	if(m_parentsList.isEmpty())
	{
		QStringList cmd;
		cmd << "diff-tree" << id();
		CoKwargs opts;
		opts.insert("numstat","");
		opts.insert("root","");
		bool success = repo()->repoGit()->execute(cmd, opts, &out);
		QString out2;
		foreach(str, out.split(QRegExp("\\n").removeFirst()))
		{
			QStringList strSplit = str.split(QRegExp("\\t"));
			out2 = "%1\t%2\t%3\n";
			out2.arg(strSplit.at(0)).arg(strSplit.at(1)).arg(strSplit.at(2));	
		}
		out = out2;
	}
	else
	{
		QStringList cmd;
		cmd << "diff" << m_parentsList.first().id() << id();
		CoKwargs opts;
		opts.insert("numstat","");
		bool success = repo()->repoGit()->execute(cmd, opts, &out);
	}
	return CoStats::CoStats(repo(), out); 
}

static int CoCommit::commitsCount(CoRepo* repo,QString ref, QString path)
{
	QStringList cmd;
	cmd << "rev-list" << ref;
   if(!path.isEmpty())
   {
		cmd << "--" << path;
   }
	QString out;
	bool sucess = repo->repoGit()->execute(cmd, CoKwargs(), &out);
	return out.trimmed().split(QRegExp("\\n")).size();
}

static int CoCommit::commitsCount(CoRepo* repo, CoRef* ref, QString path)
{
	return commitsCount(repo, ref.name(), path);
}

static int CoCommit::commitsCount(CoRepo* repo, CoCommit* ref, QString path)
{
	return commitsCount(repo, ref.id(), path);
}

static QList<CoCommit*> CoCommit::findAllCommits(CoRepo* repo, QString ref, CoKwargs kwargs, QString path)
{
	QStringList cmd;
	cmd << "rev-list" << ref;
	if(!path.isEmpty())
	{
		cmd << "--" << path;
	}
	kwargs.insert("pretty","raw");
	QString out;
	bool success = repo->repoGit()->execute(cmd, kwargs, &out);
	return listCommitsFromString(repo, out);
}

static QList<CoCommit*> CoCommit::findAllCommits(CoRepo* repo, CoRef* ref, CoKwargs kwargs, QString path)
{
	return findAllCommits(reppo, ref.name(), kwargs, path);
}

static QList<CoCommit*> CoCommit::findAllCommits(CoRepo* repo, CoCommit* ref, CoKwargs kwargs, QString path)
{
	return findAllCommits(reppo, ref.id(), kwargs, path);
}

static QList<CoCommit*> CoCommit::listCommitsFromString(CoRepo* repo, QString text)
{

}
