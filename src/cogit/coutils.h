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

#include "cogit_global.h"

namespace CoUtils
{
	/*! 确保文件名为filename(包括路径名)的文件要存在
	 * \return 如果文件存在,或者本来不存在,但是创建成功,则返回True,否则返回False
	 */
	COGIT_EXPORT bool touch(QString filename);

	/*! 判断一个目录是否为git目录,如果是一般仓库,git目录为仓库顶层目录下的.git目录,如果是bare仓库,git目录则为仓库顶层目录
	 * \param path 要判断的目录路径
	 * \return 如果是git目录,返回True
	 * \attention path为绝对路径
	 */
	COGIT_EXPORT bool isGitDir(QString path);
}

#endif
