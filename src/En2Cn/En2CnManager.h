#ifndef EN2CNMANAGER_H
#define EN2CNMANAGER_H

#include <QObject>

#include "En2CnKeyInfo.h"

class CEn2CnKeyFile;
class CEn2CnTableModel;
class CEn2CnThread;

#if defined(gEn2CnMgr)
    #undef gEn2CnMgr
#endif
#define gEn2CnMgr (CEn2CnManager::Instance())

//Ӣ�ķ�������ĵĹ�����
class CEn2CnManager : public QObject
{
Q_OBJECT
private:
    explicit CEn2CnManager(QObject *parent = nullptr);
    ~CEn2CnManager();

public:
    static CEn2CnManager* Instance();
    static void Release();

public:
    CEn2CnKeyFile* GetKeyFile();
	CEn2CnTableModel* GetKeyModel();

    //ͳһ����Ӣ�ķ�������ĵ���ɾ�Ĳ�
    void AddKeyInfo(const CEn2CnKeyInfo& keyInfo);
    void AddKeyInfo(int iKeyId, const QString& strEnKey, const QString& strCnKey);
    void UpdateKeyInfo(int iKeyId, const QString& strEnKey, const QString& strCnKey);
    void UpdateKeyInfo(const QString& strEnKey, const QString& strCnKey);
    void DelKeyInfo(int iKeyId);
    void DelKeyInfo(const QString& strEnKey);
    void DelAllKey();
    bool ExistKey(const QString& strEnKey);
    int GetMaxKeyId();

	//������Ŀ¼
	void TranslatePaths(const QStringList& listPath);

signals:

	public slots :

private slots :
	void OnThreadFinished();

private:
    static CEn2CnManager* sm_pInstance;

private:
	//���뵥��Ŀ¼
	void TranslatePath(const QString& strPath);

private:
    CEn2CnKeyFile*              m_pKeyFile;         //Ӣ�ķ�������ĵ��ļ�
	CEn2CnTableModel*            m_pKeyModel;
};

#endif // EN2CNMANAGER_H
