/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coutils.h
 *	\brief CoUtils命名空间所包含内容的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COTREE_H
#define COTREE_H 

#include "corepo.h"

namespace CoUtils
{
	COGIT_EXPORT QString dashify(QString str);
	COGIT_EXPORT void touch(QString filename);
	COGIT_EXPORT bool isGitDir(QDir dir);
}

#endif
