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
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "codiff.h"
#include "cocommit.h"
#include "corepo.h"

#include <QList>
#include <QRegExp>

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

const CoRepo* CoDiff::repo() const
{
	return m_repo;
}

const QString CoDiff::aPath() const
{
	return m_aPath;
}

const QString CoDiff::bPath() const
{
	return m_bPath;
}

const CoCommit* CoDiff::aCommit() const
{
	return m_aCommit;
}

const CoCommit* CoDiff::bCommit() const
{
	return m_bCommit;
}

const qint32 CoDiff::aMode() const
{
	return m_aMode;
}

const qint32 CoDiff::bMode() const
{
	return m_bMode;
}

const bool CoDiff::isNewFile() const
{
	return m_isNewFile;
}

const bool CoDiff::isDeletedFile() const
{
	return m_isDeletedFile;
}

const bool CoDiff::isRenamed() const
{
	return m_isRenamed;
}

const QString CoDiff::renameFrom() const
{
	return m_renameFrom;
}

const QString CoDiff::renameTo() const
{
	return m_renameTo;
}

const QString CoDiff::diffContent() const
{
	return m_diff;
}

QList<CoDiff*> CoDiff::diffsFromString(CoRepo* repo, QString text)
{
	QList<CoDiff*> diffs;
	QRegExp diffHeader(
			"#^diff[ ]--git[ ]a/(\\S+)[ ]b/(\\S+)\\n(?:^similarity[ ]index[ ](\\d+)%\\n^rename[ ]from[ ](\\S+)\\n^rename[ ]to[ ](\\S+)(?:\\n|$))?(?:^old[ ]mode[ ](\\d+)\\n^new[ ]mode[ ](\\d+)(?:\\n|$))?(?:^new[ ]file[ ]mode[ ](.+)(?:\\n|$))?(?:^deleted[ ]file[ ]mode[ ](.+)(?:\\n|$))?(?:^index[ ]([0-9A-Fa-f]+)\\.\\.([0-9A-Fa-f]+)[ ]?(.+)?(?:\\n|$))?"
			);
	QString diff;
	QStringList textSplit = ("\n"+text).split("\ndiff --git");
	textSplit.removeFirst();
	foreach(diff, textSplit)
	{
		if(diffHeader.indexIn(diff) != -1)
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
