/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cotree.cpp
 *	\brief CoTree类的实现部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#include "cotree.h" 

CoTree::CoTree(CoRepo *repo, QString id, int mode, QString name):CoObject(repo,id,CoObject::Tree)
{
	m_name = name;
	m_mode = mode;
	//TODO
	//初始化m_contents
}

CoTree::~CoTree()
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


const QString CoTree::baseName() const
{
}
int CoTree::count() const
{
}
