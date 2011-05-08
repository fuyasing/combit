/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cotag.h
 *	\brief CoTag类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COTAG_H
#define COTAG_H 

#include "cogit_global.h"
#include "coref.h"

#include <QStringList>

class CoRepo;
class CoCommit;

//! 本类的功能：Git tag引用的封装
/*!
 * 本类是Git引用中tag引用的封装
 * 继承自CoRef
 * \sa CoRef
 */
class COGIT_EXPORT CoTag : public CoRef
{
	public:

		/*!
		 */
		explicit CoTag();

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name tag的名字，例如v1.0
		 * \param commit 所指向的commit
		 */
		explicit CoTag(CoRepo* repo, QString name, CoCommit* commit);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name tag的名字，例如v1.0
		 * \param commit 所指向的commit的id
		 */
		explicit CoTag(CoRepo* repo, QString name, QString commit);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name tag的名字，例如v1.0
		 */
		explicit CoTag(CoRepo* repo, QString name);

		/*! 析构函数
		*/
		~CoTag();
		
		/*!
		 */
		bool isValid() const;

		/*! 获取repo中所有的head的列表
		 * \param repo 指定的Repo
		 * \param opts git for-each-ref命令可接受的附加参数
		 */
		static QList<CoTag*> findAllTags(CoRepo* repo, CoKwargs opts=CoKwargs());

};

#endif
