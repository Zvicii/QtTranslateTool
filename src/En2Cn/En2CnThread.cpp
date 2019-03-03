#include "En2CnThread.h"

#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>

#include "En2CnManager.h"
#include "En2CnTableModel.h"
#include "En2CnKeyInfo.h"

CEn2CnThread::CEn2CnThread(const QString& strPath, QObject *parent)
	: QThread(parent)
	, m_strPath(strPath)
	, m_bQuitThread(false)
{
}

CEn2CnThread::~CEn2CnThread()
{
}

void CEn2CnThread::StartThread()
{
	m_bQuitThread = false;
	start();
}

void CEn2CnThread::StopThread()
{
	m_bQuitThread = true;
}

//virtual
void CEn2CnThread::run()
{
	while (!m_bQuitThread)
	{	

		QStringList listFile = GetFileList(m_strPath);

		foreach(QString strFile, listFile)
		{
			if (!m_bQuitThread)
			{
				TranslateFile(QString("%1/%2").arg(m_strPath).arg(strFile));

				msleep(5);
			}
		}
		
		//当前目录翻译完成
		return;
	}
}

void CEn2CnThread::TranslatePath(const QString& strPath)
{
	if (strPath.isEmpty())
	{
		return;
	}

	QDir dirPath(strPath);
	QStringList listSuffix;
	listSuffix << "*.html" << "*.htm";
	dirPath.setNameFilters(listSuffix);

	QStringList listFile = dirPath.entryList(QDir::Files | QDir::Readable, QDir::Size | QDir::Time | QDir::Name);

	foreach(QString strFile, listFile)
	{
		if (!m_bQuitThread)
		{
			TranslateFile(QString("%1/%2").arg(strPath).arg(strFile));
		}
	}
}


QStringList CEn2CnThread::GetFileList(const QString& strPath)
{
	QStringList listFile;
	if (strPath.isEmpty())
	{
		return listFile;
	}

	QDir dirPath(strPath);
	QStringList listSuffix;
	listSuffix << "*.html" << "*.htm";
	dirPath.setNameFilters(listSuffix);

	listFile = dirPath.entryList(QDir::Files | QDir::Readable, QDir::Size | QDir::Time | QDir::Name);

	return listFile;
}

void CEn2CnThread::TranslateFile(const QString& strFile)
{
	if (strFile.isEmpty())
	{
		return;
	}

	QFile oldFile(strFile);
	if (!oldFile.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		return;
	}
	QTextStream instream(&oldFile);
	instream.setCodec("UTF-8");
	QString strOldData = instream.readAll();
	oldFile.close();

	foreach(CEn2CnKeyInfo keyinfo, gEn2CnMgr->GetKeyModel()->GetDataList())
	{
		strOldData.replace(keyinfo.GetEnKey().toUtf8(), keyinfo.GetCnKey().toUtf8());
	}

	QFile newFile(strFile);
	if (!newFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
		return;
	}
	QTextStream outstream(&newFile);
	outstream.setCodec("UTF-8");
	outstream << strOldData;
	newFile.close();
}
