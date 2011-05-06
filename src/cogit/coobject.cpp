 /*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coobject.cpp
 *	\brief CoObject类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "coobject.h"
#include "corepo.h"
#include "cotree.h"
#include "coblob.h"

#include <QRegExp>
#include <QStringList>

CoObject::CoObject()
{
	m_repo = NULL;
	m_id = "";
	m_type = CoObject::Invalid;
}

CoObject::CoObject(CoRepo *repo, QString id, CoObject::CoObjType type)
{
	m_repo = repo;
	m_id = id;
	m_type = type;
}
CoObject::~CoObject()
{
}

const bool CoObject::isValid() const
{
	return m_repo != NULL && !m_id.isEmpty() && m_type != CoObject::Invalid;
}

CoRepo* CoObject::repo() const
{
	return m_repo;
}

const QString CoObject::id() const
{
	return m_id;
}

const CoObject::CoObjType CoObject::type() const
{
	return m_type;
}

CoObject* CoObject::objectFromString(CoRepo *repo, QString text)
{
	if(repo == NULL || text.isEmpty())
		return NULL;
	QStringList textSplit = text.split(QRegExp("\\s+"));
	CoObject *obj;
	if(textSplit.at(1)=="blob")
	{
		obj = new CoBlob(repo, textSplit.at(2), textSplit.at(0).toInt(), textSplit.at(3));
	}
	else if(textSplit.at(1)=="tree")
	{
		obj = new CoTree(repo, textSplit.at(2), textSplit.at(0).toInt(), textSplit.at(3));
	}
	return obj;
}
