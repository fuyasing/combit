/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coutils.cpp
 *	\brief CoUtils命名空间所包含内容的实现部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#include "coutils.h" 
#include <QFileInfo>
#include <QFile>
#include <QDir>

bool CoUtils::touch(QString filename)
{
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly))
		return false;
	file.close();
	return true;
}

bool CoUtils::isGitDir(QString path)
{
	QDir gitDir(path);
	if(gitDir.exists())
	{
		QDir objectsDir(path);
		QDir refsDir(path);
		if(objectsDir.cd("objects") && refsDir.cd("refs") && gitDir.exists("HEAD"))
		{
			QFileInfo headref(gitDir,"HEAD");
			bool ret = headref.isFile() || (headref.isSymLink() && headref.symLinkTarget().startsWith("refs"));
			return ret;
		}
	}
	return false;
}
