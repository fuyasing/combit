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
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "coactor.h" 
#include <QRegExp>

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

CoActor::CoActor(CoActor other)
{
	m_name = other.name();
	m_email = other.email();
}

CoActor::~CoActor()
{
}

QString CoActor::name()
{
	return m_name;
}
QString CoActor::email()
{
	return m_email;
}
QString CoActor::sign()
{
	return QString("%1 <%2>").arg(m_name).arg(m_email);
}

