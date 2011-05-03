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
#include "corepo.h"
#include "costats.h"
#include "codiff.h"
#include "coref.h"
#include "cotree.h"

#include <QRegExp>

CoCommit::CoCommit(CoRepo* repo, QString id, QString tree,CoActor author, QDateTime authored_date, CoActor committer,QDateTime committed_date, QString message,QStringList parents):CoObject(repo, id, CoObject::Commit)
{
	m_tree = tree;
	m_author = author;
	m_authoredDate = authored_date;
	m_committer = committer;
	m_committedDate = committed_date;
	m_message = message;
	m_parentsIds = parents;
	m_parentsList = QList<CoCommit*>();
}

CoCommit::CoCommit(CoRepo* repo, QString id):CoObject(repo, id, CoObject::Commit)
{
	QStringList cmd;
	cmd << "cat-file" << id;
	CoKwargs opts;
	opts.insert("p","");
	QString out;
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	if(success)
	{
		QStringList lines = out.split("\n");
		QStringList messages;
		if(!lines.isEmpty())
		{
			m_tree = lines.takeFirst().trimmed().split(QRegExp("\\s+")).last();
			while(!lines.isEmpty() && lines.first().startsWith("parent"))
				m_parentsIds.append(lines.takeFirst().trimmed().split(QRegExp("\\s+")).last());
			QStringList lineSplit = lines.takeFirst().trimmed().split(QRegExp("\\s+"));
			lineSplit.removeFirst();
			lineSplit.removeLast();
			m_authoredDate = QDateTime::fromTime_t(lineSplit.takeLast().toUInt());
			m_author = CoActor(lineSplit.join(" "));

			lineSplit.clear();
			lineSplit = lines.takeFirst().trimmed().split(QRegExp("\\s+"));
			lineSplit.removeFirst();
			lineSplit.removeLast();
			m_committedDate = QDateTime::fromTime_t(lineSplit.takeLast().toUInt());
			m_committer = CoActor(lineSplit.join(" "));
			if(!lines.isEmpty() && lines.first().trimmed().isEmpty())
				while(!lines.isEmpty())
					messages.append(lines.takeFirst().trimmed());
			m_message = messages.join("\n");
		}
		m_parentsList = QList<CoCommit*>();
	}
}

CoCommit::~CoCommit()
{
}

QList<CoCommit*> CoCommit::parents()
{
	if(m_parentsIds.isEmpty())
		return QList<CoCommit*>();
	if(m_parentsList.isEmpty())
	{
		QString parentId;
		foreach(parentId,m_parentsIds)
		{
			m_parentsList.append(new CoCommit(repo(),parentId));
		}
	}
	return m_parentsList;
}

const QString CoCommit::tree() const
{
	return m_tree;
}

const CoActor CoCommit::author() const
{
	return m_author;
}

const QDateTime CoCommit::authoredDate() const
{
	return m_authoredDate;
}

const CoActor CoCommit::committer() const
{
	return m_committer;
}

const QDateTime CoCommit::committedDate() const
{
	return m_committedDate;
}

const QString CoCommit::idAbbrev() const
{
	return id().left(7);
}

const QString CoCommit::summary() const
{
	return m_message.split("\n").at(0);
}

const QString CoCommit::message() const
{
	return m_message;
}

QList<CoDiff*> CoCommit::diffs()
{
	if(m_parentsIds.isEmpty())
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

const CoStats* CoCommit::stats()
{
	QString out;
	if(m_parentsIds.isEmpty())
	{
		QStringList cmd;
		cmd << "diff-tree" << id();
		CoKwargs opts;
		opts.insert("numstat","");
		opts.insert("root","");
		bool success = repo()->repoGit()->execute(cmd, opts, &out);
		QStringList tmp = out.split("\n");
		tmp.removeFirst();
		out = tmp.join("\n");
	}
	else
	{
		QStringList cmd;
		cmd << "diff" << m_parentsIds.first() << id();
		CoKwargs opts;
		opts.insert("numstat","");
		bool success = repo()->repoGit()->execute(cmd, opts, &out);
	}
	return new CoStats::CoStats(repo(), out); 
}

//const CoStats* CoCommit::stats() const
//{
	//QString out;
	//if(m_parentsIds.isEmpty())
	//{
		//QStringList cmd;
		//cmd << "diff-tree" << id();
		//CoKwargs opts;
		//opts.insert("numstat","");
		//opts.insert("root","");
		//bool success = repo()->repoGit()->execute(cmd, opts, &out);
		//QString out2 ="";
		//QString str;
		//foreach(str, out.split("\n").removeFirst())
		//{
			//QStringList strSplit = str.trimmed().split("\t");
			//out2 += "%1\t%2\t%3\n";
			//out2.arg(strSplit.at(0)).arg(strSplit.at(1)).arg(strSplit.at(2));
		//}
		//out = out2;
	//}
	//else
	//{
		//QStringList cmd;
		//cmd << "diff" << m_parentsIds.first() << id();
		//CoKwargs opts;
		//opts.insert("numstat","");
		//bool success = repo()->repoGit()->execute(cmd, opts, &out);
	//}
	//return new CoStats::CoStats(repo(), out); 
//}

int CoCommit::commitsCount(CoRepo* repo,QString ref, QString path)
{
	QStringList cmd;
	cmd << "rev-list" << ref;
   if(!path.isEmpty())
   {
		cmd << "--" << path;
   }
	QString out;
	bool sucess = repo->repoGit()->execute(cmd, CoKwargs(), &out);
	return out.trimmed().split("\n").size();
}

int CoCommit::commitsCount(CoRepo* repo, CoRef* ref, QString path)
{
	return commitsCount(repo, ref->name(), path);
}

int CoCommit::commitsCount(CoRepo* repo, CoCommit* ref, QString path)
{
	return commitsCount(repo, ref->id(), path);
}

QList<CoCommit*> CoCommit::findAllCommits(CoRepo* repo, QString ref, CoKwargs opts, QString path)
{
	QStringList cmd;
	cmd << "rev-list" << ref;
	if(!path.isEmpty())
	{
		cmd << "--" << path;
	}
	opts.insert("pretty","raw");
	QString out;
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	return listCommitsFromString(repo, out);
}

QList<CoCommit*> CoCommit::listCommitsFromString(CoRepo* repo, QString text)
{
	QStringList lines;
	QString str;
	foreach(str, text.split("\n"))
	{
		if(!str.trimmed().isEmpty())
		{
			lines.append(str);
		}
	}
	QList<CoCommit*> commits;
	while(!lines.isEmpty())
	{
		QString id = lines.takeFirst().trimmed().split(QRegExp("\\s+")).at(1);
		QString tree = lines.takeFirst().trimmed().split(QRegExp("\\s+")).at(1);
		QStringList parents;
		while(!lines.isEmpty() && lines.first().startsWith("parent"))
			parents.append(lines.takeFirst().trimmed().split(QRegExp("\\s+")).last());
		QStringList lineSplit = lines.takeFirst().trimmed().split(QRegExp("\\s+"));
		lineSplit.removeFirst();
		lineSplit.removeLast();
		QDateTime authorTime = QDateTime::fromTime_t(lineSplit.takeLast().toUInt());
		CoActor	authorInfo = CoActor::CoActor(lineSplit.join(" "));
		
		lineSplit.clear();
		lineSplit = lines.takeFirst().trimmed().split(QRegExp("\\s+"));
		lineSplit.removeFirst();
		lineSplit.removeLast();
		QDateTime committerTime = QDateTime::fromTime_t(lineSplit.takeLast().toUInt());
		CoActor	committerInfo = CoActor::CoActor(lineSplit.join(" "));
		QStringList messages;
		while(!lines.isEmpty() && lines.first().startsWith(" "))
			messages.append(lines.takeFirst().trimmed());
		QString message = messages.join("\n");
		commits.append(new CoCommit(repo, id, tree, authorInfo, authorTime, committerInfo, committerTime, message, parents));
	}
	return commits;
}

QList<CoDiff*> CoCommit::makeDiff(CoRepo* repo, QString a, QString b, QStringList paths)
{
	if(!paths.isEmpty())
		paths.prepend("--");
	if(!b.isEmpty())
		paths.prepend(b);
	paths.prepend(a);
	
	QStringList cmd;
	cmd << "diff" << paths;
	CoKwargs opts;
	opts.insert("M","");
	opts.insert("full-index","");
	QString out;
	bool success = repo->repoGit()->execute(cmd, opts, &out);
	if(success)
		return CoDiff::diffsFromString(repo, out);
}

QList<CoDiff*> CoCommit::makeDiff(CoRepo* repo, CoCommit* a, CoCommit* b, QStringList paths)
{
	if(!b)
		return makeDiff(repo, a->id(), b->id(), paths);
	else
		return makeDiff(repo, a->id(), "", paths);
}

QList<CoDiff*> CoCommit::makeDiff(CoRepo* repo, CoTree* a, CoTree* b, QStringList paths)
{
	if(!b)
		return makeDiff(repo, a->id(), b->id(), paths);
	else
		return makeDiff(repo, a->id(), "", paths);
}

