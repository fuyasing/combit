/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coobject.h
 *	\brief CoObject类的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COOBJECT_H
#define COOBJECT_H 

#include "cogit_global.h"

#include <QString>

//!	本类的功能：Git对象的抽象基类
/*!
 *	本类是Git对象的抽象基类，提供Git数据对象的基本属性。
 *	继承自CoObject的类有：
 *	\sa 
 *	CoBlob,CoTree
 */
class COGIT_EXPORT CoObject
{

	public:

		/*! 关于Git对象类型的枚举，方便确定一个指向子类实例的CoObject指针指向的到底是哪种子类实例
		 */
		enum CoObjType
		{
			Blob,	/*!< Blob类型 */
			Tree,	/*!< Tree类型 */
			Commit	/*!< Commit类型 */
		};
		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param id Git对象的（完整的）SHA串
		 * \param type Git对象的子类类别
		 */
		explicit CoObject(CoRepo* repo,QString id,CoObjType type);

		/*! 析构函数
		 */
		~CoObject();

		/*! 获取指向该Git对象所属Repo的指针
		 */
		const CoRepo* repo() const;

		/*! 获取该Git对象的SHA串
		 */
		const QString id() const;

		/*! 获取该Git对象的类型
		 */
		const CoObjType type() const;

		/*! 根据特定格式字符串构造Git对象(blob,tree,...)
		 * 字符串特定格式同"git ls-tree"命令输出结果中的一项的格式：
		 * <mode>\t<type>\t<id>\t<name>\n
		 * 例如：
		 * 100644 blob 7cd253d387d63aa26338683ef26fe4b6dcac8bd2	src/main.cpp
		 * \param repo 所属repo的指针
		 * \param text 特定格式的字符串
		 * \return 指向特定Git对象的CoObject型指针
		 */
		static CoObject* objectFromString(CoRepo* repo,QString text);

	private:

		CoRepo* m_repo;
		QString m_id;
		
		CoObjType m_type;

};

#endif
