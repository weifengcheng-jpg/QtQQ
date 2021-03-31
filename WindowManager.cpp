#include "WindowManager.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"

//单例模式，创建全局静态对象
Q_GLOBAL_STATIC(WindowManager,theInstance)


WindowManager::WindowManager()
	:QObject(nullptr)
	,m_talkwindowshell(nullptr)
{
}

WindowManager::~WindowManager()
{
}

QWidget * WindowManager::findWindowName(const QString & qsWindowName)
{
	if (m_windowMap.contains(qsWindowName))
	{
		return m_windowMap.value(qsWindowName);
	}
	
	return nullptr;
}

void WindowManager::deleteWindowName(const QString & qsWindowName)
{
	m_windowMap.remove(qsWindowName);
}

void WindowManager::addWindowName(const QString & qsWindowName, QWidget * qWidget)
{
	if (!m_windowMap.contains(qsWindowName))
	{
		m_windowMap.insert(qsWindowName, qWidget);
	}
}

WindowManager * WindowManager::getInstance()
{
	return theInstance();
}

void WindowManager::addNewTalkWindow(const QString & uid, GroupType groupType, const QString & strPeople)
{
	if (m_talkwindowshell == nullptr)
	{
		m_talkwindowshell = new TalkWindowShell;
		connect(m_talkwindowshell, &TalkWindowShell::destroyed, [this](QObject* obj) {
			m_talkwindowshell = nullptr;
		});
	}

	QWidget* widget = findWindowName(uid);
	if (!widget)
	{
		TalkWindow* talkwindow = new TalkWindow(m_talkwindowshell, uid, groupType);
		TalkWindowItem* talkwindowItem = new TalkWindowItem(talkwindow);

		switch (groupType) {
		case COMPANY:
		{
			talkwindow->setWindowName(QStringLiteral("奇牛科技-越分享越拥有"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("公司群"));
			break;
		}
		case PERSONELGROUP:
		{
			talkwindow->setWindowName(QStringLiteral("公心、民心、爱心，事事在心"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("人事群"));
			break;
		}
		case MARKETGROUP:
		{
			talkwindow->setWindowName(QStringLiteral("今天工作不努力，明天努力找工作"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("市场群"));
			break;
		}
		case DEVELOPMENTGROUP:
		{
			talkwindow->setWindowName(QStringLiteral("只有两种编程语言：一种是天天挨骂的，另一种是没人用的"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("研发群"));
			break;
		}
		case PTOP:
		{
			talkwindow->setWindowName(QStringLiteral("奇牛科技-越分享越拥有"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("公司群"));
			break;
		}
		default:
			break;
		}
	}
	else
	{
		m_talkwindowshell->setCurrentWidget(widget);
	}

	m_talkwindowshell->show();
	m_talkwindowshell->activateWindow();
}
