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
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COREPO_H
#define COREPO_H 

#include "cogit_global.h"
#include "cogit.h"

#include <QDate>

class CoHead;
class CoTag;
class CoCommit;
class QByteArray;

//! 本类的功能：Git Repo的封装类
/*! 本类是Git Repo的封装类，实现Git Repo的相关操作
 */
class COGIT_EXPORT CoRepo : public QObject
{
	
	public:

		/*! 构造函数，根据Repo路径创建CoRepo对象
		 * Repo可以是bare Repo或含工作区的Repo(正常的Git Repo)
		 * 例如:
		 * CoRepo repo("/Users/yandy/workspace/cogit");
		 * CoRepo repo("/Users/yandy/workspace/cogit.git");
		 * \param path Git Repo的路径，如详述部分的示例
		 * \attention path请使用绝对路径
		 */
		explicit CoRepo(QString path = "");

		/*! 析构函数
		 */
		~CoRepo();

		/*!
		 */
		bool isValid() const;

		/*! 判断该对象所指目录是否为一个Git仓库目录
		 */
		bool isRepo() const;

		/*! 判断是否为bare Repo
		 */
		bool isBare() const;

		/*! 获得git Repo的git路径。
		 * 对于bare Repo，git Repo的git路径与工作目录路径想同
		 * 对于一般的Repo，git Repo的git路径为工作目录最顶层中的.git目录的路径
		 * \sa wdPath()
		 */
		QString gitPath() const;

		/*! 获得git Repo的工作目录路径
		 * 对于bare Repo，输出等同gitPath()
		 * 对于一般的Repo，git Repo的工作目录路径为git所管理项目的最顶层目录的路径
		 * \sa gitPath()
		 */
		QString wdPath() const;

		/*! 获得与CoRepo绑定的CoGit对象的指针
		 * CoGit对象是与git程序交互的门户
		 */
		CoGit* repoGit() const;
		
		/*! 获得关于Repo的描述信息
		 */
		QString getDescription() const;

		/*! 设置关于Repo的描述信息
		 * \param descr 描述信息内容
		 */
		void setDescription(QString descr);

		/*! 判断该仓库是否支持基于git://协议的公共,非授权的只读访问,如果支持返回True
		 */
		bool isDaemonExport();

		/*! 设置该仓库是否支持基于git://协议的公共,非授权的只读访问
		 */
		void setDaemonExport(bool is_daemon_export);

		/*! 获得该仓库的备选仓库,如果没有则返回空字符串列表
		 */
		QStringList getAlternates();

		/*! 设置该仓库的备选仓库列表
		 */
		void setAlternates(QStringList paths);

		/*! 判断index的状态，是否有未提交的改动
		 * \return 如果有未提交的改动，返回True
		 */
		bool isDirty();

		/*! 获得当前活动的分支的名字
		 */
		QString activeBranch();
		
		/*! 获取当前Repo所有分支的列表
		 */
		QList<CoHead*> branches();

		/*! 获得当前Repo所有Tag的列表
		 */
		QList<CoTag*> tags();

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

		/*! 获得指定分支中所含commit的个数
		 * \param start 分支名或commit id
		 * \param path 限定条件之一:commit必须含有path,置空表示无此限制
		 */
		int commitCountInBranch(QString start = "master", QString path = "");


		/*! 复制一个当前Repo的bare Repo，到path路径(包含新Repo的目录名)下
		 * \param path 新Repo的完整路径(一般以/<name>.git结尾)
		 * \param opts 传递给git clone命令的额外的参数
		 */
		CoRepo* forkBare(QString path, CoKwargs opts = CoKwargs());

		/*! 对给定的分支或commit或tree打包
		 * \param name 分支名或commit或tree的id
		 * \param prefix tar包中，每个文件名的前缀
		 * \return 打成包的二进制码
		 */
		QByteArray* archiveTar(QString treeish="master",QString prefix="");

		/*! 对给定的分支或commit或tree打包并压缩
		 * \param name 分支名或commit或tree的id
		 * \param prefix 压缩包中，每个文件名的前缀
		 * \return 打成压缩包后的二进制码
		 */
		QByteArray* archiveTarGz(QString treeish="master",QString prefix="");
		
		/*! 将给定的路径初始化为Git bare Repo
		 * \param path 要创建的bare Repo的完整路径(一般以/<name>.git结尾)
		 * \param mkdir 如果为True，则如果path所指向的目录不存在，则创建之
		 * \param opts python风格的额外参数字典
		 * \attention 此函数为静态函数
		 */
		static CoRepo* initBare(QString path, bool mkdir=true, CoKwargs opts = CoKwargs());

	private:

		bool m_isRepo;
		bool m_isBare;
		QString m_gitPath;
		QString m_wdPath;
		CoGit* m_git;
};

#endif
