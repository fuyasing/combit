/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cocommit.h
 *	\brief CoCommit类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COCOMMIT_H
#define COCOMMIT_H 

#include "cogit_global.h"
#include "coobject.h"
#include "coactor.h"

#include <QList>
#include <QStringList>
#include <QDateTime>

class CoRepo;
class CoStats;
class CoDiff;
class CoRef;
class CoTree;

//! 本类的功能：Git commit对象的封装
/*!
 * 本类是Git中的基本对象：commit对象的封装类,commit对象存储版本信息，指向特定的tree对象
 * 继承自:
 * \sa CoObject
 */
class COGIT_EXPORT CoCommit : public CoObject
{
		
	public:
	
		/*! 函数列表为空构造函数
		 */
		explicit CoCommit();

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param id commit对象的（完整的）SHA串
		 * \param tree Commit指向的tree的id
		 * \param author commit的创建者
		 * \param authored_date commit创建日期
		 * \param committer commit的提交者
		 * \param committed_date commit的提交日期
		 * \param message commit提交信息
		 * \param parents 父commit id的列表
		 */
		explicit CoCommit
			(
			 CoRepo* repo, QString id, CoTree* tree, CoActor author,
			 QDateTime authored_date, CoActor committer,QDateTime committed_date,
			 QString message,QStringList parents
			 );

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param id commit对象的SHA串
		 * \attention 此构造函数效率较前一个低
		 */
		explicit CoCommit(CoRepo* repo, QString id);

		/* 析构函数
		 */
		~CoCommit();

		/*! 判断所建对象是否有效
		 *  \return 对象有效返回True
		 */
		bool isValid() const;

		/*! 获取父commit对象的列表
		 * \attention 第一次调用后会缓存父commit对象列表
		 */
		QList<CoCommit*> parents();

		/*! 获取commit指向的tree
		 */
		CoTree* tree() const;

		/*! 获取commit的创建者
		 */
		CoActor author() const;

		/*! 获取commit的创建日期
		 */
		QDateTime authoredDate() const;

		/*! 获取commit的提交者
		 */
		CoActor committer() const;

		/*! 获取commit的提交日期
		 */
		QDateTime committedDate() const;

		/*! 获取commit id的7位简略值
		 */
		QString idAbbrev() const;

		/*! 获取commit提交信息的第一行
		 */
		QString summary() const;

		/*! 获取commit完整的提交信息
		 */
		QString message() const;

		/*! 生成当前commit和其第一父commit之间的CoDiff对象(差异对象)列表，如果没有父commit，则生成包含所有内容的CoDiff对象列表
		 */
		QList<CoDiff*> diffs();

		/*! 根据当前commit和其第一父commit之间的差异生成CoStats对象，如果没有父commit则根据包含所有内容生成CoStats对象
		 */
		CoStats* stats();
		
		/*! 计算从ref开始，向前可达到的所有包含path的commit的个数
		 * \param repo 所属Repo的指针
		 * \param ref 计算起始的CoRef的name或其所指commit的SHA1值
		 * \param path 包含的path，默认为空串，表示无path限制
		 * \sa CoRef
		 * \attention 这是个静态函数
		 */
		static int commitsCount(CoRepo* repo, QString ref, QString path="");

		/*! 计算从ref开始，向前可达到的所有包含path的commit的个数
		 * \param repo 所属Repo的指针
		 * \param ref 计算起始的CoRef对象的指针
		 * \param path 包含的path，默认为空串，表示无path限制
		 * \attention 这是个静态函数
		 */
		static int commitsCount(CoRepo* repo, CoRef* ref, QString path="");

		/*! 计算从ref开始，向前可达到的所有包含path的commit的个数
		 * \param repo 所属Repo的指针
		 * \param ref 计算起始的CoRef所指commit的CoCommit对象指针
		 * \param path 包含的path，默认为空串，表示无path限制
		 * \sa CoRef
		 * \attention 这是个静态函数
		 */
		static int commitsCount(CoRepo* repo, CoCommit* ref, QString path="");

		/*! 通过"git rev-list"命令生成符合给定条件的所有Commit对象的列表
		 * \param repo 所属Repo的指针
		 * \param ref 条件之一；查找commit的范围,可以是commit的id,或者ref的名字,也可以是符合git格式的范围,例如: kdja2874..kddg2114
		 * \param opts 条件之一；rev-list可选的命令参数列表
		 * \param path 条件之一；commit需要包含path，默认为空，表示无此限制
		 * \sa CoRef
		 * \attention 这是个静态函数
		 */
		static QList<CoCommit*> findAllCommits(CoRepo* repo, QString ref, CoKwargs opts = CoKwargs(), QString path="");

		/*! 根据"git rev-list"命令的输出生成commit对象的列表
		 * \param repo 所属Repo的指针
		 * \param text git rev-list命令的输出
		 * \attention 这是个静态函数
		 */
		static QList<CoCommit*> listCommitsFromString(CoRepo* repo, QString text);

		/*! 生成tree对象之间或tree对象和index(工作区)之间的CoDiff对象(CoGit库中描述差异的对象)列表
		 * \param repo 所属Repo的指针
		 * \param a 一个tree或者commit的id值
		 * \param b 如果比较两个tree对象之间的差异，为另一个tree或者commit的id值；如果比较tree和index之间的差异，则留空
		 * \param paths 比较限定在paths内，留空表示无此限制
		 * \sa CoDiff 
		 * \attention 这是个静态函数
		 */
		static QList<CoDiff*> makeDiff(CoRepo* repo, QString a, QString b="",QStringList paths = QStringList());

		/*! 生成tree对象之间或tree对象和index(工作区)之间的CoDiff对象(CoGit库中描述差异的对象)列表
		 * \param repo 所属Repo的指针
		 * \param a CoCommit对象的指针
		 * \param b 如果比较两个tree对象之间的差异，为另一个CoCommit对象的指针；如果比较tree和index之间的差异，则赋NULL
		 * \param paths 比较限定在paths内，留空表示无此限制
		 * \sa CoDiff 
		 * \attention 这是个静态函数
		 */
		static QList<CoDiff*> makeDiff(CoRepo* repo, CoCommit* a, CoCommit* b=NULL, QStringList paths = QStringList());

		/*! 生成tree对象之间或tree对象和index(工作区)之间的CoDiff对象(CoGit库中描述差异的对象)列表
		 * \param repo 所属Repo的指针
		 * \param a CoTree对象的指针
		 * \param b 如果比较两个tree对象之间的差异，为另一个CoTree对象的指针；如果比较tree和index之间的差异，则赋NULL
		 * \param paths 比较限定在paths内，留空表示无此限制
		 * \sa CoDiff 
		 * \attention 这是个静态函数
		 */
		static QList<CoDiff*> makeDiff(CoRepo* repo, CoTree* a, CoTree* b=NULL, QStringList paths = QStringList());

	private:
	
		QStringList m_parentsIds;
		CoTree* m_tree;
		CoActor m_author;
		QDateTime m_authoredDate;
		CoActor m_committer;
		QDateTime m_committedDate;
		QString m_message;
		QList<CoCommit*> m_parentsList;
};


#endif
		
