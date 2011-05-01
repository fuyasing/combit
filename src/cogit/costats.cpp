 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file costats.cpp
 *	\brief CoStats类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "costats.h"

CoStatDict::CoStatDict()
{
	m_statdict.insert("deletions",0);
	m_statdict.insert("insertions",0);
	m_statdict.insert("lines",0);
	m_statdict.insert("files",0);
}

CoStatDict::~CoStatDict()
{

}

int CoStatDict::getDeletions()
{
	return m_statdict.value("deletions");
}

bool CoStatDict::setDeletions(int num)
{
	if(!m_statdict.contains("deletions"))
		return false;
	m_statdict["deletions"] = num;
	return true;
}

int CoStatDict::getInsertions()
{
	return m_statdict.value("insertions");
}

bool CoStatDict::setInsertions(int num)
{
	if(!m_statdict.contains("insertions"))
		return false;
	m_statdict["insertions"] = num;
	return true;
}

int CoStatDict::getLines()
{
	return m_statdict.value("lines");
}

bool CoStatDict::setLines(int num)
{
	if(!m_statdict.contains("lines"))
		return false;
	m_statdict["lines"] = num;
	return true;
}

int CoStatDict::getFiles()
{
	return m_statdict.value("lines");
}

bool CoStatDict::setFiles(int num)
{
	if(!m_statdict.contains("files"))
		return false;
	m_statdict["files"] = num;
	return true;
}

bool CoStatDict::isEmpty()
{
	return m_statdict.isEmpty();
}
CoStats::CoStats(CoRepo* repo, CoStatDict total, QHash<QString, CoStatDict> files)
{
	m_repo = repo;
	m_total = total;
	m_files = files;
}

CoStats::CoStats(CoRepo* repo, QString text)
{
	m_repo = repo;
	QString line;
	QStringList lineSplit;
	foreach(line, text.split('\n'))
	{
		CoStatDict fileDict;
		lineSplit = line.trimmed().split('\t');
		int deletions = lineSplit.at(0).toInt();
		int insertions = lineSplit.at(1).toInt();
		fileDict.setDeletions(deletions);
		fileDict.setInsertions(insertions);
		fileDict.setLines(deletions + insertions);
		fileDict.setFiles(1);
		m_total.setDeletions(m_total.getDeletions() + deletions);	
		m_total.setInsertions(m_total.getInsertions() + insertions);
		m_total.setFiles(m_total.getFiles()+1);
		m_files.insert(lineSplit.at(2),fileDict);
	}
	m_total.setLines(m_total.getDeletions() + m_total.getInsertions());
}

CoStats::~CoStats()
{
}

const CoRepo* CoStats::repo() const
{
	return m_repo;
}

const CoStatDict CoStats::total() const
{
	return m_total;
}

const QHash<QString, CoStatDict> CoStats::files() const
{
	return m_files;
}

const bool CoStats::isClean() const
{
	return m_total.isEmpty();
}
