/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cogit_global.h
 *	\brief CoGit库的全局声明声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 *
 *	\version 0.1
 */

#ifndef COGIT_GLOBAL_H
#define COGIT_GLOBAL_H

#include <QtCore/qglobal.h>
#include "version_cogit.h"

#if defined(COGIT_LIBRARY)
#  define COGIT_EXPORT Q_DECL_EXPORT
#else
#  define COGIT_EXPORT Q_DECL_IMPORT
#endif

/*! 仿python语言的参数字典,例如:
 * -tx -Nname --prefix=/usr
 *  存储为CoKwargs为
 *  CoKwargs opts()
 *  opts.insert("t","");
 *  opts.insert("x","")
 *  opts.insert("N","name")
 *  opts.insert("prefix","/usr")
 */
typedef QHash<QString,QString> CoKwargs;


#endif // COGIT_GLOBAL_H
