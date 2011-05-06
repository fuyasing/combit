 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file corepo.cpp
 *	\brief CoRepo类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "corepo.h"
#include "cohead.h"
#include "cotag.h"
#include "cocommit.h"
#include "coutils.h"

#include <QByteArray>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTextStream>

CoRepo::CoRepo(QString path)
{
	m_isRepo = m_isBare = false;
	m_gitPath = m_wdPath = "";
	m_git = NULL;

	QDir ePath(path);
	if(ePath.exists())
	{
		while(!ePath.isRoot())
		{
			QString pathStr = ePath.absolutePath();
			if(CoUtils::isGitDir(pathStr))
			{
				m_isBare = true;
				m_gitPath = pathStr;
				m_wdPath = pathStr;
				break;
			}
			QString gitPath = pathStr + "/.git";
			if(CoUtils::isGitDir(gitPath))
			{
				m_isBare = false;
				m_gitPath = gitPath;
				m_wdPath = pathStr;
				break;
			}
			if(!ePath.cdUp())
				break;
		}
	}
	if(!m_gitPath.isEmpty())
	{
		m_isRepo = true;
		m_git = new CoGit(m_wdPath);
	}
	else
		m_isRepo = false;
}

CoRepo::~CoRepo()
{
	if(m_git)
		delete m_git;
}

const bool CoRepo::isValid() const
{
	return m_isRepo;
}

const bool CoRepo::isRepo() const
{
	return 	m_isRepo;
}

const bool CoRepo::isBare() const
{
	return m_isBare;
}

const QString CoRepo::gitPath() const
{
	return m_gitPath;
}

const QString CoRepo::wdPath() const
{
	return m_wdPath;
}

CoGit* CoRepo::repoGit() const
{
	return m_git;
}

QString CoRepo::getDescription() const
{
	if(!isValid())
		return "";

	QString filename = m_gitPath + "/description";
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly))
		return "";

	QTextStream in(&file);
	QString description;
	while(!in.atEnd())
		description += in.readLine() + '\n';
	file.close();
	return description;
}

void CoRepo::setDescription(QString descr)
{
	if(!isValid())
		return;

	QString filename = m_gitPath + "/description";
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly))
		return;

	QTextStream out(&file);
	out << descr << '\n';
	file.close();
}

bool CoRepo::isDaemonExport()
{
	if(!isValid())
		return false;

	QString filename = m_gitPath + "/git-daemon-export-ok";
	return QFile::exists(filename);
}

void CoRepo::setDaemonExport(bool is_daemon_export)
{
	if(!isValid())
		return;

	QString filename = m_gitPath + "/git-daemon-export-ok";
	if(is_daemon_export && !isDaemonExport())
		CoUtils::touch(filename);
	else if(!is_daemon_export && isDaemonExport())
		QFile::remove(filename);
}

QStringList CoRepo::getAlternates()
{
	if(!isValid())
		return QStringList();

	QString alterPath = m_gitPath + "/objects" + "/info" + "/alternates";
	if(QFile::exists(alterPath))
	{
		QFile file(alterPath);
		if(!file.open(QIODevice::ReadOnly))
			return QStringList();

		QTextStream in(&file);
		QStringList alts;
		while(!in.atEnd())
		{
			QString line = in.readLine();
			alts.append(line);
		}
		file.close();
		return alts;
	}
	else
		return QStringList();
}

void CoRepo::setAlternates(QStringList paths)
{
	if(!isValid())
		return;

	QString alterPath = m_gitPath + "/objects" + "/info" + "/alternates";
	if(paths.isEmpty())
	{
		QFile file(alterPath);
		if(file.exists())
			file.remove(alterPath);
	}
	else
	{
		QFile file(alterPath);
		if(!file.open(QIODevice::WriteOnly))
		{
			return;
		}
		QTextStream out(&file);
		QString path;
		foreach(path, paths)
			out << '\n' << path;
		file.close();
	}
}

bool CoRepo::isDirty()
{
	if(!isValid())
		return false;

	if(m_isBare)
	{
		return false;
	}
	QStringList cmd;
	cmd << "diff" << "HEAD" << "--";
	QString out, error;
	bool success = repoGit()->execute(cmd, CoKwargs(), &out, &error);
	if(success)
	{
		return out.trimmed().size()>0;
	}
	else
	{
		return false;
	}
}

QString CoRepo::activeBranch()
{
	if(!isValid())
		return "";

	QStringList cmd;
	cmd << "symbolic-ref" << "HEAD";
	QString out, branch, error;
	branch = "";
	bool success = repoGit()->execute(cmd, CoKwargs(), &out, &error);
	if(success)
	{
		out = out.trimmed();
		if(out.startsWith("refs/heads/"))
			branch = out.section("refs/heads/", 1);
	}
	else
	{
	}
	return branch;
}

QList<CoHead*> CoRepo::branches()
{
	if(!isValid())
		return QList<CoHead*>();
	return CoHead::findAllHeads(this);
}

QList<CoTag*> CoRepo::tags()
{
	if(!isValid())
		return QList<CoTag*>();
	return CoTag::findAllTags(this);
}

QList<CoCommit*> CoRepo::commitsInBranch(QString start, QString path, int maxCount, int skip)
{
	if(!isValid() || start.isEmpty())
		return QList<CoCommit*>();
	CoKwargs opts;
	opts.insert("max-count", QString::number(maxCount));
	opts.insert("skip", QString::number(skip));
	return CoCommit::findAllCommits(this, start, opts, path);
}

QList<CoCommit*> CoRepo::commitsBetween(QString from, QString to)
{
	if(!isValid() || (from.isEmpty() && to.isEmpty()))
		return QList<CoCommit*>();
	QString ref = QString("%1..%2").arg(from).arg(to);
	return CoCommit::findAllCommits(this,ref);
}

QList<CoCommit*> CoRepo::commitsSince(QString start, QString path, QDate since)
{
	if(!isValid() || start.isEmpty())
		return QList<CoCommit*>();
	CoKwargs opts;
	QString date = QString("%1-%2-%3").arg(QString::number(since.year())).arg(QString::number(since.month())).arg(QString::number(since.day()));
	opts.insert("since",date);
	return CoCommit::findAllCommits(this,start,opts,path);
}

int CoRepo::commitCountInBranch(QString start, QString path)
{
	if(!isValid() || start.isEmpty())
		return 0;
	return CoCommit::commitsCount(this, start, path);
}

CoRepo* CoRepo::forkBare(QString path, CoKwargs opts)
{
	if(!isValid() || path.isEmpty())
		return NULL;
	QStringList cmd;
	cmd << "clone" << m_gitPath << path;
	opts.insert("bare","");
	QString out, error;
	bool success = repoGit()->execute(cmd, opts, &out, &error);
	if(success)
		return new CoRepo(path);
	else
	{
		return NULL;
	}
}

QByteArray* CoRepo::archiveTar(QString treeish, QString prefix)
{
	if(!isValid() || treeish.isEmpty())
		return NULL;
	QStringList cmd;
	cmd << "archive" << treeish;
	CoKwargs opts;
	if(!prefix.isEmpty())
		opts.insert("prefix",prefix);
	QByteArray* out = new QByteArray;
	QByteArray* error = new QByteArray;
	bool success = repoGit()->execute(cmd, opts, out, error);
	if(!success)
	{
	}
	return out;
}

QByteArray* CoRepo::archiveTarGz(QString treeish, QString prefix)
{
	//TODO
}

CoRepo* CoRepo::initBare(QString path, bool mkdir, CoKwargs opts)
{
	if(path.isEmpty())
		return NULL;
	QDir gitDir(path);
	if(mkdir && !gitDir.exists())
		gitDir.mkpath(path);
	CoGit gitBin(path);
	QStringList cmd;
	cmd << "init";
	opts.insert("bare","");
	QString out, error;
	bool sucess = gitBin.execute(cmd,opts,&out, &error);
	if(sucess)
		return new CoRepo(path);
	else
	{
		return NULL;
	}
}
