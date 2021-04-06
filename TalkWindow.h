#pragma once

#include <QWidget>
#include "TalkWindowShell.h"
#include "ui_TalkWindow.h"

class TalkWindow : public QWidget
{
	Q_OBJECT

public:
	TalkWindow(QWidget *parent,const QString& uid/*,GroupType groupType*/);
	~TalkWindow();

public:
	void addEmotionImage(int emotionNum);
	void setWindowName(const QString& name);

private slots:
	void onSendBtnClicked(bool);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);

private:
	void initControl();

	void initCompanyTalk();	//��ʼ����˾Ⱥ����
	void initPersonelTalk();	//��ʼ�����²�����
	void initMarketTalk();	//��ʼ���г�������
	void initDevelopTalk();	//��ʼ���з�������
	void initPtoPTalk();		//��ʼ������
	void addPeopInfo(QTreeWidgetItem* pRootGroupItem);

private:
	Ui::TalkWindow ui;
	QString m_talkId;
//	GroupType m_groupType;
	QMap<QTreeWidgetItem*, QString> m_groupPeopleMap;//���з�����ϵ������
};
