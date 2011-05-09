/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file codiff.cpp
 *	\brief CoDiff类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "codiff.h"
#include "cocommit.h"
#include "corepo.h"

#include <QList>
#include <QRegExp>

CoDiff::CoDiff()
{
	m_repo = NULL;
	m_aPath = "";
	m_bPath = "";
	m_aCommit = NULL;
	m_bCommit = NULL;
	m_aMode = 0;
	m_bMode = 0;
	m_isNewFile = false;
	m_isDeletedFile = false;
	m_renameFrom = "";
	m_renameTo = "";
	m_diff = "";
}

CoDiff::CoDiff(CoRepo* repo,QString a_path,QString b_path, CoCommit* a_commit, CoCommit* b_commit, qint32 a_mode, qint32 b_mode, bool new_file, bool deleted_file, QString rename_from, QString rename_to,QString diff)
{
	m_repo = repo;
	m_aPath = a_path;
	m_bPath = b_path;
	m_aCommit = a_commit;
	m_bCommit = b_commit;
	m_aMode = a_mode;
	m_bMode = b_mode;
	m_isNewFile = new_file;
	m_isDeletedFile = deleted_file;
	m_renameFrom = rename_from;
	m_renameTo = rename_to;
	m_diff = diff;
}

CoDiff::CoDiff(CoRepo* repo,QString a_path, QString b_path, QString a_commit, QString b_commit, qint32 a_mode, qint32 b_mode, bool new_file, bool deleted_file, QString rename_from, QString rename_to, QString diff)
{
	m_repo = repo;
	m_aPath = a_path;
	m_bPath = b_path;
	m_aCommit = new CoCommit(repo, a_commit);
	m_bCommit = new CoCommit(repo, b_commit);
	m_aMode = a_mode;
	m_bMode = b_mode;
	m_isNewFile = new_file;
	m_isDeletedFile = deleted_file;
	m_renameFrom = rename_from;
	m_renameTo = rename_to;
	m_diff = diff;

}

CoDiff::~CoDiff()
{

}

bool CoDiff::isValid() const
{
	if(m_repo == NULL || m_aCommit == NULL || m_bCommit == NULL)
		return false;
	return true;

}

CoRepo* CoDiff::repo() const
{
	return m_repo;
}

QString CoDiff::aPath() const
{
	return m_aPath;
}

QString CoDiff::bPath() const
{
	return m_bPath;
}

CoCommit* CoDiff::aCommit() const
{
	return m_aCommit;
}

CoCommit* CoDiff::bCommit() const
{
	return m_bCommit;
}

qint32 CoDiff::aMode() const
{
	return m_aMode;
}

qint32 CoDiff::bMode() const
{
	return m_bMode;
}

bool CoDiff::isNewFile() const
{
	return m_isNewFile;
}

bool CoDiff::isDeletedFile() const
{
	return m_isDeletedFile;
}

bool CoDiff::isRenamed() const
{
	return m_isRenamed;
}

QString CoDiff::renameFrom() const
{
	return m_renameFrom;
}

QString CoDiff::renameTo() const
{
	return m_renameTo;
}

QString CoDiff::diffContent() const
{
	return m_diff;
}

QList<CoDiff*> CoDiff::diffsFromString(CoRepo* repo, QString text)
{
	if(repo == NULL || text.isEmpty())
		return QList<CoDiff*>();
	QList<CoDiff*> diffs;
	QRegExp diffHeader(
			"^a/(\\S+)[ ]b/(\\S+)\\n(?:^similarity[ ]index[ ](\\d+)%\\n^rename[ ]from[ ](\\S+)\\n^rename[ ]to[ ](\\S+)(?:\\n|$))?(?:^old[ ]mode[ ](\\d+)\\n^new[ ]mode[ ](\\d+)(?:\\n|$))?(?:^new[ ]file[ ]mode[ ](.+)(?:\\n|$))?(?:^deleted[ ]file[ ]mode[ ](.+)(?:\\n|$))?(?:^index[ ]([0-9A-Fa-f]+)\\.\\.([0-9A-Fa-f]+)[ ]?(.+)?(?:\\n|$))?"
			);
	QString diff;
	QStringList textSplit = ("\n"+text).split("\ndiff --git");
	textSplit.removeFirst();
	foreach(diff, textSplit)
	{
		if(diffHeader.indexIn(diff.trimmed()) != -1)
			diffs.append(
					new CoDiff(repo, diffHeader.cap(1), diffHeader.cap(2),
						diffHeader.cap(10), diffHeader.cap(11), 
						diffHeader.cap(6).toLong() || diffHeader.cap(9).toLong(),
					   	diffHeader.cap(7).toLong() || diffHeader.cap(8).toLong() || diffHeader.cap(12).toLong(), 
						diffHeader.cap(8).toLong(), diffHeader.cap(9).toLong(), 
						diffHeader.cap(4), diffHeader.cap(5), 
						diff.remove(diffHeader.indexIn(diff),diffHeader.matchedLength())
						)
					);
	}
	return diffs;
}
