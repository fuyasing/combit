/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file cogit.h
 *	\brief CoGit类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COGIT_H
#define COGIT_H

#include "cogit_global.h"
#include "coerrors.h"

#include <QStringList>
#include <QObject>

class QByteArray;

//! 本类的功能：实现与Git程序的交互
/*! 本类是对Git程序调用的封装，处理调用，输入输出
 */
class COGIT_EXPORT CoGit : public QObject
{
	Q_OBJECT

	public:

		/*! 构造函数
		 * \param gitWdDir git的顶级工作目录路径
		 */
		explicit CoGit(QString gitWdDir="", QString gitBinary = "git");

		/*! 析构函数
		 */
		~CoGit();

		/*! 判断CoGit对象是否有意义
		 */
		const bool isValid() const {return !m_gitWdDir.isEmpty() && !m_gitBin.isEmpty();}

		/*! 获取git的顶级工作目录路径
		*/
		const QString gitWdDir() const {return m_gitWdDir;}

		/*! 在子进程中调用Git程序
		 * \param cmd 不包括"git"在内的命令字符串列表
		 * \param opts 额外的参数字典
		 * \param stdOut 存储标准输出结果
		 * \param stdError 存储标准错误输出结果
		 * \param inStream 向子进程发送输入的文件的文件名，留空表示不向子进程发送输入
		 * \param withExceptionsEmit 如果为真，将发送执行异常相关的信号
		 * \return 如果Git执行正常结束，返回True，否则返回False
		 */
		bool execute(QStringList cmd, CoKwargs opts, QString* stdOut, QString* stdError, QString inStream = "", bool withExceptionsEmit = false);

		/*! 在子进程中调用Git程序
		 * \param cmd 不包括"git"在内的命令字符串列表
		 * \param opts 额外的参数字典
		 * \param stdOut 存储标准输出结果
		 * \param stdError 存储标准错误输出结果
		 * \param inStream 向子进程发送输入的文件的文件名，留空表示不向子进程发送输入
		 * \param withExceptionsEmit 如果为真，将发送执行异常相关的信号
		 * \return 如果Git执行正常结束，返回True，否则返回False
		 */
		bool execute(QStringList cmd, CoKwargs opts, QByteArray* stdOut, QByteArray* stdError, QString inStream = "", bool withExceptionsEmit = false);

		/*! 向pid号为pid的子进程发送终止信号
		 * \param pid 子进程的pid号
		 */
		void cancel();

	signals:

		void cancelProcess();
		void exceptionOccur(CoErrors::ErrorType error);


	private slots:

		void onExcuteExceptionOccur(CoErrors::ErrorType error);


	private:

		QStringList transformKwargs(CoKwargs opts);

		QString m_gitWdDir;
		QString m_gitBin;
		bool m_hasProcess;


};

#endif // COGIT_H
