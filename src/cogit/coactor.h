/*!
 *	COPYRIGHT NOTICE
 *	Copyright (c) 2011, Combinz
 *	All rights reserved.
 *
 *	CoGit Library is a Object-Oriented Qt wrap of Git
 *	CoGit Library is released under the GPLv2 License
 *
 *	\file coactor.h
 *	\brief CoActor类的声明部分
 *
 *	\author 丁彦 dingyan@freestorm.org
 *	\author 付亚星 fuyaxing@freestorm.org
 *	\date 2011/03/01
 */

#ifndef COACTOR_H
#define COACTOR_H

#include "cogit_global.h"

//! 本类的功能：储存Git Repo代码贡献者信息的类
/*!
 * 储存参与代码贡献者的信息，可以时commit的创建者或者提交者
 */

class COGIT_EXPORT CoActor
{
	
	public:

		/*! 构造函数
		 * \param name 姓名
		 * \param email 电子邮件地址
		 */
		explicit CoActor(QString name = "" , QString email = "");

		/*! 构造函数，根据格式化的签名抽取name和email的信息并加以储存
		 * sign的格式为: Michael Ding <yandy@combinz.com>
		 * \param sign 格式化的签名
		 */
		explicit CoActor(QString sign);

		/*! 析构函数
		 */
		~CoActor();
		
		/*! 获取名字
		 */
		const QString name() const;

		/*! 获取email地址
		 */
		const QString email() const;

		/*! 获取格式化的签名
		 */
		const QString sign() const;
			
	private:
	
		QString m_name;
		QString m_email;
};

#endif
