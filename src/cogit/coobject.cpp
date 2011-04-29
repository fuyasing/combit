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
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "coobject.h"

CoObject::CoObject(CoRepo *repo, QString id, CoObject::CoObjType type)
{
	m_repo = repo;
	m_id = id;
	m_type = type;
}
CoObject::~CoObject()
{
}

const CoRepo* CoObject::repo() const
{
	return m_repo;
}

const QString CoObject::id() const
{
	return m_id;
}

const CoObject::CoObjType type() const
{
	return m_type;
}

CoObject* CoObject::getObjectFromString(CoRepo *repo, QString text)
{
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
