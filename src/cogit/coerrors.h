/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coerrors.h
 *	\brief 异常处理模块的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 *
 */

#ifndef COERRORS_H
#define COERRORS_H 

namespace CoErrors{

	enum ErrorType{
		InvalidGitRepositoryError,
		NoSuchPathError,
		GitCommandError
	};
}

#endif
