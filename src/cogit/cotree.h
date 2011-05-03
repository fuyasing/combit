/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cotree.h
 *	\brief CoTree类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COTREE_H
#define COTREE_H 

#include "cogit_global.h"
#include "coobject.h"

class CoRepo;

//! 本类的功能：Git Tree对象的封装
/*!
 * 本类是Git中的基本对象：Tree对象的封装类，Tree对象是用来组织Blob的存储结构的，每个Tree包括其所包含的Blob以及下一级的Tree。其存储结构对应于文件系统中该仓库的目录结构
 * 继承自：
 * \sa CoObject
 */
class COGIT_EXPORT CoTree : public CoObject
{

	public:

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param id Tree对象的（完整的）SHA串
		 * \param mode Tree对象的mode
		 * \param name Tree对象的name
		 */
		explicit CoTree(CoRepo* repo, QString id, qint32 mode, QString name);

		/*! 析构函数
		*/
		~CoTree();

		/*! 获取该Git对象的mode
		 */
		const qint32 mode() const;

		/*! 获取该Git对象的name,即所指目录的目录名
		 */
		const QString name() const;

		/*! 获取Tree对象所包含Blob和Tree对象的个数
		 */
		int count();

		/*! 判断是否含有name为<name>的Git对象
		 * \param name 需要判断是否存在的Git对象的name属性值
		 * \return 如果存在，返回True,否则返回False
		 */
		bool contains(QString &name);

		/*! 获取指向name为<name>的Git对象的指针
		 * \param name name的值
		 * \return 指向特定Git对象实例的CoObject型的指针
		 */
		const CoObject* item(QString &name);

		/*! 获取该Tree对象包含的所有Git对象，以列表形式返回
		 * \return 返回CoObject型指针的列表
		 */
		QList<CoObject*> items();

		/*! 列出该Tree对象包含的所有项目的name
		 */
		QStringList itemNames();

		/*! 获得id值为id的tree对象的内容,内容组织形式为:
		 * Hash<name,object*>
		 * \param repo 所属的Repo
		 * \param id tree的id值
		 * \attention 此函数为静态函数
		 */
		static QHash<QString,CoObject*> getContentsFromId(CoRepo* repo, QString id);

	private:

		void initContents();

		bool m_isInited;
		QString m_name;
		qint32 m_mode;
		QHash<QString,CoObject*> m_contents;

};

#endif
