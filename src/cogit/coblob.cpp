/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coblob.cpp
 *	\brief CoBlob类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "coblob.h" 

CoBlob::CoBlob(CoRepo *repo, QString id, int mode, QString name):CoObject(repo,id,CoObject::Blob)
{
	m_mode = mode;
	m_name = name;
	m_size = -1;
	m_data = "";
}

CoBlob::~CoBlob()
{
}

const int CoObject::mode() const
{
	return m_mode;
}

const QString CoObject::name() const
{
	return m_name;
}


const int CoBlob::size() const
{
	if(m_size < 0)
	{
	}
	return m_size;
}

const QString CoBlob::data() const
{
}

const QString CoBlob::baseName() const
{
}

const QString CoBlob::mimeType() const
{
	//TODO
}

const CoBlames CoBlob::blame(const CoRepo* repo,const CoCommit* commit,const QFile &file)
{
}

