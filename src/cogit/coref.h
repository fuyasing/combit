/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coref.h
 *	\brief CoRef类的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COREF_H
#define COREF_H

#include "cogit_global.h"

#include <QString>

//! 本类的功能：Git引用的抽象基类
/*!
 * 本类是Git引用的抽象基类，提供Git引用对象的基本属性。Git的引用指向特定的commit，方便定位到特定的commit
 * 继承自CoObject的类有:
 * \sa
 * CoHead,CoTag
 */
class COGIT_EXPORT CoRef
{

	public:

		/*!关于Git引用类型的枚举,方便确定一个指向子类实例的CoRef指针指向的到底是哪种子类实例*/
		enum CoRefType
		{
			Head,	/*!<Head类型*/
			Tag	/*!<Tag类型*/
		};

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name Ref的名字，例如master
		 * \param commit 所指向的commit
		 * \param type Git对象的子类类别
		 */
		explicit CoRef(CoRepo* repo, QString name, CoCommit* commit, CoRefType type);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name Ref的名字，例如master
		 * \param commit 所指向的commit的id
   		 * \param type Git对象的子类类别
		 */
		explicit CoRef(CoRepo* repo, QString name, QString commit, CoRefType type);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param name Ref的名字，例如master
   		 * \param type Git对象的子类类别
		 */
		explicit CoRef(CoRepo* repo, QString name, CoRefType type);

		/*!析构函数
		 */
		~CoRef();

		/*!获取指向该Git引用所属Repo的指针
		 */
		const CoRepo* repo() const;
		/*! 获取Git引用的名字
		*/
		const QString name() const;

		/*! 获取Git引用指向的commit
		*/
		const CoCommit* commit() const;

		/*!获取该Git引用的类型*/
		const CoRefType type() const;
	
	protect:
		/*! 设置Git引用指向的commit
		 * \param commit 要指向的commit
		 * \return 如果设置成功,返回True
		 */
		bool setCommit(CoCommit* commit);

		/*! 设置Git引用指向的commit
		 * \param commit 要指向的commit的id
		 * \return 如果设置成功,返回True
		 */
		bool setCommit(QString commit);


	private:

		CoRepo* m_repo;
		QString m_name;
		CoCommit* m_commit;
		CoRefType m_type;

};

#endif
