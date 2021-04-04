#pragma once

#include <QTextEdit>

class QMsgTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	QMsgTextEdit(QWidget *parent);
	~QMsgTextEdit();

private slots:
	void onEmotionImageFrameChange(int frame);//动画改变时响应的槽函数

public:
	void addEmotionUrl(int emotionNum);
	void deletAllEmotionImage();

private:
	QList<QString> m_listEmotionUrl;
	QMap<QMovie*, QString> m_emotionMap;
};
