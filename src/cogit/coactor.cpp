/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coactor.cpp
 *	\brief CoActor类的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "coactor.h"

#include <QRegExp>

CoActor::CoActor()
{
	m_name = "";
	m_email = "";
}

CoActor::CoActor(QString name , QString email)
{
	m_name = name;
	m_email = email;
}

CoActor::CoActor(QString sign)
{

	/*
	   根据格式化的字符串创建CoActor对象
	   字符串格式：Michael Ding <yandy@gmail.com>
	   */
	QRegExp rx("(.*)(?:\\s*)<(.+?)>");
	int pos = rx.indexIn(sign);
	if(pos >-1)
	{
		m_name = rx.cap(1);
		m_email = rx.cap(2);
	}
	else
	{
		m_name = sign;
		m_email = "";
	}
}

CoActor::~CoActor()
{
}

const QString CoActor::name() const
{
	return m_name;
}
const QString CoActor::email() const
{
	return m_email;
}
const QString CoActor::sign() const
{
	return QString("%1 <%2>").arg(m_name).arg(m_email);
}

const bool CoActor::isValid() const
{
	return !m_name.isEmpty();
}

