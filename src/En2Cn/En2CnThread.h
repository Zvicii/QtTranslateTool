#pragma once

#include <QThread>

class CEn2CnThread : public QThread
{
	Q_OBJECT

public:
	CEn2CnThread(const QString& strPath, QObject *parent);
	~CEn2CnThread();

	void StartThread();
	void StopThread();

protected:
	virtual void run();

private:
	void TranslatePath(const QString& strPath);
	QStringList GetFileList(const QString& strPath);
	void TranslateFile(const QString& strFile);

private:
	QString					m_strPath;
	bool					m_bQuitThread;
};
