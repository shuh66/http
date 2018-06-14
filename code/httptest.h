#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QVector>   
#include <QFile>     
#include <QPushButton>  
#include <QVBoxLayout>  
#include <QIODevice>  
#include <QFileInfo>  
#include <QProgressBar>  
#include <QEventLoop>
#include <QThread>
#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <iostream>
#include <QDebug>
#include <QEventLoop>
#include <QTime>
#include <QNetworkProxy>
#include <QtWidgets/QMainWindow>
#include "ui_httptest.h"
#include <string.h>

class httptest : public QMainWindow
{
	Q_OBJECT

public:
	httptest(QWidget *parent = 0);
	~httptest();
	QVector<int> data;
	QString ftm;
	QString tim;
	QString d;
	QString posturl;
protected slots:  
    void httpDownload(); 
	void httpPost();
    void replyFinished(QNetworkReply*); 
	void replyFinished1(QNetworkReply*);
	void replyFinished2(QNetworkReply*);
	void replyFinisheds(QNetworkReply*);

    void onDownloadProgress(qint64 bytesSent,qint64 bytesTotal);
	void onPostProgress(qint64,qint64);
	void saveProgress(qint64,qint64);
	void onProgress(qint64,qint64);
    void onReadyRead();
	void onReadyR();
	//void reset();
	void httpt();
	void text();
	void lines();
	void posesave();
	//void onReadyW();//  
    //void stop();//暂停，重新下载 
private:
	 QVector<QString> re;
	 QVector<QString> red;
	 QVector<float> uptime;
	 QVector<int> laytime;
	 QVector<float> downtime;
	 int logo;
	 QByteArray b;

	QTime time;
	QTime time1;
	QTime time2;
    QFile *file;  
    QFileInfo fileInfo;  
    QNetworkAccessManager *accessManager;
	QNetworkAccessManager *accessManager1;
	QNetworkAccessManager *accessManager2;
	QNetworkAccessManager *accessManagers;
	QNetworkRequest requests;
	QNetworkRequest request1;
    QNetworkRequest request; 
	QNetworkRequest request2;
    QNetworkReply *reply;  
	QNetworkReply *reply1;
	QNetworkReply *reply2;
	QNetworkReply *replys;
 int num;
   // bool httpRequestAbort; //请求停止的标志位,false表示允许请求  
private:
	Ui::httptestClass ui;
};

#endif // HTTPTEST_H
