#pragma once

#include "basicwindow.h"
#include "ui_TalkWindowShell.h"
#include <qmap.h>
#include <QTcpSocket>

class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

const int gtcpPort = 6666;

class TalkWindowShell : public BasicWindow
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = Q_NULLPTR);
	~TalkWindowShell();

public:
	//添加新的聊天窗口
	void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, const QString& uid);
	
	//设置当前聊天窗口
	void setCurrentWidget(QWidget* widget);

	const QMap<QListWidgetItem*, QWidget*>& getTalkWindowItemMap()const;

private:
	void initControl();		//初始化控件
	void initTcpSocket();	//初始化TCP

public slots:
	void onEmotionBtnClicked(bool);//表情按钮点击后执行的槽函数

	//客户端发送Tcp数据（数据，数据类型，文件）
	void updateSendTcpMsg(QString& strData, int &msgType, QString sFile = "");
private slots:
	void onTalkWindowItemClicked(QListWidgetItem* item);//左侧列表点击后执行的槽函数
	void onEmotionItemClicked(int emotionNum);	//表情被选中

private:
	Ui::TalkWindowClass ui;
	QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;//打开的聊天窗口
	EmotionWindow* m_emotionWindow;	//表情窗口

private:
	QTcpSocket *m_tcpClientSocket;	//Tcp客户端
};
