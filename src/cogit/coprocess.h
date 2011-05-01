/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coprocess.h
 *	\brief CoProcess类的声明部分
 *
 *	\author 丁彦 yandy.ding@gmail.com
 *	\date 2011/03/01
 */

#ifndef COPROCESS_H
#define COPROCESS_H

#include <QProcess>

#include "cogit_global.h"
class CoGit;

//! 本类的功能：实现对子进程的控制
/*! Git程序的具体执行是在子进程中进行的,本进程提供对于子进程的控制方法,包括同步执行,输入输出管道等
 */
class CoProcess : public QProcess
{
	
	Q_OBJECT

	public:
		/*!构造函数
		 * \param git 指向调用它的CoGit对象的指针
		 * \param wd git的顶级工作目录路径
		 */
		CoProcess(CoGit* git, const QString& wd);

		/*!实现同步运行，并获得运行结果
		 * \param cmd 完整的命令字符串列表
		 * \param stdOut 存储命令执行的标准输出
		 * \param stdError 存储命令执行的错误输出
		 * \param inStream 向子进程发送输入的文件的文件名，留空表示不向子进程发送输入
		 * \return 如果同步运行成功,返回True
		 */
		bool runSync(QStringList cmd, QByteArray* stdOut, QByteArray* stdError, QString inStream);

		
	public signal:

		void exceptionOccur(CoError::ErrorType error);


	public slots:

		/*! 当接受到终止信号,所执行的终止操作
		 */
		void onCancel();


	private slots:

		void onReadyReadStandardOutput();
		void onReadyReadStandardError();
		void onFinished(int, QProcess::ExitStatus);

	
	private:

		void setupSignals();
		bool startProcess(QStringList cmd);
		void sendExceptionSignal();

		QStringList m_cmd;
		QString m_gitWdDir;
		QByteArray* m_stdOut;
		QByteArray* m_stdError;
		QString m_inStream;
		bool isWinShell;
		bool canceling;
		bool isErrorExit;
		bool busy;
}

#endif

//! 本类的功能:实现对子进程的控制
