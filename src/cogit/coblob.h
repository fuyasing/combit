/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coblob.h
 *	\brief CoBlob类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COBLOB_H
#define COBLOB_H 

#include "cogit_global.h"
#include "coobject.h"

#include <QStringList>

class CoRepo;
class CoCommit;

//! 本类的功能：Git Blob对象的封装
/*!
 * 本类是Git中的基本对象：Blob对象的封装类,Blob对象存储的是文件的特定版本的内容
 * 继承自:
 * \sa CoObject
 */
class COGIT_EXPORT CoBlob : public CoObject
{

	public:

		/*!参数列表为空的构造函数
		 */
		explicit CoBlob();

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param id Blob对象的（完整的）SHA串
		 * \param mode Blob对象的mode 
		 * \param name Blob对象的name 
		 */
		explicit CoBlob(CoRepo* repo, QString id, qint32 mode, QString name);

		/*! 析构函数
		*/
		~CoBlob();

		/*!
		 */
		const bool isValid() const;

		/*! 获取该Git对象的mode
		 */
		const qint32 mode() const;

		/*! 获取该Git对象的name,即所指文件的文件名
		 */
		const QString name() const;

		/*! 获取Blob对象的大小（单位byte）
		 * \note 第一次调用后，该值将被缓存
		 */
		const qint32 size();

		/*! 获取Blob对象的内容，如文本内容
		 *  内容存储在QString型的字符串中
		 * \note 第一次调用后，该值将被缓存
		 */
		const QString data();

		/*! 获取Blob对象的mime type 信息
		 * \note 第一次调用后，该值将被缓存
		 * \attention 该函数在第一版中未实现，返回值一直是"text/plain"
		 */
		const QString mimeType() const;

		/*! 获取Blob对象对应文件的文件名(不含扩展名)
		 */
		const QString baseName() const;

		/*! 获得id(SHA串)为id的blob对象的内容
		 * \param repo 所属仓库
		 * \param id blob的id值
		 * \attention 此函数为静态函数
		 */
		static const QString getDataFromId(CoRepo* repo, QString id);

		/*! 获取给定文件相对于特定commit的Blame信息
		 * \return 存储在CoBlames类型中的blame信息
		 */
		static const CoBlames blame(CoRepo* repo,const CoCommit* commit,const QString file);


	private:

		qint32 m_mode;
		QString m_name;
		qint32 m_size;
		QString m_data;
		QString m_mimeType;
		QString m_baseName;
};


#endif
