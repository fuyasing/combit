/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file corepo.h
 *	\brief CoRepo类的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COREPO_H
#define COREPO_H 

#include <QList>

#include "cogit.h"
#include "coobject.h"
#include "coerrors.h"
#include "coref.h"

#include "coblob.h"
#include "cocommit.h"
#include "codiff.h"
#include "coerrors.h"
#include "cohead.h"
#include "costats.h"
#include "cotag.h"
#include "cotree.h"
#include "coutils.h"

class QObject;

/*! Blame结果的封装
 */
typedef QMultiHash<CoCommit*,int> CoBlames;

//! 本类的功能：Git Repo的封装类
/*! 本类是Git Repo的封装类，实现Git Repo的相关操作
 */
class COGIT_EXPORT CoRepo
{

	
	public:
		
		/*! 构造函数，根据Repo路径创建CoRepo对象
		 * Repo可以是bare Repo或含工作区的Repo(正常的Git Repo)
		 * 例如:
		 * CoRepo repo("/Users/yandy/workspace/cogit");
		 * CoRepo repo("/Users/yandy/workspace/cogit.git");
		 * \param path Git Repo的路径，如详述部分的示例
		 */
		explicit CoRepo(QString path="");

		/*! 析构函数
		 */
		~CoRepo();

		/*! 判断是否为bare Repo
		 */
		const bool isBare() const;

		/*! 获得git Repo的git路径。
		 * 对于bare Repo，git Repo的git路径与工作目录路径想同
		 * 对于一般的Repo，git Repo的git路径为工作目录最顶层中的.git目录的路径
		 * \sa wdPath()
		 */
		const QString gitPath() const;

		/*! 获得git Repo的工作目录路径
		 * 对于bare Repo，输出等同gitPath()
		 * 对于一般的Repo，git Repo的工作目录路径为git所管理项目的最顶层目录的路径
		 * \sa gitPath()
		 */
		const QString wdPath() const;

		/*! 获得与CoRepo绑定的CoGit对象的指针
		 * CoGit对象是与git程序交互的门户
		 */
		const CoGit* repoGit() const;
		
		/*! 获得关于Repo的描述信息
		 */
		QString getDescription();

		/*! 设置关于Repo的描述信息
		 * \return 如果设置成功，返回True
		 */
		bool setDescription(QString descr);

		/*! 判断index的状态，是否有未提交的改动
		 * \return 如果有未提交的改动，返回True
		 */
		bool isDirty();

		/*! 获得当前活动的分支的名字
		 */
		QString activeBranch();
		
		/*! 获取当前Repo所有分支的列表
		 */
		QList<CoHead *> branches();

		/*! 获得指定分支里符合一定限制条件的所有commit的列表
		 * \param start 分支名或commit id
		 * \param path 限定条件之一：commit必须含有path，置空表示无此限制
		 * \param maxCount 限制条件之一：返回commit列表所含commit的最大数量
		 * \param skip 限制条件之一：需要跳过的commits数目
		 */
		QList<CoCommit *> commitsInBranch(QString start="master",QString path="",int maxCount=10, int skip=0);

		/*! 获得commit历史中从from到to的commit的列表
		 * \param from 较新的commit 
		 * \param to 较旧的commit
		 */
		QList<CoCommit *> commitsBetween(QString from, QString to);

		/*! 获得从start开始向前(向更旧的commit方向)，以及在since日期之后的提交，如果有限制条件，还要满足限制条件
		 * \param start 分支名或commit id
		 * \param path 限制条件：commit必须包含path，置空表示无此限制
		 * \param since 最旧的commit不能早于的日期
		 */
		QList<CoCommit *> commitsSince(QString start="master",QString path="",QDate since=QDate(1970,1,1));

		/*! 获得在otherRepo的otherRef中存在而在本仓库的ref中不存在的commits的列表
		 * \param otherRepo 别的Repo
		 * \param ref 本Repo的分支
		 * \param otherRef 别的Repo的分支
		 */
		QList<CoCommit *> commitDeltas(CoRepo * otherRepo, QString ref="master", QString otherRef="master");

		/*! 复制一个当前Repo的bare Repo，到path路径(包含新Repo的目录名)下
		 * \param path 新Repo的完整路径(一般以/<name>.git结尾)
		 * \param kwargs 传递给git clone命令的额外的参数
		 */
		CoRepo* forkBare(QString path, CoKwargs kwargs);

		/*! 对给定的分支或commit或tree打包
		 * \param name 分支名或commit或tree的id
		 * \param prefix tar包中，每个文件名的前缀
		 * \return 打成包的二进制码
		 */
		QByteArray* archiveTar(QString name="master",QString prefix="");

		/*! 对给定的分支或commit或tree打包并压缩
		 * \param name 分支名或commit或tree的id
		 * \param prefix 压缩包中，每个文件名的前缀
		 * \return 打成压缩包后的二进制码
		 */
		QByteArray* archiveTarGz(QString name="master",QString prefix="");
		
		/*! 将给定的路径初始化为Git bare Repo
		 * \param path 要创建的bare Repo的完整路径(一般以/<name>.git结尾)
		 * \param mkdir 如果为True，则如果path所指向的目录不存在，则创建之
		 * \param kwargs python风格的额外参数字典
		 * \attention 此函数为静态函数
		 */
		static CoRepo* initBare(QString path, bool mkdir=true, CoKwargs kwargs);

	private:

		bool m_isBare;
		QString m_gitPath;
		QString m_wdPath;
		CoGit* m_git;
};

#endif
