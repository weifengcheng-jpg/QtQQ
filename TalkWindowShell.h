#pragma once

#include "basicwindow.h"
#include "ui_TalkWindowShell.h"
#include <qmap.h>

class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

enum GroupType {
	COMPANY = 0,	//��˾Ⱥ
	PERSONELGROUP,	//���²�
	DEVELOPMENTGROUP,//�з���
	MARKETGROUP,	//�г���
	PTOP			//ͬ��֮�䵥������
};

class TalkWindowShell : public BasicWindow
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = Q_NULLPTR);
	~TalkWindowShell();

public:
	//����µ����촰��
	void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, const QString& uid/*,GroupType grouptype*/);
	
	//���õ�ǰ���촰��
	void setCurrentWidget(QWidget* widget);

	const QMap<QListWidgetItem*, QWidget*>& getTalkWindowItemMap()const;

private:
	void initControl();//��ʼ���ؼ�

public slots:
	void onEmotionBtnClicked(bool);//���鰴ť�����ִ�еĲۺ���

private slots:
	void onTalkWindowItemClicked(QListWidgetItem* item);//����б�����ִ�еĲۺ���
	void onEmotionItemClicked(int emotionNum);	//���鱻ѡ��

private:
	Ui::TalkWindowClass ui;
	QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;//�򿪵����촰��
	EmotionWindow* m_emotionWindow;	//���鴰��
};
