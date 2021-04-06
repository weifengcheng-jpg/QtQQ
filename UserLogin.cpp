#include "UserLogin.h"
#include "CCMainWindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

QString gLoginEmployeeID;//��¼��QQ��(Ա����)

UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	initTitleBar();
	setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");
	loadStyleSheet("UserLogin");
	initControl();
}

UserLogin::~UserLogin()
{
}

void UserLogin::initControl()
{
	QLabel *headlabel = new QLabel(this);
	headlabel->setFixedSize(68, 68);
	QPixmap pix(":/Resources/MainWindow/head_mask.png");
	headlabel->setPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/girl.png"), pix, headlabel->size()));
	headlabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);
	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);

	//�������ݿ�
	if (!connectMySql())
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�������ݿ�ʧ�ܣ�"));
		close();
	}
}

bool UserLogin::connectMySql()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setDatabaseName("qtqq");	//���ݿ�����
	db.setHostName("localhost");//������
	db.setUserName("root");		//�û���
	db.setPassword("666666");	//����
	db.setPort(3306);			//�˿�

	if (db.open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UserLogin::veryfyAccountCode()
{
	QString strAccountInput = ui.editUserAccount->text();
	QString strCodeInput = ui.editPassword->text();

	//����Ա����(QQ�ŵ�½)
	QString strSqlCode = QString("SELECT code FROM tab_accounts WHERE employeeID = %1").arg(strAccountInput);
	QSqlQuery queryEmployeeID(strSqlCode);
	queryEmployeeID.exec();

	if (queryEmployeeID.first())//ָ��������һ��
	{
		//���ݿ���qq�Ŷ�Ӧ������ 
		QString strCode = queryEmployeeID.value(0).toString();

		if (strCode == strCodeInput)
		{
			gLoginEmployeeID = strAccountInput;
			return true;
		}
		else
		{
			return false;
		}
	}

	//�˺ŵ�¼
	strSqlCode = QString("SELECT code,employeeID FROM tab_accounts WHERE account = '%1'")
						.arg(strAccountInput);
	QSqlQuery queryAccount(strSqlCode);
	queryAccount.exec();
	if (queryAccount.first())
	{
		QString strCode = queryAccount.value(0).toString();

		if (strCode == strCodeInput)
		{
			gLoginEmployeeID = queryAccount.value(1).toString();
			return true;
		}
		else
		{
			return false;
		}
	}


	return false;
}

void UserLogin::onLoginBtnClicked()
{
	if (!veryfyAccountCode())
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��������˺Ż������������������룡"));
		//ui.editPassword->setText("");
		//ui.editPassword->setText("");
		return;
	}

	close();
	CCMainWindow* mainwindow = new CCMainWindow;
	mainwindow->show();
}