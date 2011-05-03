/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file codiff.h
 *	\brief CoDiff类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef CODIFF_H
#define CODIFF_H 

#include "cogit_global.h"

#include <QList>

class CoCommit;
class CoRepo;

//! 本类的功能：Git 两个commit对象差异信息的封装
/*! 一个CoDiff对象存储一个文件在两个commit中的差异信息
 * 如果两个commit分别为a和b，则这些信息包括:
 * a中的mode和b中的mode
 * a中的路径和b中的路径（包含文件名）
 * 是否为新建文件或删除文件
 * 是否重命名了，如果是，原名是什么，新名是什么
 * 差异的内容
 */
class COGIT_EXPORT CoDiff
{
	
	public:

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param a_path 在a中的路径
		 * \param b_path 在b中的路径
		 * \param a_commit a commit的指针
		 * \param b_commit b commit的指针
		 * \param a_mode 在a中的mode
		 * \param b_mode 在b中的mode
		 * \param new_file 如果是新建文件，值为True
		 * \param deleted_file 如果是删除文件，值为True
		 * \param rename_from 如果重命名了，原文件名
		 * \param rename_to 如果重命名了，现文件名
		 * \param diff 差异内容
		 */
		explicit CoDiff(
				CoRepo* repo,QString a_path, QString b_path, 
				CoCommit* a_commit, CoCommit* b_commit,
				qint32 a_mode, qint32 b_mode, bool new_file, bool deleted_file, 
				QString rename_from, QString rename_to, QString diff
			);
	
		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param a_path 在a中的路径
		 * \param b_path 在b中的路径
		 * \param a_commit a commit的id
		 * \param b_commit b commit的id
		 * \param a_mode 在a中的mode
		 * \param b_mode 在b中的mode
		 * \param new_file 如果是新建文件，值为True
		 * \param deleted_file 如果是删除文件，值为True
		 * \param rename_from 如果重命名了，原文件名
		 * \param rename_to 如果重命名了，现文件名
		 * \param diff 差异内容
		 */
		explicit CoDiff(
				CoRepo* repo,QString a_path, QString b_path, 
				QString a_commit, QString b_commit,
				qint32 a_mode, qint32 b_mode, bool new_file, bool deleted_file, 
				QString rename_from, QString rename_to, QString diff
			);

		/*! 析构函数
		 */
		~CoDiff();

		/*! 获取所属Repo的指针
		 */
		const CoRepo* repo() const;

		/*! 获取在a中的路径（包含文件名）
		 */
		const QString aPath() const;

		/*! 获取在b中的路径（包含文件名）
		 */
		const QString bPath() const;

		/*! 获取a commit的指针
		 */
		const CoCommit* aCommit() const;

		/*! 获取b commit的指针
		 */
		const CoCommit* bCommit() const;

		/*! 获取在a中的mode
		 */
		const qint32 aMode() const;

		/*! 获取在b中的mode
		 */
		const qint32 bMode() const;

		/*! 是否是新文件
		 * \return 是新文件返回True
		 */
		const bool isNewFile() const;

		/*! 是否是被删除文件
		 * \return 是被删除文件返回True
		 */
		const bool isDeletedFile() const;

		/*! 是否重命名了
		 * \return 重命名了返回True
		 */
		const bool isRenamed() const;

		/*! 获得重命名前的文件名
		 */
		const QString renameFrom() const;

		/*! 获得重命名后的文件名
		 */
		const QString renameTo() const;

		/*! 获取差异内容
		 */
		const QString diffContent() const;

		/*! 根据git diff命令的输出，生成CoDiff列表
		 * \param repo 所属Repo的指针
		 * \param text git diff命令的输出
		 */
		static QList<CoDiff*> diffsFromString(CoRepo* repo, QString text);
	
	private:
		CoRepo* m_repo;
		QString m_aPath;
		QString m_bPath;
		CoCommit* m_aCommit;
		CoCommit* m_bCommit;
		qint32 m_aMode;
		qint32 m_bMode;
		bool m_isNewFile;
		bool m_isDeletedFile;
		QString m_renameFrom;
		QString m_renameTo;
		bool m_isRenamed;
		QString m_diff;
};

#endif 
