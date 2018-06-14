#include "httptest.h"
#include<QtDebug>
#include<qmessagebox.h>
httptest::httptest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton->setText("download");  
    ui.pushButton1->setText("upload");
	ui.pushButton3->setText("test time");
    ui.progressBar->hide();  
    ui.progressBar1->hide();
	ui.progressBar2->hide();
	ui.progressBars->hide();
	QString ftm="";
	QString tim="";
	QString d="";
	QFile filep("posturl.txt");
	if(!filep.open(QIODevice::ReadOnly | QIODevice::Text))
   { 
       qDebug()<<"Can't open the file!"<<endl;
    }
	int len=filep.size();
	if(len==0){ui.pushButton1->setEnabled(false);}
	else{
		    while(!filep.atEnd())
          {
          QByteArray line1 = filep.readLine();
          QString posturl(line1);
	      red.push_back(posturl); 
          }
	}
	 QFile files("result.txt");
     files.open(QFile::WriteOnly|QFile::Truncate);
     files.close();
	 QString displayString;
     
	 
	 QFile file("text.txt");
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    { 
       qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
   {
    QByteArray line = file.readLine();
    QString str(line);
	displayString.append(str);
	 re.push_back(str.remove(QRegExp("\\s")));  
   }
   ui.textEdit->clear();
   ui.textEdit->setPlainText(displayString);
   ui.textEdit->setEnabled(false);
   qDebug()<<re;
	num=0;
    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(httpDownload()));
	connect(ui.pushButton1,SIGNAL(clicked()),this,SLOT(lines()));
    connect(ui.pushButton3,SIGNAL(clicked()),this,SLOT(httpt()));
	connect(ui.pushButtono,SIGNAL(clicked()),this,SLOT(posesave()));

}
void httptest::posesave()
{
	qDebug()<<uptime;
	qDebug()<<downtime;
	qDebug()<<laytime;
	qDebug()<<b;
	float q=23872945;
	float p=6826675;
	float dspeed=((q/1024)/1024)/((downtime[0]+downtime[1])/2);
	float uspeed=p/1024/1024/((uptime[0]+uptime[1])/2);
	QString data = QString("%1").arg(dspeed);
	QString dataa = QString("%1").arg(uspeed);
	QByteArray inputdata = data.toLatin1(); 
	QByteArray outputdata=dataa.toLatin1();
	QVector<int> t;
	QVector<int> m;

	QString tt;
	QString mm;
	for(int i=0;i<laytime.size()/5;i++)
	{
		t.push_back(laytime[i*5]);
		QString ss=QString::number(laytime[i*5]);
		tt.append(ss);
		tt.append("ms  ");
	}
	for(int j=0;j<laytime.size()/5;j++)
	{
		m.push_back((laytime[j*5+1]+laytime[j*5+2]+laytime[j*5+3]+laytime[j*5+4])/4);
		QString sss=QString::number((laytime[j*5+1]+laytime[j*5+2]+laytime[j*5+3]+laytime[j*5+4])/4);
		mm.append(sss);
		mm.append("ms  ");

	}
	QByteArray fm;
	fm=tt.toLatin1();
	//QString s = QString::number(a, 10);
    QByteArray tm;
	tm=mm.toLatin1();
 

	
	qDebug()<<inputdata;
	qDebug()<<outputdata;
	qDebug()<<fm;
	qDebug()<<tm;
	QUrl url("http://127.0.0.1/testmp4/ind.php");  
    accessManagers=new QNetworkAccessManager(this);  
    requests.setUrl(url);  
	replys=accessManagers->post(requests,"filedata="+b+"/\r\n"+outputdata+"M/s"+"\r\n"+inputdata+"M/s"+"\r\n"+fm+"\r\n"+tm+"\r\n");//通过发送数据，返回值保存在reply指针里.  
    connect(accessManagers, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinisheds(QNetworkReply*)));//finish为manager自带的信号，replyFinished是自定义的  
	
	connect(replys, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(saveProgress(qint64 ,qint64 )));//download文件时进度  	  
    ui.progressBars->setValue(0);  
    ui.progressBars->show(); 

}
void httptest::replyFinisheds(QNetworkReply *replys){  
   
    QVariant status_code = replys->attribute(QNetworkRequest::HttpStatusCodeAttribute);  
	qDebug()<<status_code;
	
    if(replys->error() == QNetworkReply::NoError)  
    {   
		ui.pushButtono->setText("success"); 
		ui.pushButtono->setEnabled(false);
		ui.progressBars->hide();
   }  
    else  
    {  
        //处理错误  
         ui.pushButtono->setText("failed"); 
    }  
    replys->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;  
  
} 
void httptest::saveProgress(qint64 bytesSent, qint64 bytesTotal){  
    ui.progressBars->setMaximum(bytesTotal);
    ui.progressBars->setValue(bytesSent); 
}

void httptest::lines()
{
	if(ui.lineEdit->text().isEmpty())//如果为空
   {		
	QMessageBox::warning(this, QString::fromLocal8Bit("warning"),QString::fromLocal8Bit("name cann't be empty"));
    }
	else{
		QString flag=ui.lineEdit->text();b = flag.toLatin1();qDebug()<<b;
		httpPost();}
}
void httptest::text()
{
	logo=1;
	QString strText=ui.textEdit->toPlainText();
	QTextStream ts(&strText);
    while( ! ts.atEnd())
    {
	  QString a=ts.readLine();
	  qDebug()<<a;
	  re.push_back(a.remove(QRegExp("\\s")));
     }
	qDebug()<<re;
}

void httptest::httpt(){  
	ui.pushButton3->setEnabled(false);
	QUrl url(re[num/5]);
	num++;
    accessManager2=new QNetworkAccessManager(this);  
    request2.setUrl(url);
	request2.setAttribute(QNetworkRequest::CacheLoadControlAttribute,QNetworkRequest::AlwaysNetwork);//CacheLoadControlAttribute=0;//(QNetworkRequest::CacheLoadControl,0);
	qDebug()<<"statr";
    time2.start(); 
	reply2=accessManager2->get(request2);//通过发送数据，返回值保存在reply指针里.  
    connect(accessManager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished2(QNetworkReply*)));//finish为manager自带的信号，replyFinished是自定义的  
	connect(reply2, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT( onProgress(qint64 ,qint64 ))); 	
	connect((QObject *)reply2, SIGNAL(readyRead()),this, SLOT(onReadyR()));  
    ui.progressBar2->setValue(0);  
    ui.progressBar2->show(); 
} 
void httptest::replyFinished2(QNetworkReply *reply2)
{
	int timed = time2.elapsed();
	d="";
	ftm="";
	tim="";
	qDebug()<<timed;
    QVariant status_code = reply2->attribute(QNetworkRequest::HttpStatusCodeAttribute);  
	qDebug()<<status_code;
	//QString contentType = reply->header(QNetworkRequest::ContentLengthHeader).toString();
	//qDebug()<<contentType; 
    //无错误返回  
	//float a=23872945;
	//float b=(float)timed/1000;
	laytime.push_back(timed);
    //float speeddown=a/1024/1024/b;
    if(reply2->error() == QNetworkReply::NoError)  
    {     QFile filew("result.txt");
			if((laytime.size()%5)==1)
	        {   for(int i=0;i<=laytime.size()/5;i++)
			     {     d=d+re[i]+"\n";}
			if(laytime.size()==(re.size()-1)*5+1)
			{
				if(filew.open(QIODevice::Append|QIODevice::ReadWrite | QIODevice::Text))
			             {
				          QTextStream inw(&filew);
                          inw<<d;
                           }
					filew.close();

			}
			ui.label6->setText(d);
				 for(int j=0;j<=laytime.size()/5;j++)
				 {
				    ftm=ftm+QString::number(laytime[j*5])+" ms"+"\n";
					
				 }
                 if(laytime.size()==(re.size()-1)*5+1)
					{ if(filew.open(QIODevice::Append|QIODevice::ReadWrite | QIODevice::Text))
			             {
				          QTextStream inw(&filew);
                          inw<<"first delay time:\n"<<ftm;
                            }
					filew.close();
					}
			   ui.label4->setText(ftm);
			   httpt();
			}
	        else if((laytime.size()%5)!=0&&(laytime.size()%5)!=1){httpt();}
			else if((laytime.size()%5)==0&&laytime.size()!=(re.size()*5))
			{
				for(int j=0;j<laytime.size()/5;j++)
				 {
				    tim=tim+QString::number((laytime[j*5+1]+laytime[j*5+2]+laytime[j*5+3]+laytime[j*5+4])/4)+" ms"+"\n";
				 }
				ui.label5->setText(tim);httpt();

			
			}
	       else if(laytime.size()==re.size()*5){
			   for(int k=0;k<laytime.size()/5;k++)
				 {
				    tim=tim+QString::number((laytime[k*5+1]+laytime[k*5+2]+laytime[k*5+3]+laytime[k*5+4])/4)+" ms"+"\n";
				 }
				ui.label5->setText(tim);ui.pushButton3->setText("success");
               if(filew.open(QIODevice::Append|QIODevice::ReadWrite | QIODevice::Text))
			  {
				 QTextStream inw(&filew);
                  inw<<"average delay time:\n"<<tim;
               }
		   }
			 
		//ui.pushButton3->setEnabled(false);
      //reply2->deleteLater();laytime.clear();num=0;
    }  
    else  
    {  
        //处理错误  
         ui.pushButton3->setText("failed");
		 ui.progressBar2->hide();
		 ui.label9->setText(re[laytime.size()/5]+"  "+"failed");
		 reply2->deleteLater();laytime.clear();num=0;
    }  
	//file->close();
    //要删除reply，但是不能在repyfinished里直接delete，要调用deletelater; 
}
void httptest::onProgress(qint64 bytesSent, qint64 bytesTotal){  
    ui.progressBar2->setMaximum(bytesTotal);
    ui.progressBar2->setValue(bytesSent); 
}  
  
void httptest::onReadyR(){  
	QByteArray tmp = reply2->readAll();
    qDebug()<<tmp;
    //file->write(tmp);
    ui.pushButton3->setText("downloading");  
} 
void httptest::httpDownload(){  
     ui.pushButton->setEnabled(false);
    QUrl url("https://cloudclass-dev.oss-cn-beijing.aliyuncs.com/speedtest/mp4speedtest.zip");  
    fileInfo= url.path();  
	file=new QFile(fileInfo.fileName());
	file->open(QIODevice::ReadWrite);//只写方式打开文件  
    accessManager=new QNetworkAccessManager(this);  
    request.setUrl(url);   
	qDebug()<<"statr";
    time.start(); 
	reply=accessManager->get(request);//通过发送数据，返回值保存在reply指针里.  
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));//finish为manager自带的信号，replyFinished是自定义的  
	connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT( onDownloadProgress(qint64 ,qint64 )));//download文件时进度  	
	connect((QObject *)reply, SIGNAL(readyRead()),this, SLOT(onReadyRead()));  
    ui.progressBar->setValue(0);  
    ui.progressBar->show(); 
} 
 
void httptest::replyFinished(QNetworkReply *reply){  
    //获取响应的信息，状态码为200表示正常  
	int time_Diff = time.elapsed();
	qDebug()<<time_Diff;
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);  
	qDebug()<<status_code;
	//QString contentType = reply->header(QNetworkRequest::ContentLengthHeader).toString();
	//qDebug()<<contentType; 
    //无错误返回  
	float a=23872945;
	float b=(float)time_Diff/1000;
	downtime.push_back(b);
	//float speeddown=a/1024/1024/((downtime[0]+downtime[1])/2);
	//ui.label1->setText(QString::number(speeddown,'f',2));
       if(reply->error() == QNetworkReply::NoError)  
      {  
         QFile filew("result.txt");
		//ui.pushButton->setEnabled(false);
       if(downtime.size()==1)
	  {
		  httpDownload();
	  }
	   else{float speeddown=a/1024/1024/((downtime[0]+downtime[1])/2);
	     ui.label1->setText(QString::number(speeddown,'f',2));
	    //ui.pushButton->setEnabled(true);
		ui.pushButton->setText("success");
		  if(filew.open(QIODevice::Append|QIODevice::ReadWrite | QIODevice::Text))
			  {
				 QTextStream inw(&filew);
                  inw<<"download speed :"<<QString::number(speeddown,'f',2)<<"M/s"<<"\n";
               }
		  filew.close();
		  
		file->close();//file->remove();
         reply->deleteLater();
		 //downtime.clear();
	    }
      }  
      else  
      {  
        //处理错误  
         ui.pushButton->setText("failed");
		 ui.pushButton->setEnabled(true);
		  ui.progressBar->hide();
		 file->close();
         reply->deleteLater();
		  //downtime.clear();
      } 
	//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater; 
	  file->close();file->remove();
    
} 
void httptest::onDownloadProgress(qint64 bytesSent, qint64 bytesTotal){  
    ui.progressBar->setMaximum(bytesTotal);
    ui.progressBar->setValue(bytesSent); 
}  
  
void httptest::onReadyRead(){  
	QByteArray tmp = reply->readAll();
    qDebug()<<tmp;
    file->write(tmp);
    ui.pushButton->setText("downloading");  
} 
void httptest::httpPost(){  
	ui.pushButton1->setEnabled(false);
    QUrl url(red[0]);  
	QByteArray byteArry;
    byteArry.resize(5120000);
    for (int i=0;i<5120000;i++)
    {
        byteArry[i]=i;
    }
    accessManager1=new QNetworkAccessManager(this);  
    request1.setUrl(url);  

	qDebug()<<"statr";
    time1.start(); 
	reply1=accessManager1->post(request1,"filedata="+b.toBase64()+"/\r\n"+byteArry.toBase64());//通过发送数据，返回值保存在reply指针里.  
    connect(accessManager1, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished1(QNetworkReply*)));//finish为manager自带的信号，replyFinished是自定义的  
	
	connect(reply1, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT( onPostProgress(qint64 ,qint64 )));//download文件时进度  	
//	connect((QObject *)reply1, SIGNAL(readyRead()),this, SLOT(onReadyW()));  
    ui.progressBar1->setValue(0);  
    ui.progressBar1->show(); 
} 
void httptest::replyFinished1(QNetworkReply *reply1){  
    //获取响应的信息，状态码为200表示正常  
	int time_Diff1 = time1.elapsed();
	qDebug()<<time_Diff1;
    QVariant status_code = reply1->attribute(QNetworkRequest::HttpStatusCodeAttribute);  
	qDebug()<<status_code;
	//QString contentType = reply->header(QNetworkRequest::ContentLengthHeader).toString();
	//qDebug()<<contentType; 
    //无错误返回 
    float a1=6826675;
	float b1=(float)time_Diff1/1000;
	uptime.push_back(b1);
    if(reply1->error() == QNetworkReply::NoError)  
    {  	QFile filew("result.txt");
		if(uptime.size()<2)
	    {
		   httpPost();
	     }
		if(uptime.size()==2)
	  {
		float speedup=a1/1024/1024/((uptime[0]+uptime[1])/2);
	    ui.label3->setText(QString::number(speedup,'f',2));  ui.pushButton1->setText("success"); 
		if(filew.open(QIODevice::Append|QIODevice::ReadWrite | QIODevice::Text))
			  {
				 QTextStream inw(&filew);
                  inw<<"upload speed :"<<QString::number(speedup,'f',2)<<"M/s"<<"\n";
               }
		  filew.close();
		  //ui.progressBar1->hide();
		  //ui.pushButton1->setEnabled(true);
		   ui.progressBar1->hide();
		   //uptime.clear();
	  }
      
  
    }  
    else  
    {  
        //处理错误  
         ui.pushButton1->setText("failed"); 
		 //ui.pushButton1->setEnabled(true);
		 ui.progressBar1->hide();
		  //uptime.clear();
    }  
    reply1->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;  
  
} 
void httptest::onPostProgress(qint64 bytesSent, qint64 bytesTotal){  
    ui.progressBar1->setMaximum(bytesTotal);
    ui.progressBar1->setValue(bytesSent); 
}  
  
//void httptest::onReadyW(){  
//	QByteArray tmp = reply1->readAll();
//    qDebug()<<tmp;
   // file->write(tmp);
//    ui.pushButton1->setText("posting");  
//}
  
//void httptest::stop(){  
//    if(!httpRequestAbort)  
//    {  
//    reply->abort();//响应终止  
//    httpRequestAbort=true;  
//    //stop_Btn->setText("start");  
//    }  
//    else  
//    {   httpDownload();  
//        httpRequestAbort=false;  
//        //stop_Btn->setText("stop");  
//     }  
//  
//}  
httptest::~httptest()
{

}
