/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cohead.h
 *	\brief CoHead类的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COHEAD_H
#define COHEAD_H 

#include "cogit_global.h"
#include "coref.h"

#include <QStringList>

class CoCommit;
class CoRepo;

//! 本类的功能：Git Head引用的封装
/*!
 * 本类是Git引用中head引用的封装，一般来说Git的分支就是通过head引用实现的
 * 继承自CoRef
 * \sa CoRef
 */
class COGIT_EXPORT CoHead : public CoRef
{
	
	public:

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name head的名字，例如master
		 * \param commit 所指向的commit
		 */
		explicit CoHead(CoRepo* repo, QString name, CoCommit* commit);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name head的名字，例如master
		 * \param commit 所指向的commit的id
		 */
		explicit CoHead(CoRepo* repo, QString name, QString commit);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name head的名字，例如master
		 */
		explicit CoHead(CoRepo* repo, QString name);

		/*! 析构函数
		 */
		~CoHead();
	
		/*! 更新Git引用指向的commit
		 */
		const CoCommit* update();
	
		/*! 获取repo中所有的head的列表
		 * \param repo 指定的Repo
		 * \param opts git for-each-ref命令可接受的附加参数
		 */
		static QList<CoHead*> findAllHeads(CoRepo* repo, CoKwargs opts = CoKwargs());

	private:
		QString m_name;
		CoCommit* m_commit;

};

#endif
