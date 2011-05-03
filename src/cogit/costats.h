/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file costats.h
 *	\brief CoStats类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COSTATS_H
#define COSTATS_H 

#include "cogit_global.h"

class CoRepo;

//a! 本类的功能：存储Stat信息的基础单元
/*! 字典(或称Hash)数据结构，包含4个键值对：
 * deletions = 删除的行数
 * insertions = 插入的行数
 * lines = 总共改变的行数，lines=deletions+insertions
 * files = 有改变的文件数
 */
class COGIT_EXPORT CoStatDict
{
	public:
		
		/*! 构造函数，初始化数据，生成4个键值对，并使得deletions=0,insertions=0,lines=0,files=0
		 */
		explicit CoStatDict();

		/*! 析构函数
		 */
		~CoStatDict();

		/*! 获得deletions的值
		 */
		int getDeletions();

		/*! 设置deletions的值
		 * \param num 要设置的数值
		 * \return 如果设置成功，返回True；否则，返回False
		 */
		bool setDeletions(int num);

		/*! 获得insertions的值
		 */
		int getInsertions();

		/*! 设置insertions的值
		 * \param num 要设置的数值
		 * \return 如果设置成功，返回True；否则，返回False
		 */
		bool setInsertions(int num);

		/*! 获得lines的值
		 */
		int getLines();

		/*! 设置lines的值
		 * \param num 要设置的数值
		 * \return 如果设置成功，返回True；否则，返回False
		 */
		bool setLines(int num);

		/*! 获得files的值
		 */
		int getFiles();

		/*! 设置files的值
		 * \param num 要设置的数值
		 * \return 如果设置成功，返回True；否则，返回False
		 */
		bool setFiles(int num);

		/*! 判断Statas信息是否为空:即有没有差异
		 * \return 如果为空返回True
		 */
		bool isEmpty();


	private:

		QHash<QString,int> m_statdict;
};

//! 本类的功能：Git stat信息的封装
/*! git stat信息是差异信息的总结，commit描述，merge结果，检测工作空间是否clean等方面都有使用。一般根据diff操作输出生。
 */
class COGIT_EXPORT CoStats
{
	
	public: 

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param total 关于整个Repo的CoStatDict
		 * \param files 对每个有改动的文件，关联一个针对其的CoStatDict
		 */
		explicit CoStats(CoRepo* repo, CoStatDict total, QHash<QString,CoStatDict> files);

		/*! 构造函数
		 * \param repo 所属Repo的指针
		 * \param text diff操作的输出值
		 */
		explicit CoStats(CoRepo* repo, QString text);

		/*! 析构函数
		 */
		~CoStats();

		/*! 获取所属Repo
		 */
		CoRepo* repo() const;

		/*! 获取关于整个Repo的CoStatDict
		 */
		CoStatDict total() const;

		/*! 获取一个Hash表，键为有改动的文件名(包括路径)，值为此文件对应的CoStatDict
		 */
		QHash<QString,CoStatDict> files() const;

		/*! 是否内容为空(即没有差别)
		 * \return 如果为空，返回True
		 */
		const bool isClean();
		
	private:
		
		CoRepo* m_repo;
		CoStatDict m_total;
		QHash<QString,CoStatDict> m_files;
		
};

#endif
